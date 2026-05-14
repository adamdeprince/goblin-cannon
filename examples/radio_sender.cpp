#include "radio_common.hpp"

#include "wbhf_modem/accounting.hpp"
#include "wbhf_modem/client_udp.hpp"
#include "wbhf_modem/control_server.hpp"
#include "wbhf_modem/io.hpp"

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
  std::size_t log_capacity = 65536;
};

const char* event_type_name(wbhf_modem::LogEventType event_type) noexcept {
  switch (event_type) {
  case wbhf_modem::LogEventType::udp_ingress:
    return "udp_ingress";
  case wbhf_modem::LogEventType::udp_decision:
    return "udp_decision";
  case wbhf_modem::LogEventType::transmitter_enqueue:
    return "transmitter_enqueue";
  case wbhf_modem::LogEventType::receiver_client_message:
    return "receiver_client_message";
  case wbhf_modem::LogEventType::receiver_signal:
    return "receiver_signal";
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
  while (running.load() || !log_queue.empty()) {
    wbhf_modem::BidMessageLogRecord record;
    if (!log_queue.try_pop(record)) {
      std::this_thread::sleep_for(std::chrono::milliseconds(1));
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
    out.flush();
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
    } else if (key == "--log-capacity") {
      args.log_capacity = static_cast<std::size_t>(std::stoul(value));
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
  return args;
}

} // namespace

int main(int argc, char** argv) {
  using namespace wbhf_modem;

  try {
    const auto args = parse_args(argc, argv);
    std::signal(SIGINT, handle_signal);
    std::signal(SIGTERM, handle_signal);

    auto tx_queue = std::make_shared<SpscRingBuffer<DelimitedMessage>>(4096);
    auto log_queue = std::make_shared<SpscRingBuffer<BidMessageLogRecord>>(args.log_capacity);
    auto log_queue_mutex = std::make_shared<std::mutex>();
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

    FileIqSink sink(args.iq_output, args.sample_format, args.scale);
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
      auto status_sink = std::make_shared<KernelClientUdpStatusSink>();
      auto socket = std::make_unique<ClientUdpIngressSocket>(client_udp_config,
                                                             status_sink,
                                                             transmitter_control,
                                                             accounting);
      client_udp_thread = std::thread([&, socket = std::move(socket)] mutable {
        BidMessageTransmitIntake intake;
        while (running.load()) {
          const auto received = socket->poll_once(intake, *tx_queue, *log_queue);
          const auto pumped = socket->pump_pending(intake, *tx_queue, *log_queue);
          if (!received.accepted && !received.rejected && !pumped.transmitted && !pumped.budget_rejected) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1));
          }
        }
      });
    }
    std::vector<Complex> samples(args.chunk_samples);
    std::uint64_t produced_samples = 0;
    try {
      while (running.load()) {
        const auto tx = transmitter.push_samples(samples);
        if (tx.produced_samples == 0U) {
          std::this_thread::sleep_for(std::chrono::milliseconds(1));
          continue;
        }
        const auto out = std::span<const Complex>(samples).first(tx.produced_samples);
        produced_samples += sink.write(out);
        sink.flush();
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
    if (log_thread.joinable()) {
      log_thread.join();
    }
    return 0;
  } catch (const std::exception& exception) {
    std::cerr << "radio sender error: " << exception.what() << '\n';
    return 1;
  }
}
