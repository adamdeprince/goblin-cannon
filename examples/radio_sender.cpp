#include "radio_common.hpp"

#include "wbhf_modem/accounting.hpp"
#include "wbhf_modem/client_udp.hpp"
#include "wbhf_modem/control_server.hpp"
#include "wbhf_modem/io.hpp"
#include "wbhf_modem/market_data_shm.hpp"
#include "wbhf_modem/symbols.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <memory>
#include <mutex>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>
#include <sstream>
#include <utility>
#include <vector>

namespace {

std::atomic_bool running = true;

void handle_signal(int) {
  running.store(false);
}

struct Args {
  std::string transmitter_address = "127.0.0.1:50052";
  std::string iq_output = "/dev/audio";
  wbhf_modem::SampleFormat sample_format = wbhf_modem::SampleFormat::s16_stereo_iq;
  std::size_t chunk_samples = 256;
  float scale = 0.95F;
  std::filesystem::path log_file = "/tmp/wbhf_transmitter.log";
  std::filesystem::path latency_config_file;
  std::filesystem::path budget_config_file = "config/client_budgets.conf";
  std::filesystem::path client_udp_config_file;
  std::filesystem::path market_shm_path;
  std::size_t log_capacity = 65536;
  std::size_t pipe_capacity_bytes = 4096;
  std::uint32_t market_shm_capacity = 256;
  std::uint32_t market_shm_payload_bytes = 64;
  double pace_sample_rate_hz = 0.0;
  std::uint64_t iq_trace_interval_ms = 1000;
};

const char* event_type_name(wbhf_modem::LogEventType event_type) noexcept {
  switch (event_type) {
  case wbhf_modem::LogEventType::udp_ingress:
    return "udp_ingress";
  case wbhf_modem::LogEventType::udp_decision:
    return "udp_decision";
  case wbhf_modem::LogEventType::transmitter_enqueue:
    return "transmitter_enqueue";
  case wbhf_modem::LogEventType::transmitter_framer:
    return "transmitter_framer";
  case wbhf_modem::LogEventType::receiver_client_message:
    return "receiver_client_message";
  case wbhf_modem::LogEventType::receiver_signal:
    return "receiver_signal";
  case wbhf_modem::LogEventType::iq_transport:
    return "iq_transport";
  case wbhf_modem::LogEventType::budget_refund:
    return "budget_refund";
  }
  return "unknown";
}

const char* status_name(wbhf_modem::BidMessageLogStatus status) noexcept {
  switch (status) {
  case wbhf_modem::BidMessageLogStatus::sent:
    return "sent";
  case wbhf_modem::BidMessageLogStatus::rejected:
    return "rejected";
  case wbhf_modem::BidMessageLogStatus::invalid_message_format:
    return "invalid_message_format";
  case wbhf_modem::BidMessageLogStatus::unauthorized_source:
    return "unauthorized_source";
  case wbhf_modem::BidMessageLogStatus::budget_exhausted:
    return "budget_exhausted";
  case wbhf_modem::BidMessageLogStatus::expired_refunded:
    return "expired_refunded";
  case wbhf_modem::BidMessageLogStatus::delivery_matched:
    return "delivery_matched";
  case wbhf_modem::BidMessageLogStatus::delivery_unmatched:
    return "delivery_unmatched";
  }
  return "unknown";
}

wbhf_modem::ClientUdpStatusCode client_status_code_for_log(wbhf_modem::BidMessageLogStatus status) noexcept {
  switch (status) {
  case wbhf_modem::BidMessageLogStatus::sent:
    return wbhf_modem::ClientUdpStatusCode::message_sent;
  case wbhf_modem::BidMessageLogStatus::rejected:
    return wbhf_modem::ClientUdpStatusCode::insufficient_bid;
  case wbhf_modem::BidMessageLogStatus::invalid_message_format:
    return wbhf_modem::ClientUdpStatusCode::invalid_message_format;
  case wbhf_modem::BidMessageLogStatus::budget_exhausted:
    return wbhf_modem::ClientUdpStatusCode::insufficient_budget;
  case wbhf_modem::BidMessageLogStatus::unauthorized_source:
  case wbhf_modem::BidMessageLogStatus::expired_refunded:
  case wbhf_modem::BidMessageLogStatus::delivery_matched:
  case wbhf_modem::BidMessageLogStatus::delivery_unmatched:
    break;
  }
  return wbhf_modem::ClientUdpStatusCode::invalid_message_format;
}

std::string payload_hex(const std::vector<std::uint8_t>& payload) {
  std::ostringstream out;
  out << std::hex << std::setfill('0');
  for (const auto byte : payload) {
    out << std::setw(2) << static_cast<unsigned>(byte);
  }
  return out.str();
}

std::uint64_t epoch_nanos() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

class SamplePacer {
public:
  explicit SamplePacer(double sample_rate_hz)
      : sample_rate_hz_(sample_rate_hz),
        start_(std::chrono::steady_clock::now()) {}

  void wait_until(std::uint64_t produced_samples) {
    if (sample_rate_hz_ <= 0.0) {
      return;
    }
    const auto elapsed_ns = static_cast<std::int64_t>(
        (static_cast<long double>(produced_samples) * 1'000'000'000.0L) /
        static_cast<long double>(sample_rate_hz_));
    const auto target = start_ + std::chrono::nanoseconds(elapsed_ns);
    const auto now = std::chrono::steady_clock::now();
    if (target > now) {
      std::this_thread::sleep_until(target);
    } else if (now - target > std::chrono::milliseconds(100)) {
      start_ = now - std::chrono::nanoseconds(elapsed_ns);
    }
  }

private:
  double sample_rate_hz_ = 0.0;
  std::chrono::steady_clock::time_point start_;
};

class TransmitFramerTraceObserver final : public wbhf_modem::DelimitedMessageObserver {
public:
  TransmitFramerTraceObserver(std::shared_ptr<wbhf_modem::SpscRingBuffer<wbhf_modem::BidMessageLogRecord>> log_queue,
                              std::shared_ptr<std::mutex> log_queue_mutex)
      : log_queue_(std::move(log_queue)),
        log_queue_mutex_(std::move(log_queue_mutex)) {}

  void on_delimited_message(const wbhf_modem::DelimitedMessage& message) override {
    wbhf_modem::BidMessageLogRecord record;
    record.event_type = wbhf_modem::LogEventType::transmitter_framer;
    record.local_timestamp_ns = epoch_nanos();
    record.payload = message.bytes;
    record.status = wbhf_modem::BidMessageLogStatus::sent;
    if (message.bytes.size() >= 2U && wbhf_modem::is_client_symbol_byte(message.bytes[1])) {
      record.client_id = wbhf_modem::client_symbol_to_id(message.bytes[1]);
      record.has_client_id = true;
    }
    std::scoped_lock lock(*log_queue_mutex_);
    (void)log_queue_->try_push(std::move(record));
  }

private:
  std::shared_ptr<wbhf_modem::SpscRingBuffer<wbhf_modem::BidMessageLogRecord>> log_queue_;
  std::shared_ptr<std::mutex> log_queue_mutex_;
};

class ClientBidStatusObserver final : public wbhf_modem::BidMessageLogObserver {
public:
  explicit ClientBidStatusObserver(std::shared_ptr<wbhf_modem::ClientUdpStatusSink> status_sink)
      : status_sink_(std::move(status_sink)) {}

  void on_bid_message_log(const wbhf_modem::BidMessageLogRecord& record) override {
    if (!status_sink_ || record.event_type != wbhf_modem::LogEventType::udp_decision) {
      return;
    }
    if (record.reply_ip.empty() || record.reply_port == 0U) {
      return;
    }
    if (record.status == wbhf_modem::BidMessageLogStatus::unauthorized_source) {
      return;
    }
    status_sink_->send_client_status({.ip = record.reply_ip, .port = record.reply_port},
                                     client_status_code_for_log(record.status),
                                     static_cast<std::uint32_t>(record.bid_price),
                                     static_cast<std::uint32_t>(record.winning_bid_price));
  }

private:
  std::shared_ptr<wbhf_modem::ClientUdpStatusSink> status_sink_;
};

std::string json_escape(std::string_view value) {
  std::ostringstream out;
  for (const auto ch : value) {
    switch (ch) {
    case '\\':
      out << "\\\\";
      break;
    case '"':
      out << "\\\"";
      break;
    case '\n':
      out << "\\n";
      break;
    case '\r':
      out << "\\r";
      break;
    case '\t':
      out << "\\t";
      break;
    default:
      if (static_cast<unsigned char>(ch) < 0x20U) {
        out << "\\u" << std::hex << std::setw(4) << std::setfill('0')
            << static_cast<unsigned>(static_cast<unsigned char>(ch)) << std::dec;
      } else {
        out << ch;
      }
      break;
    }
  }
  return out.str();
}

void log_writer_loop(wbhf_modem::SpscRingBuffer<wbhf_modem::BidMessageLogRecord>& log_queue,
                     const std::filesystem::path& path) {
  std::ofstream out(path, std::ios::app);
  if (!out) {
    std::cerr << "failed to open transmitter log file: " << path << '\n';
    while (running.load()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
    return;
  }
  std::size_t records_since_flush = 0;
  constexpr std::size_t flush_batch = 64;
  while (running.load() || !log_queue.empty()) {
    wbhf_modem::BidMessageLogRecord record;
    if (!log_queue.try_pop(record)) {
      if (records_since_flush != 0U) {
        out.flush();
        records_since_flush = 0;
      }
      std::this_thread::sleep_for(std::chrono::microseconds(200));
      continue;
    }
    const auto ts = record.local_timestamp_ns == 0U ? epoch_nanos() : record.local_timestamp_ns;
    out << "{\"ts_ns\":" << ts
        << ",\"event\":\"" << event_type_name(record.event_type) << "\""
        << ",\"status\":\"" << status_name(record.status) << "\""
        << ",\"payload_hex\":\"" << payload_hex(record.payload) << "\"";
    if (!record.raw_payload.empty()) {
      out << ",\"raw_payload_hex\":\"" << payload_hex(record.raw_payload) << "\"";
    }
    out << ",\"bid_cents\":" << record.bid_price
        << ",\"winning_bid_cents\":" << record.winning_bid_price;
    if (record.has_client_id) {
      out << ",\"client_id\":" << static_cast<unsigned>(record.client_id);
    }
    if (!record.reply_ip.empty()) {
      out << ",\"source_ip\":\"" << json_escape(record.reply_ip) << "\""
          << ",\"source_port\":" << record.reply_port;
    }
    if (record.receiver_timestamp_ns != 0U) {
      out << ",\"receiver_ts_ns\":" << record.receiver_timestamp_ns;
    }
    if (record.expected_latency_ns != 0U) {
      out << ",\"expected_latency_ns\":" << record.expected_latency_ns;
    }
    if (record.observed_latency_ns != 0U) {
      out << ",\"observed_latency_ns\":" << record.observed_latency_ns;
    }
    if (record.remaining_budget_cents != 0U) {
      out << ",\"remaining_budget_cents\":" << record.remaining_budget_cents;
    }
    if (record.matched_timestamp_ns != 0U) {
      out << ",\"matched_ts_ns\":" << record.matched_timestamp_ns;
    }
    if (!record.event_name.empty()) {
      out << ",\"event_name\":\"" << json_escape(record.event_name) << "\"";
    }
    if (!record.detail.empty()) {
      out << ",\"detail\":\"" << json_escape(record.detail) << "\"";
    }
    if (record.metric != 0.0) {
      out << ",\"metric\":" << record.metric;
    }
    if (record.count != 0U) {
      out << ",\"count\":" << record.count;
    }
    out << "}\n";
    ++records_since_flush;
    if (records_since_flush >= flush_batch) {
      out.flush();
      records_since_flush = 0;
    }
  }
  out.flush();
}

Args parse_args(int argc, char** argv) {
  Args args;
  for (int i = 1; i < argc; ++i) {
    const std::string key = argv[i];
    if (i + 1 >= argc) {
      throw std::invalid_argument("missing value for " + key);
    }
    const std::string value = argv[++i];
    if (key == "--transmitter") {
      args.transmitter_address = value;
    } else if (key == "--iq-output") {
      args.iq_output = value;
    } else if (key == "--sample-format") {
      args.sample_format = radio_example::parse_sample_format(value);
    } else if (key == "--chunk-samples") {
      args.chunk_samples = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--scale") {
      args.scale = std::stof(value);
    } else if (key == "--log-file") {
      args.log_file = value;
    } else if (key == "--latency-config") {
      args.latency_config_file = value;
    } else if (key == "--budget-config") {
      args.budget_config_file = value;
    } else if (key == "--client-udp-config") {
      args.client_udp_config_file = value;
    } else if (key == "--market-shm-path") {
      args.market_shm_path = value;
    } else if (key == "--market-shm-capacity") {
      args.market_shm_capacity = static_cast<std::uint32_t>(std::stoul(value));
    } else if (key == "--market-shm-payload-bytes") {
      args.market_shm_payload_bytes = static_cast<std::uint32_t>(std::stoul(value));
    } else if (key == "--log-capacity") {
      args.log_capacity = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--pipe-capacity-bytes") {
      args.pipe_capacity_bytes = static_cast<std::size_t>(std::stoul(value));
    } else if (key == "--pace-sample-rate-hz") {
      args.pace_sample_rate_hz = std::stod(value);
    } else if (key == "--iq-trace-interval-ms") {
      args.iq_trace_interval_ms = static_cast<std::uint64_t>(std::stoull(value));
    } else {
      throw std::invalid_argument("unknown argument: " + key);
    }
  }
  if (args.chunk_samples == 0U) {
    throw std::invalid_argument("chunk-samples must be positive");
  }
  if (args.log_capacity == 0U) {
    throw std::invalid_argument("log-capacity must be positive");
  }
  if (args.market_shm_capacity == 0U) {
    throw std::invalid_argument("market-shm-capacity must be positive");
  }
  if (args.market_shm_payload_bytes < 2U) {
    throw std::invalid_argument("market-shm-payload-bytes must be at least 2");
  }
  if (args.pace_sample_rate_hz < 0.0) {
    throw std::invalid_argument("pace-sample-rate-hz must be non-negative");
  }
  return args;
}

} // namespace

int main(int argc, char** argv) {
  using namespace wbhf_modem;

  radio_example::prepare_realtime_process("radio_sender");

  try {
    const auto args = parse_args(argc, argv);
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    auto tx_queue = std::make_shared<SpscRingBuffer<DelimitedMessage>>(4096);
    auto log_queue = std::make_shared<SpscRingBuffer<BidMessageLogRecord>>(args.log_capacity);
    auto log_queue_mutex = std::make_shared<std::mutex>();
    BidMessageTransmitIntake shared_bid_intake;
    auto client_status_sink = std::make_shared<KernelClientUdpStatusSink>();
    ClientBidStatusObserver client_status_observer(client_status_sink);
    auto transmitter_control = std::make_shared<TransmitterControlState>();
    ClientExpectedLatenciesNs expected_latencies{};
    expected_latencies.fill(5'000'000U);
    if (!args.latency_config_file.empty()) {
      expected_latencies = load_client_expected_latencies_ns_config(args.latency_config_file, 5'000'000U);
    }
    const auto initial_budgets = load_client_budgets_cents_config(args.budget_config_file);
    auto accounting = std::make_shared<ClientBudgetAccounting>(initial_budgets, expected_latencies);
    if (std::filesystem::exists(args.log_file)) {
      accounting->replay_jsonl_log(args.log_file);
    }
    TransmitterControlServer transmitter_server(
        transmitter_control,
        {.listen_address = args.transmitter_address,
         .transmit_queue = tx_queue,
         .log_queue = log_queue,
         .log_queue_mutex = log_queue_mutex,
         .client_expected_latency_ns = expected_latencies,
         .accounting = accounting});
    ControlledRealtimeTransmitter transmitter(transmitter_control, *tx_queue);
    TransmitFramerTraceObserver framer_trace(log_queue, log_queue_mutex);
    transmitter.set_consumed_message_observer(&framer_trace);

    transmitter_server.start();
    std::cout << "transmitter gRPC: " << transmitter_server.bound_address() << '\n'
              << "IQ output: " << args.iq_output << '\n'
              << "transmitter log: " << args.log_file << '\n'
              << "latency config: "
              << (args.latency_config_file.empty() ? std::string("default 5000000 ns")
                                                    : args.latency_config_file.string())
              << '\n'
              << "budget config: " << args.budget_config_file
              << '\n';
    if (!args.market_shm_path.empty()) {
      std::cout << "market data shared memory: " << args.market_shm_path
                << " capacity=" << args.market_shm_capacity
                << " payload_bytes=" << args.market_shm_payload_bytes << '\n';
    }

    FileIqSink sink(args.iq_output, args.sample_format, args.scale, args.pipe_capacity_bytes);
    SamplePacer pacer(args.pace_sample_rate_hz);
    std::thread log_thread([&] {
      log_writer_loop(*log_queue, args.log_file);
    });
    std::thread accounting_thread([&] {
      while (running.load()) {
        const auto refunds = accounting->expire(epoch_nanos());
        if (!refunds.empty()) {
          std::scoped_lock lock(*log_queue_mutex);
          for (const auto& record : refunds) {
            (void)log_queue->try_push(record);
          }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
      }
    });
    std::thread client_udp_thread;
    if (!args.client_udp_config_file.empty()) {
      ClientUdpIngressConfig client_udp_config = load_client_udp_ingress_config(args.client_udp_config_file);
      auto socket = std::make_unique<ClientUdpIngressSocket>(client_udp_config,
                                                             client_status_sink,
                                                             transmitter_control,
                                                             accounting);
      client_udp_thread = std::thread([&, socket = std::move(socket)] mutable {
        while (running.load()) {
          // Wait for a datagram without holding any mutex; kernel wakes us
          // immediately on packet arrival instead of an unconditional 1ms sleep.
          const bool data_ready = socket->wait_for_data(1);
          {
            std::scoped_lock lock(*log_queue_mutex);
            if (data_ready) {
              (void)socket->poll_once(shared_bid_intake, *tx_queue, *log_queue);
            }
            (void)socket->pump_pending(shared_bid_intake, *tx_queue, *log_queue);
          }
        }
      });
    }
    std::thread market_shm_thread;
    if (!args.market_shm_path.empty()) {
      MarketDataShmConfig market_config;
      market_config.path = args.market_shm_path;
      market_config.capacity = args.market_shm_capacity;
      market_config.payload_bytes = args.market_shm_payload_bytes;
      auto consumer = std::make_unique<MarketDataShmConsumer>(market_config);
      market_shm_thread = std::thread([&, consumer = std::move(consumer)] mutable {
        while (running.load()) {
          bool did_work = false;
          {
            std::scoped_lock lock(*log_queue_mutex);
            BidMessage message;
            std::uint32_t drained = 0;
            while (drained < args.market_shm_capacity && consumer->try_pop(message)) {
              const auto result = shared_bid_intake.submit(std::move(message),
                                                           *tx_queue,
                                                           *log_queue,
                                                           &client_status_observer,
                                                           accounting.get());
              did_work = true;
              did_work = did_work || result.transmitted || result.queued_for_arbitration ||
                         result.logged_records != 0U || result.budget_rejected;
              ++drained;
            }
            const auto pumped = shared_bid_intake.pump(*tx_queue,
                                                       *log_queue,
                                                       &client_status_observer,
                                                       accounting.get());
            did_work = did_work || pumped.transmitted || pumped.budget_rejected ||
                       pumped.logged_records != 0U;
          }
          if (!did_work) {
            std::this_thread::sleep_for(std::chrono::microseconds(250));
          }
        }
      });
    }
    std::vector<Complex> samples(args.chunk_samples);
    std::uint64_t produced_samples = 0;
    auto last_iq_trace = std::chrono::steady_clock::now();
    // Promote this (audio/DSP) thread to SCHED_FIFO best-effort once we've
    // finished setup; pin to CPU 2 so it doesn't fight with logger/intake.
    radio_example::promote_to_realtime("radio_sender.audio", 50, 2);
    try {
      while (running.load()) {
        const auto tx = transmitter.push_samples(samples);
        if (tx.produced_samples == 0U) {
          // Startup / restart only: pacer otherwise gates this loop. Tight
          // sleep so we don't add millisecond-class latency before steady state.
          std::this_thread::sleep_for(std::chrono::microseconds(50));
          continue;
        }
        const auto out = std::span<const Complex>(samples).first(tx.produced_samples);
        const auto write_start = std::chrono::steady_clock::now();
        produced_samples += sink.write(out);
        const auto write_stop = std::chrono::steady_clock::now();
        sink.flush();
        pacer.wait_until(produced_samples);

        if (args.iq_trace_interval_ms != 0U &&
            std::chrono::steady_clock::now() - last_iq_trace >=
                std::chrono::milliseconds(args.iq_trace_interval_ms)) {
          BidMessageLogRecord record;
          record.event_type = LogEventType::iq_transport;
          record.local_timestamp_ns = epoch_nanos();
          record.status = BidMessageLogStatus::sent;
          record.event_name = "tx_iq";
          record.count = produced_samples;
          record.metric = static_cast<double>(sink.queued_bytes());
          record.observed_latency_ns = static_cast<std::uint64_t>(
              std::chrono::duration_cast<std::chrono::nanoseconds>(write_stop - write_start).count());
          std::scoped_lock lock(*log_queue_mutex);
          (void)log_queue->try_push(std::move(record));
          last_iq_trace = std::chrono::steady_clock::now();
        }
      }
    } catch (...) {
      running.store(false);
      transmitter_server.stop();
      if (accounting_thread.joinable()) {
        accounting_thread.join();
      }
      if (client_udp_thread.joinable()) {
        client_udp_thread.join();
      }
      if (market_shm_thread.joinable()) {
        market_shm_thread.join();
      }
      if (log_thread.joinable()) {
        log_thread.join();
      }
      throw;
    }

    std::cout << "stopping sender, produced_samples=" << produced_samples << '\n';
    transmitter_server.stop();
    running.store(false);
    if (accounting_thread.joinable()) {
      accounting_thread.join();
    }
    if (client_udp_thread.joinable()) {
      client_udp_thread.join();
    }
    if (market_shm_thread.joinable()) {
      market_shm_thread.join();
    }
    if (log_thread.joinable()) {
      log_thread.join();
    }
    return 0;
  } catch (const std::exception& exception) {
    std::cerr << "radio sender error: " << exception.what() << '\n';
    return 1;
  }
}
