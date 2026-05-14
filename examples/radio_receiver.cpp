#include "radio_common.hpp"

#include "wbhf_modem/control_server.hpp"
#include "wbhf_modem/control/v1/receiver_control.grpc.pb.h"
#include "wbhf_modem/io.hpp"
#include "wbhf_modem/quote_udp.hpp"

#include <grpcpp/grpcpp.h>

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <cstdint>
#include <deque>
#include <iostream>
#include <memory>
#include <mutex>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>
#include <vector>

namespace {

std::atomic_bool running = true;

void handle_signal(int) {
  running.store(false);
}

struct Args {
  std::string receiver_address = "127.0.0.1:50051";
  std::string transmitter_control_address = "127.0.0.1:50052";
  std::string iq_input = "/dev/audio";
  std::string quote_destination_ip = "127.0.0.1";
  std::uint16_t quote_destination_port = 9001;
  std::uint8_t client_id = 0;
  wbhf_modem::SampleFormat sample_format = wbhf_modem::SampleFormat::s16_stereo_iq;
  std::size_t chunk_samples = 256;
  float scale = 0.95F;
};

std::uint64_t epoch_nanos() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

void set_permission_bit(wbhf_modem::SymbolPermissionMask& mask, std::uint8_t symbol) {
  const auto index = static_cast<std::size_t>(symbol - wbhf_modem::symbol_min_byte);
  mask[index / 8U] = static_cast<std::uint8_t>(mask[index / 8U] |
                                              (static_cast<std::uint8_t>(1U) << (index % 8U)));
}

wbhf_modem::SymbolPermissionMask default_receiver_permissions(std::uint8_t client_id) {
  wbhf_modem::SymbolPermissionMask mask{};
  for (std::uint16_t symbol = wbhf_modem::symbol_min_byte;
       symbol <= wbhf_modem::market_symbol_max_byte;
       ++symbol) {
    set_permission_bit(mask, static_cast<std::uint8_t>(symbol));
  }
  set_permission_bit(mask, wbhf_modem::client_id_to_symbol(client_id));
  return mask;
}

struct ReceiverSessionEvent {
  enum class Type {
    client_message,
    signal_event,
  };

  Type type = Type::client_message;
  std::uint64_t timestamp_ns = 0;
  std::uint8_t client_id = 0;
  std::vector<std::uint8_t> payload;
  std::string event_type;
  std::string detail;
  double metric = 0.0;
  std::uint64_t count = 0;
};

class ReceiverSessionEventQueue {
public:
  explicit ReceiverSessionEventQueue(std::size_t capacity)
      : capacity_(capacity) {}

  void push(ReceiverSessionEvent event) {
    {
      std::scoped_lock lock(mutex_);
      if (queue_.size() >= capacity_) {
        queue_.pop_front();
      }
      queue_.push_back(std::move(event));
    }
    cv_.notify_one();
  }

  bool try_pop(ReceiverSessionEvent& event) {
    std::scoped_lock lock(mutex_);
    if (queue_.empty()) {
      return false;
    }
    event = std::move(queue_.front());
    queue_.pop_front();
    return true;
  }

  void wait_for_event(std::chrono::milliseconds timeout) {
    std::unique_lock lock(mutex_);
    if (!queue_.empty()) {
      return;
    }
    cv_.wait_for(lock, timeout);
  }

private:
  std::size_t capacity_ = 0;
  std::mutex mutex_;
  std::condition_variable cv_;
  std::deque<ReceiverSessionEvent> queue_;
};

class ReceiverMessageObserver final : public wbhf_modem::DelimitedMessageObserver {
public:
  ReceiverMessageObserver(wbhf_modem::QuotePacketEmitter& quote_emitter,
                          std::shared_ptr<ReceiverSessionEventQueue> session_events)
      : quote_emitter_(quote_emitter),
        session_events_(std::move(session_events)) {}

  void on_delimited_message(const wbhf_modem::DelimitedMessage& message) override {
    if (message.bytes.size() >= 2U && wbhf_modem::is_client_symbol_byte(message.bytes[1])) {
      session_events_->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::client_message,
                                                 .timestamp_ns = epoch_nanos(),
                                                 .client_id = wbhf_modem::client_symbol_to_id(message.bytes[1]),
                                                 .payload = message.bytes});
      return;
    }
    quote_emitter_.on_delimited_message(message);
  }

private:
  wbhf_modem::QuotePacketEmitter& quote_emitter_;
  std::shared_ptr<ReceiverSessionEventQueue> session_events_;
};

void receiver_session_loop(std::shared_ptr<wbhf_modem::ReceiverControlState> control,
                           std::shared_ptr<ReceiverSessionEventQueue> session_events,
                           std::string transmitter_address,
                           std::uint8_t client_id) {
  namespace pb = ::wbhf_modem::control::v1;
  auto steady_millis = [] {
    return std::chrono::duration_cast<std::chrono::milliseconds>(
               std::chrono::steady_clock::now().time_since_epoch())
        .count();
  };
  while (running.load()) {
    auto channel = grpc::CreateChannel(transmitter_address, grpc::InsecureChannelCredentials());
    auto stub = pb::TransmitterControl::NewStub(channel);
    grpc::ClientContext context;
    auto stream = stub->ReceiverSession(&context);

    pb::ReceiverSessionClientMessage hello;
    hello.mutable_hello()->set_client_id(client_id);
    if (!stream->Write(hello)) {
      control->clear_banks();
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
      continue;
    }

    std::atomic_bool stream_open = true;
    std::atomic<std::int64_t> last_server_heartbeat_millis;
    last_server_heartbeat_millis.store(steady_millis());

    std::thread writer([&] {
      auto send_event = [&](const ReceiverSessionEvent& event) {
        pb::ReceiverSessionClientMessage out;
        if (event.type == ReceiverSessionEvent::Type::client_message) {
          auto* client_message = out.mutable_client_message();
          client_message->set_receiver_unix_nanos(event.timestamp_ns);
          client_message->set_client_id(event.client_id);
          client_message->set_wire_payload(reinterpret_cast<const char*>(event.payload.data()),
                                           event.payload.size());
        } else {
          auto* signal_event = out.mutable_signal_event();
          signal_event->set_receiver_unix_nanos(event.timestamp_ns);
          signal_event->set_event_type(event.event_type);
          signal_event->set_detail(event.detail);
          signal_event->set_metric(event.metric);
          signal_event->set_count(event.count);
        }
        return stream->Write(out);
      };

      auto last_heartbeat = std::chrono::steady_clock::now() - std::chrono::seconds(1);
      while (running.load() && stream_open.load()) {
        ReceiverSessionEvent event;
        while (session_events->try_pop(event)) {
          if (!send_event(event)) {
            stream_open.store(false);
            break;
          }
        }
        if (!stream_open.load()) {
          break;
        }

        if (std::chrono::steady_clock::now() - last_heartbeat >= std::chrono::seconds(1)) {
          pb::ReceiverSessionClientMessage heartbeat;
          const auto now = std::chrono::system_clock::now().time_since_epoch();
          heartbeat.mutable_heartbeat()->set_unix_micros(
              static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now).count()));
          if (!stream->Write(heartbeat)) {
            break;
          }
          last_heartbeat = std::chrono::steady_clock::now();
        }

        if (steady_millis() - last_server_heartbeat_millis.load() > 3000) {
          control->clear_banks();
          context.TryCancel();
          return;
        }
        session_events->wait_for_event(std::chrono::milliseconds(10));
      }
      stream->WritesDone();
    });

    pb::ReceiverSessionServerMessage message;
    while (running.load() && stream->Read(&message)) {
      if (message.has_heartbeat()) {
        last_server_heartbeat_millis.store(steady_millis());
      } else if (message.has_bank_update()) {
        const auto& bank_update = message.bank_update();
        std::vector<std::uint64_t> prices(bank_update.prices_units().begin(),
                                          bank_update.prices_units().end());
        try {
          const auto bank = static_cast<std::uint8_t>(bank_update.bank());
          if (bank_update.generation() != 0U) {
            control->replace_bank(bank, prices, bank_update.generation());
          } else {
            control->update_bank(bank, prices);
          }
        } catch (const std::exception& exception) {
          std::cerr << "receiver session ignored invalid bank update: " << exception.what() << '\n';
        }
      }
    }
    stream_open.store(false);
    context.TryCancel();
    if (writer.joinable()) {
      writer.join();
    }
    (void)stream->Finish();
    control->clear_banks();
    if (running.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(250));
    }
  }
}

Args parse_args(int argc, char** argv) {
  Args args;
  for (int i = 1; i < argc; ++i) {
    const std::string key = argv[i];
    if (i + 1 >= argc) {
      throw std::invalid_argument("missing value for " + key);
    }
    const std::string value = argv[++i];
    if (key == "--receiver") {
      args.receiver_address = value;
    } else if (key == "--transmitter-control") {
      args.transmitter_control_address = value;
    } else if (key == "--transmitter-ip") {
      args.transmitter_control_address = value + ":50052";
    } else if (key == "--iq-input") {
      args.iq_input = value;
    } else if (key == "--quote-destination-ip") {
      args.quote_destination_ip = value;
    } else if (key == "--quote-destination-port") {
      args.quote_destination_port = static_cast<std::uint16_t>(std::stoul(value));
    } else if (key == "--client-id") {
      const auto client_id = std::stoul(value);
      if (client_id >= wbhf_modem::Clients) {
        throw std::invalid_argument("client-id must be in [0, " +
                                    std::to_string(wbhf_modem::Clients - 1U) +
                                    "]");
      }
      args.client_id = static_cast<std::uint8_t>(client_id);
    } else if (key == "--sample-format") {
      args.sample_format = radio_example::parse_sample_format(value);
    } else if (key == "--chunk-samples") {
      args.chunk_samples = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--scale") {
      args.scale = std::stof(value);
    } else {
      throw std::invalid_argument("unknown argument: " + key);
    }
  }
  if (args.chunk_samples == 0U) {
    throw std::invalid_argument("chunk-samples must be positive");
  }
  return args;
}

} // namespace

int main(int argc, char** argv) {
  using namespace wbhf_modem;

  try {
    const auto args = parse_args(argc, argv);
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    SpscRingBuffer<DelimitedMessage> rx_messages(4096);
    auto receiver_control = std::make_shared<ReceiverControlState>();
    auto session_events = std::make_shared<ReceiverSessionEventQueue>(4096);
    const auto permissions = default_receiver_permissions(args.client_id);
    receiver_control->update_permissions(permissions);
    ReceiverControlServer receiver_server(receiver_control, {.listen_address = args.receiver_address});

    QuoteUdpSinkConfig quote_config;
    quote_config.backend = QuoteUdpBackend::kernel_udp;
    quote_config.destination_ip = args.quote_destination_ip;
    quote_config.destination_port = args.quote_destination_port;
    quote_config.source_ip = "0.0.0.0";
    quote_config.source_port = 0;
    auto quote_sink = make_quote_packet_sink(quote_config);

    ControlledRealtimeReceiver receiver(receiver_control, rx_messages);
    QuotePacketEmitter quote_emitter(receiver_control, quote_sink);
    ReceiverMessageObserver message_observer(quote_emitter, session_events);
    receiver.set_decoded_message_observer(&message_observer);
    FileIqSource source(args.iq_input, args.sample_format, args.scale);

    receiver_server.start();
    std::thread session_thread([&] {
      receiver_session_loop(receiver_control, session_events, args.transmitter_control_address, args.client_id);
    });
    std::cout << "receiver gRPC: " << receiver_server.bound_address() << '\n'
              << "transmitter session: " << args.transmitter_control_address << '\n'
              << "client id: " << static_cast<unsigned>(args.client_id) << '\n'
              << "IQ input: " << args.iq_input << '\n'
              << "quote UDP: " << args.quote_destination_ip << ':' << args.quote_destination_port << '\n';

    std::vector<Complex> samples(args.chunk_samples);
    std::uint64_t decoded_messages = 0;
    try {
      while (running.load()) {
        const auto n = source.read(samples);
        if (n == 0U) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          continue;
        }
        const auto result = receiver.push_samples(std::span<const Complex>(samples).first(n));
        if (result.lock_lost) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "lock_lost"});
        }
        if (result.output_backpressure) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "output_backpressure"});
        }
        if (result.replay_rejected) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "replay_rejected",
                                                    .metric = result.sync_timestamp_seconds});
        }
        DelimitedMessage message;
        while (rx_messages.try_pop(message)) {
          ++decoded_messages;
        }
      }
    } catch (...) {
      running.store(false);
      receiver_server.stop();
      if (session_thread.joinable()) {
        session_thread.join();
      }
      throw;
    }

    std::cout << "stopping receiver, decoded_messages=" << decoded_messages << '\n';
    running.store(false);
    if (session_thread.joinable()) {
      session_thread.join();
    }
    receiver_server.stop();
    return 0;
  } catch (const std::exception& exception) {
    std::cerr << "radio receiver error: " << exception.what() << '\n';
    return 1;
  }
}
