#include "wbhf_modem/control_server.hpp"
#include "wbhf_modem/quote_udp.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <csignal>
#include <cstdint>
#include <iostream>
#include <memory>
#include <span>
#include <stdexcept>
#include <string>
#include <thread>

namespace {

std::atomic_bool running = true;

void handle_signal(int) {
  running.store(false);
}

wbhf_modem::Modulation parse_modulation(const std::string& value) {
  if (value == "qpsk") {
    return wbhf_modem::Modulation::qpsk;
  }
  if (value == "8psk") {
    return wbhf_modem::Modulation::psk8;
  }
  if (value == "16qam") {
    return wbhf_modem::Modulation::qam16;
  }
  if (value == "64qam") {
    return wbhf_modem::Modulation::qam64;
  }
  if (value == "256qam") {
    return wbhf_modem::Modulation::qam256;
  }
  if (value == "1024qam") {
    return wbhf_modem::Modulation::qam1024;
  }
  throw std::invalid_argument("unknown modulation: " + value);
}

wbhf_modem::RealtimePipelineConfig make_pipeline(wbhf_modem::Modulation modulation,
                                                 double bandwidth_hz) {
  wbhf_modem::RealtimePipelineConfig pipeline;
  pipeline.rf.modem.sample_rate_hz = 48000.0;
  pipeline.rf.modem.bandwidth_hz = bandwidth_hz;
  pipeline.rf.modem.symbol_rate_hz = 24000.0;
  pipeline.rf.modem.modulation = modulation;
  pipeline.rf.modem.rrc_rolloff = 0.25;
  pipeline.rf.modem.filter_span_symbols = 8;
  pipeline.rf.modem.receiver_oversampling = 8;
  pipeline.rf.expected_schedule_epoch = 1;
  pipeline.rf.acquisition_sequence = wbhf_modem::make_default_qpsk_sequence(64, 0x12345678U);
  pipeline.rf.equalizer_training_sequence = wbhf_modem::make_default_qpsk_sequence(64, 0x87654321U);
  pipeline.rf.pilot_sequence = {0, 1, 2, 3};
  pipeline.rf.symbols_per_frame = 64;
  pipeline.rf.pilot_interval_symbols = 32;
  pipeline.rf.header_repetition = 3;
  pipeline.convolutional = wbhf_modem::PuncturedConvolutionalCodeConfig::rate_1_2();
  pipeline.sync_timestamp.enabled = false;
  pipeline.frame_counter_start = 1;
  for (std::size_t i = 0; i < pipeline.aes_key.bytes.size(); ++i) {
    pipeline.aes_key.bytes[i] = static_cast<std::uint8_t>(0x41U + i * 17U);
  }
  return pipeline;
}

struct Args {
  std::string receiver_address = "127.0.0.1:50051";
  std::string transmitter_address = "127.0.0.1:50052";
  std::string quote_destination_ip = "127.0.0.1";
  std::uint16_t quote_destination_port = 9001;
  wbhf_modem::Modulation modulation = wbhf_modem::Modulation::qam64;
  double bandwidth_hz = 48000.0;
};

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
    } else if (key == "--transmitter") {
      args.transmitter_address = value;
    } else if (key == "--quote-destination-ip") {
      args.quote_destination_ip = value;
    } else if (key == "--quote-destination-port") {
      args.quote_destination_port = static_cast<std::uint16_t>(std::stoul(value));
    } else if (key == "--modulation") {
      args.modulation = parse_modulation(value);
    } else if (key == "--bandwidth-hz") {
      args.bandwidth_hz = std::stod(value);
    } else {
      throw std::invalid_argument("unknown argument: " + key);
    }
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
    SpscRingBuffer<DelimitedMessage> rx_messages(4096);
    const auto pipeline = make_pipeline(args.modulation, args.bandwidth_hz);

    auto receiver_control = std::make_shared<ReceiverControlState>(pipeline);
    auto transmitter_control = std::make_shared<TransmitterControlState>(pipeline);

    ReceiverControlServer receiver_server(receiver_control, {.listen_address = args.receiver_address});
    TransmitterControlServer transmitter_server(
        transmitter_control,
        {.listen_address = args.transmitter_address, .transmit_queue = tx_queue});

    QuoteUdpSinkConfig quote_config;
    quote_config.backend = QuoteUdpBackend::kernel_udp;
    quote_config.destination_ip = args.quote_destination_ip;
    quote_config.destination_port = args.quote_destination_port;
    quote_config.source_ip = "0.0.0.0";
    quote_config.source_port = 0;
    auto quote_sink = make_quote_packet_sink(quote_config);

    ControlledRealtimeTransmitter transmitter(transmitter_control, *tx_queue);
    ControlledRealtimeReceiver receiver(receiver_control, rx_messages);
    QuotePacketEmitter quote_emitter(receiver_control, quote_sink);
    receiver.set_decoded_message_observer(&quote_emitter);

    receiver_server.start();
    transmitter_server.start();
    std::cout << "receiver gRPC: " << receiver_server.bound_address() << '\n'
              << "transmitter gRPC: " << transmitter_server.bound_address() << '\n'
              << "quote UDP: " << args.quote_destination_ip << ':' << args.quote_destination_port << '\n';

    std::array<Complex, 2048> samples{};
    std::uint64_t decoded_messages = 0;
    while (running.load()) {
      const auto tx = transmitter.push_samples(samples);
      if (tx.produced_samples == 0U) {
        std::this_thread::sleep_for(std::chrono::milliseconds(1));
        continue;
      }
      (void)receiver.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
      DelimitedMessage message;
      while (rx_messages.try_pop(message)) {
        ++decoded_messages;
      }
    }

    std::cout << "stopping, decoded_messages=" << decoded_messages << '\n';
    transmitter_server.stop();
    receiver_server.stop();
    return 0;
  } catch (const std::exception& exception) {
    std::cerr << "local node error: " << exception.what() << '\n';
    return 1;
  }
}
