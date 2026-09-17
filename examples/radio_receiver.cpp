#include "radio_common.hpp"

#include "goblin_cannon/control_server.hpp"
#include "goblin_cannon/control/v1/receiver_control.grpc.pb.h"
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/io.hpp"
#include "goblin_cannon/quote_udp.hpp"
#include "goblin_cannon/ring_buffer.hpp"

#include <grpcpp/grpcpp.h>

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <csignal>
#include <cstdint>
#include <deque>
#include <limits>
#include <iostream>
#include <memory>
#include <mutex>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>
#include <utility>
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
  goblin_cannon::SampleFormat sample_format = goblin_cannon::SampleFormat::s16_stereo_iq;
  std::size_t chunk_samples = 256;
  float scale = 0.95F;
  std::size_t pipe_capacity_bytes = 4096;
  std::uint64_t iq_trace_interval_ms = 1000;
  std::uint64_t canonical_timeout_ms = 1000;
  std::uint64_t bad_message_window_ms = 10000;
  std::uint64_t bad_message_shutdown_threshold = 8;
};

std::uint64_t epoch_nanos() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

void set_permission_bit(goblin_cannon::SymbolPermissionMask& mask, std::uint8_t symbol) {
  const auto index = static_cast<std::size_t>(symbol - goblin_cannon::symbol_min_byte);
  mask[index / 8U] = static_cast<std::uint8_t>(mask[index / 8U] |
                                              (static_cast<std::uint8_t>(1U) << (index % 8U)));
}

goblin_cannon::SymbolPermissionMask default_receiver_permissions(std::uint8_t client_id) {
  goblin_cannon::SymbolPermissionMask mask{};
  for (std::uint16_t symbol = goblin_cannon::symbol_min_byte;
       symbol <= goblin_cannon::market_symbol_max_byte;
       ++symbol) {
    set_permission_bit(mask, static_cast<std::uint8_t>(symbol));
  }
  set_permission_bit(mask, goblin_cannon::client_id_to_symbol(client_id));
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

struct ReceiverUdpPacket {
  std::array<std::uint8_t, 32> bytes{};
  std::size_t size = 0;
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

// Wraps a real QuotePacketSink so the decode thread only does a non-blocking
// ring push instead of a sendto() syscall per decoded quote. A background
// thread drains the ring and calls the underlying sink.
class AsyncQuotePacketSink final : public goblin_cannon::QuotePacketSink {
public:
  AsyncQuotePacketSink(std::shared_ptr<goblin_cannon::QuotePacketSink> inner,
                       std::size_t capacity = 4096)
      : inner_(std::move(inner)),
        ring_(capacity) {
    if (!inner_) {
      throw std::invalid_argument("AsyncQuotePacketSink requires inner sink");
    }
    thread_ = std::thread([this] { drain_loop(); });
  }

  ~AsyncQuotePacketSink() override {
    stop();
    if (thread_.joinable()) {
      thread_.join();
    }
  }

  AsyncQuotePacketSink(const AsyncQuotePacketSink&) = delete;
  AsyncQuotePacketSink& operator=(const AsyncQuotePacketSink&) = delete;

  void send_packet(std::span<const std::uint8_t> payload) override {
    ReceiverUdpPacket buffer{};
    if (payload.size() > buffer.bytes.size()) {
      dropped_.fetch_add(1U, std::memory_order_relaxed);
      return;
    }
    std::copy(payload.begin(), payload.end(), buffer.bytes.begin());
    buffer.size = payload.size();
    if (!ring_.try_push(buffer)) {
      dropped_.fetch_add(1U, std::memory_order_relaxed);
    }
  }

  void stop() noexcept {
    stop_.store(true, std::memory_order_release);
  }

  [[nodiscard]] std::uint64_t dropped() const noexcept {
    return dropped_.load(std::memory_order_relaxed);
  }

private:
  void drain_loop() {
    ReceiverUdpPacket payload{};
    while (!stop_.load(std::memory_order_acquire) && running.load(std::memory_order_acquire)) {
      bool any = false;
      while (ring_.try_pop(payload)) {
        inner_->send_packet(std::span<const std::uint8_t>(payload.bytes).first(payload.size));
        any = true;
      }
      if (!any) {
        std::this_thread::sleep_for(std::chrono::microseconds(50));
      }
    }
    // Drain remaining on shutdown so we don't lose tail quotes.
    while (ring_.try_pop(payload)) {
      try {
        inner_->send_packet(std::span<const std::uint8_t>(payload.bytes).first(payload.size));
      } catch (...) {
        break;
      }
    }
  }

  std::shared_ptr<goblin_cannon::QuotePacketSink> inner_;
  goblin_cannon::SpscRingBuffer<ReceiverUdpPacket> ring_;
  std::atomic_bool stop_{false};
  std::atomic_uint64_t dropped_{0};
  std::thread thread_;
};

std::uint64_t checked_add_price_delta(std::uint64_t base, std::int64_t delta) {
  if (delta >= 0) {
    const auto unsigned_delta = static_cast<std::uint64_t>(delta);
    if (base > std::numeric_limits<std::uint64_t>::max() - unsigned_delta) {
      return std::numeric_limits<std::uint64_t>::max();
    }
    return base + unsigned_delta;
  }
  const auto magnitude = static_cast<std::uint64_t>(-(delta + 1)) + 1U;
  return base < magnitude ? 0U : base - magnitude;
}

class CanonicalRadioMessageVerifier {
public:
  CanonicalRadioMessageVerifier(std::shared_ptr<goblin_cannon::ReceiverControlState> control,
                                std::chrono::milliseconds timeout,
                                std::chrono::milliseconds bad_window,
                                std::uint64_t shutdown_threshold)
      : control_(std::move(control)),
        timeout_(timeout),
        bad_window_(bad_window),
        shutdown_threshold_(shutdown_threshold) {}

  void note_radio_message(const goblin_cannon::DelimitedMessage& message) {
    const auto now = std::chrono::steady_clock::now();
    PendingRadioMessage pending;
    pending.payload = message.bytes;
    pending.received_steady = now;
    pending.received_unix_nanos = epoch_nanos();
    fill_price_snapshot(pending);

    std::scoped_lock lock(mutex_);
    prune_canonical_locked(now);
    const auto canonical = find_payload(canonical_, pending.payload);
    if (canonical != canonical_.end()) {
      canonical_.erase(canonical);
      return;
    }
    pending_radio_.push_back(std::move(pending));
  }

  void note_canonical_message(std::span<const std::uint8_t> payload) {
    const auto now = std::chrono::steady_clock::now();
    std::vector<std::uint8_t> bytes(payload.begin(), payload.end());
    std::scoped_lock lock(mutex_);
    prune_canonical_locked(now);
    const auto pending = find_payload(pending_radio_, bytes);
    if (pending != pending_radio_.end()) {
      pending_radio_.erase(pending);
      return;
    }
    canonical_.push_back(CanonicalMessage{.payload = std::move(bytes), .received_steady = now});
  }

  bool sweep(goblin_cannon::QuotePacketSink& sink,
             ReceiverSessionEventQueue& session_events) {
    const auto now = std::chrono::steady_clock::now();
    std::vector<PendingRadioMessage> expired;
    bool shutdown = false;
    {
      std::scoped_lock lock(mutex_);
      prune_canonical_locked(now);
      while (!pending_radio_.empty() && now - pending_radio_.front().received_steady >= timeout_) {
        expired.push_back(std::move(pending_radio_.front()));
        pending_radio_.pop_front();
      }
      for (std::size_t i = 0; i < expired.size(); ++i) {
        bad_message_times_.push_back(now);
      }
      while (!bad_message_times_.empty() && now - bad_message_times_.front() > bad_window_) {
        bad_message_times_.pop_front();
      }
      shutdown = shutdown_threshold_ != 0U && bad_message_times_.size() >= shutdown_threshold_;
    }

    for (const auto& bad : expired) {
      const auto packet = goblin_cannon::make_bad_message_udp_payload(bad.bank,
                                                                   bad.symbol,
                                                                   bad.base_price_units,
                                                                   bad.reconstructed_price_units);
      sink.send_bad_message_packet(std::span<const std::uint8_t, 19>(packet));
      session_events.push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                               .timestamp_ns = epoch_nanos(),
                                               .event_type = "unaccounted_radio_message",
                                               .detail = goblin_cannon::is_client_symbol_byte(bad.symbol)
                                                   ? "client_symbol"
                                                   : "market_symbol",
                                               .count = 1});
    }
    if (shutdown) {
      session_events.push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                               .timestamp_ns = epoch_nanos(),
                                               .event_type = "receiver_shutdown",
                                               .detail = "replay_or_injection_suspected",
                                               .count = shutdown_threshold_});
    }
    return shutdown;
  }

private:
  struct PendingRadioMessage {
    std::vector<std::uint8_t> payload;
    std::chrono::steady_clock::time_point received_steady;
    std::uint64_t received_unix_nanos = 0;
    std::uint8_t bank = 0;
    std::uint8_t symbol = 0;
    std::uint64_t base_price_units = 0;
    std::uint64_t reconstructed_price_units = 0;
  };

  struct CanonicalMessage {
    std::vector<std::uint8_t> payload;
    std::chrono::steady_clock::time_point received_steady;
  };

  template <typename Container>
  static typename Container::iterator find_payload(Container& container,
                                                   const std::vector<std::uint8_t>& payload) {
    return std::find_if(container.begin(), container.end(), [&](const auto& entry) {
      return entry.payload == payload;
    });
  }

  void prune_canonical_locked(std::chrono::steady_clock::time_point now) {
    while (!canonical_.empty() && now - canonical_.front().received_steady > timeout_ * 2) {
      canonical_.pop_front();
    }
  }

  void fill_price_snapshot(PendingRadioMessage& pending) const {
    if (pending.payload.size() >= 1U) {
      pending.bank = pending.payload[0];
    }
    if (pending.payload.size() >= 2U) {
      pending.symbol = pending.payload[1];
    }
    const auto decoded = goblin_cannon::decode_bank_symbol_integer(std::span<const std::uint8_t>(pending.payload));
    if (!decoded.has_value() || !goblin_cannon::is_market_symbol_byte(decoded->symbol) || !control_) {
      return;
    }
    const auto prices = control_->bank_prices_units(decoded->bank);
    if (!prices.has_value()) {
      return;
    }
    pending.bank = decoded->bank;
    pending.symbol = decoded->symbol;
    pending.base_price_units = (*prices)[goblin_cannon::market_symbol_to_index(decoded->symbol)];
    pending.reconstructed_price_units = checked_add_price_delta(pending.base_price_units, decoded->value);
  }

  std::shared_ptr<goblin_cannon::ReceiverControlState> control_;
  std::chrono::milliseconds timeout_;
  std::chrono::milliseconds bad_window_;
  std::uint64_t shutdown_threshold_ = 0;
  std::mutex mutex_;
  std::deque<PendingRadioMessage> pending_radio_;
  std::deque<CanonicalMessage> canonical_;
  std::deque<std::chrono::steady_clock::time_point> bad_message_times_;
};

class ReceiverMessageObserver final : public goblin_cannon::DelimitedMessageObserver {
public:
  ReceiverMessageObserver(goblin_cannon::QuotePacketEmitter& quote_emitter,
                          std::shared_ptr<ReceiverSessionEventQueue> session_events,
                          std::shared_ptr<CanonicalRadioMessageVerifier> verifier)
      : quote_emitter_(quote_emitter),
        session_events_(std::move(session_events)),
        verifier_(std::move(verifier)) {}

  void on_delimited_message(const goblin_cannon::DelimitedMessage& message) override {
    if (verifier_) {
      verifier_->note_radio_message(message);
    }
    if (message.bytes.size() >= 2U && goblin_cannon::is_client_symbol_byte(message.bytes[1])) {
      session_events_->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::client_message,
                                                 .timestamp_ns = epoch_nanos(),
                                                 .client_id = goblin_cannon::client_symbol_to_id(message.bytes[1]),
                                                 .payload = message.bytes});
      return;
    }
    quote_emitter_.on_delimited_message(message);
  }

private:
  goblin_cannon::QuotePacketEmitter& quote_emitter_;
  std::shared_ptr<ReceiverSessionEventQueue> session_events_;
  std::shared_ptr<CanonicalRadioMessageVerifier> verifier_;
};

void receiver_session_loop(std::shared_ptr<goblin_cannon::ReceiverControlState> control,
                           std::shared_ptr<ReceiverSessionEventQueue> session_events,
                           std::shared_ptr<CanonicalRadioMessageVerifier> verifier,
                           std::string transmitter_address,
                           std::uint8_t client_id) {
  namespace pb = ::goblin_cannon::control::v1;
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
      } else if (message.has_canonical_messages()) {
        const auto& batch = message.canonical_messages();
        for (const auto& payload : batch.payload()) {
          verifier->note_canonical_message(std::span<const std::uint8_t>(
              reinterpret_cast<const std::uint8_t*>(payload.data()),
              payload.size()));
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
      if (client_id >= goblin_cannon::Clients) {
        throw std::invalid_argument("client-id must be in [0, " +
                                    std::to_string(goblin_cannon::Clients - 1U) +
                                    "]");
      }
      args.client_id = static_cast<std::uint8_t>(client_id);
    } else if (key == "--sample-format") {
      args.sample_format = radio_example::parse_sample_format(value);
    } else if (key == "--chunk-samples") {
      args.chunk_samples = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--scale") {
      args.scale = std::stof(value);
    } else if (key == "--pipe-capacity-bytes") {
      args.pipe_capacity_bytes = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--iq-trace-interval-ms") {
      args.iq_trace_interval_ms = static_cast<std::uint64_t>(std::stoull(value));
    } else if (key == "--canonical-timeout-ms") {
      args.canonical_timeout_ms = static_cast<std::uint64_t>(std::stoull(value));
    } else if (key == "--bad-message-window-ms") {
      args.bad_message_window_ms = static_cast<std::uint64_t>(std::stoull(value));
    } else if (key == "--bad-message-shutdown-threshold") {
      args.bad_message_shutdown_threshold = static_cast<std::uint64_t>(std::stoull(value));
    } else {
      throw std::invalid_argument("unknown argument: " + key);
    }
  }
  if (args.chunk_samples == 0U) {
    throw std::invalid_argument("chunk-samples must be positive");
  }
  if (args.canonical_timeout_ms == 0U || args.bad_message_window_ms == 0U) {
    throw std::invalid_argument("canonical and bad-message windows must be positive");
  }
  return args;
}

} // namespace

int main(int argc, char** argv) {
  using namespace goblin_cannon;

#if defined(__GNUC__) || defined(__clang__)
  if (!__builtin_cpu_supports("avx2") || !__builtin_cpu_supports("fma")) {
    std::cerr << "radio_receiver requires a CPU with AVX2 + FMA (Haswell or newer).\n";
    return 1;
  }
  const bool has_avx512 = __builtin_cpu_supports("avx512f") &&
                          __builtin_cpu_supports("avx512dq") &&
                          __builtin_cpu_supports("avx512bw") &&
                          __builtin_cpu_supports("avx512vl");
  std::cout << "radio_receiver demapper ISA: "
            << (has_avx512 ? "avx-512" : "avx2+fma") << '\n';
#endif

  radio_example::prepare_realtime_process("radio_receiver");

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
    auto quote_sink_inner = make_quote_packet_sink(quote_config);
    auto quote_sink = std::shared_ptr<QuotePacketSink>(std::make_shared<AsyncQuotePacketSink>(quote_sink_inner));
    auto canonical_verifier = std::make_shared<CanonicalRadioMessageVerifier>(
        receiver_control,
        std::chrono::milliseconds(args.canonical_timeout_ms),
        std::chrono::milliseconds(args.bad_message_window_ms),
        args.bad_message_shutdown_threshold);

    ControlledRealtimeReceiver receiver(receiver_control, rx_messages);
    QuotePacketEmitter quote_emitter(receiver_control, quote_sink);
    ReceiverMessageObserver message_observer(quote_emitter, session_events, canonical_verifier);
    receiver.set_decoded_message_observer(&message_observer);
    FileIqSource source(args.iq_input, args.sample_format, args.scale, args.pipe_capacity_bytes);

    receiver_server.start();
    std::thread session_thread([&] {
      receiver_session_loop(receiver_control,
                            session_events,
                            canonical_verifier,
                            args.transmitter_control_address,
                            args.client_id);
    });
    std::cout << "receiver gRPC: " << receiver_server.bound_address() << '\n'
              << "transmitter session: " << args.transmitter_control_address << '\n'
              << "client id: " << static_cast<unsigned>(args.client_id) << '\n'
              << "IQ input: " << args.iq_input << '\n'
              << "quote UDP: " << args.quote_destination_ip << ':' << args.quote_destination_port << '\n'
              << "canonical timeout: " << args.canonical_timeout_ms << " ms"
              << " bad shutdown threshold: " << args.bad_message_shutdown_threshold << '\n';

    std::vector<Complex> samples(args.chunk_samples);
    std::uint64_t decoded_messages = 0;
    std::uint64_t consumed_samples = 0;
    auto last_iq_trace = std::chrono::steady_clock::now();
    auto last_canonical_sweep = std::chrono::steady_clock::now();
    // Promote the decode thread to SCHED_FIFO best-effort and pin off the
    // gRPC/session/UDP-egress cores.
    radio_example::promote_to_realtime("radio_receiver.audio", 50, 3);
    try {
      while (running.load()) {
        const auto n = source.read(samples);
        if (n == 0U) {
          if (std::chrono::steady_clock::now() - last_canonical_sweep >= std::chrono::milliseconds(50)) {
            if (canonical_verifier->sweep(*quote_sink, *session_events)) {
              running.store(false);
              break;
            }
            last_canonical_sweep = std::chrono::steady_clock::now();
          }
          // Tight idle; the sender produces a chunk roughly every chunk_samples /
          // sample_rate seconds and we want to wake within microseconds of it.
          std::this_thread::sleep_for(std::chrono::microseconds(50));
          continue;
        }
        const auto result = receiver.push_samples(std::span<const Complex>(samples).first(n));
        consumed_samples += result.consumed_samples;
        if (result.authentication_failures != 0U) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "authentication_failure",
                                                    .count = result.authentication_failures});
        }
        if (result.gap_events != 0U) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "message_gap",
                                                    .count = result.gap_events});
        }
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
        if (std::chrono::steady_clock::now() - last_canonical_sweep >= std::chrono::milliseconds(50)) {
          if (canonical_verifier->sweep(*quote_sink, *session_events)) {
            running.store(false);
            break;
          }
          last_canonical_sweep = std::chrono::steady_clock::now();
        }
        if (args.iq_trace_interval_ms != 0U &&
            std::chrono::steady_clock::now() - last_iq_trace >=
                std::chrono::milliseconds(args.iq_trace_interval_ms)) {
          session_events->push(ReceiverSessionEvent{.type = ReceiverSessionEvent::Type::signal_event,
                                                    .timestamp_ns = epoch_nanos(),
                                                    .event_type = "rx_iq",
                                                    .detail = "readable_bytes",
                                                    .metric = static_cast<double>(source.readable_bytes()),
                                                    .count = consumed_samples});
          last_iq_trace = std::chrono::steady_clock::now();
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
