#include "goblin_cannon/control/v1/receiver_control.grpc.pb.h"
#include "goblin_cannon/accounting.hpp"
#include "goblin_cannon/client_udp.hpp"
#include "goblin_cannon/control_server.hpp"
#include "goblin_cannon/crypto.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/io.hpp"
#include "goblin_cannon/market_data_shm.hpp"
#include "goblin_cannon/modem.hpp"
#include "goblin_cannon/message_stream.hpp"
#include "goblin_cannon/quote_udp.hpp"
#include "goblin_cannon/rf_stream.hpp"
#include "goblin_cannon/ring_buffer.hpp"

#include <grpcpp/grpcpp.h>

#include <algorithm>
#include <array>
#include <chrono>
#include <cmath>
#include <cstdlib>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <limits>
#include <memory>
#include <numbers>
#include <optional>
#include <span>
#include <stdexcept>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

using namespace goblin_cannon;

namespace {

namespace pb = ::goblin_cannon::control::v1;

constexpr std::size_t message_test_frame_bytes = 40;

void check(bool condition, const char* message) {
  if (!condition) {
    std::cerr << "test failure: " << message << '\n';
    std::abort();
  }
}

class CapturingQuotePacketSink final : public QuotePacketSink {
public:
  void send_packet(std::span<const std::uint8_t> payload) override {
    raw_packets.emplace_back(payload.begin(), payload.end());
    if (payload.size() == 9U) {
      packets.push_back(QuoteUdpPayload{});
      std::copy(payload.begin(), payload.end(), packets.back().begin());
    } else if (payload.size() == 19U) {
      bad_packets.push_back(BadMessageUdpPayload{});
      std::copy(payload.begin(), payload.end(), bad_packets.back().begin());
    }
  }

  std::vector<QuoteUdpPayload> packets;
  std::vector<BadMessageUdpPayload> bad_packets;
  std::vector<std::vector<std::uint8_t>> raw_packets;
};

class CapturingClientUdpStatusSink final : public ClientUdpStatusSink {
public:
  void send_client_status(const ClientEndpoint& endpoint,
                          ClientUdpStatusCode status,
                          std::uint32_t bid_price,
                          std::uint32_t winning_bid_price) override {
    records.push_back({.endpoint = endpoint,
                       .status = status,
                       .bid_price = bid_price,
                       .winning_bid_price = winning_bid_price});
  }

  struct Record {
    ClientEndpoint endpoint;
    ClientUdpStatusCode status = ClientUdpStatusCode::message_sent;
    std::uint32_t bid_price = 0;
    std::uint32_t winning_bid_price = 0;
  };
  std::vector<Record> records;
};

std::uint64_t read_u64_be(std::span<const std::uint8_t, 8> bytes) {
  std::uint64_t value = 0;
  for (const auto byte : bytes) {
    value = (value << 8U) | byte;
  }
  return value;
}

std::uint64_t epoch_nanos_for_test() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

SymbolPermissionMask make_permission_mask(std::initializer_list<std::uint8_t> allowed_symbols) {
  SymbolPermissionMask mask{};
  for (const auto symbol : allowed_symbols) {
    check(is_symbol_byte(symbol), "permission test symbol outside [2,255]");
    const auto index = static_cast<std::size_t>(symbol - symbol_min_byte);
    mask[index / 8U] = static_cast<std::uint8_t>(mask[index / 8U] | (1U << (index % 8U)));
  }
  return mask;
}

SymbolPermissionMask make_default_receiver_permission_mask(std::uint8_t client_id) {
  SymbolPermissionMask mask{};
  for (std::uint16_t symbol = symbol_min_byte; symbol <= market_symbol_max_byte; ++symbol) {
    const auto index = static_cast<std::size_t>(symbol - symbol_min_byte);
    mask[index / 8U] = static_cast<std::uint8_t>(mask[index / 8U] | (1U << (index % 8U)));
  }
  const auto client_symbol = client_id_to_symbol(client_id);
  const auto client_index = static_cast<std::size_t>(client_symbol - symbol_min_byte);
  mask[client_index / 8U] =
      static_cast<std::uint8_t>(mask[client_index / 8U] | (1U << (client_index % 8U)));
  return mask;
}

std::vector<std::uint8_t> make_client_udp_payload(std::uint32_t bid,
                                                  std::span<const std::uint8_t> message) {
  std::vector<std::uint8_t> payload;
  payload.reserve(4U + message.size());
  payload.push_back(static_cast<std::uint8_t>((bid >> 24U) & 0xFFU));
  payload.push_back(static_cast<std::uint8_t>((bid >> 16U) & 0xFFU));
  payload.push_back(static_cast<std::uint8_t>((bid >> 8U) & 0xFFU));
  payload.push_back(static_cast<std::uint8_t>(bid & 0xFFU));
  payload.insert(payload.end(), message.begin(), message.end());
  return payload;
}

void test_constellations() {
  for (const auto modulation :
       {Modulation::qpsk, Modulation::psk8, Modulation::qam16, Modulation::qam64, Modulation::qam256,
        Modulation::qam1024, Modulation::qci16, Modulation::qci64, Modulation::qci256, Modulation::qci1024}) {
    Constellation constellation(modulation);
    const auto bits = bits_per_symbol(modulation);
    std::array<std::uint8_t, max_bits_per_symbol> out{};
    for (std::uint32_t symbol = 0; symbol < constellation.size(); ++symbol) {
      constellation.symbol_to_bits(symbol, std::span<std::uint8_t>(out).first(bits));
      const auto point = constellation.map_bits(std::span<const std::uint8_t>(out).first(bits));
      const auto nearest = constellation.nearest_symbol(point);
      if (nearest != symbol) {
        std::cerr << "constellation failed modulation=" << to_string(modulation)
                  << " symbol=" << symbol << " nearest=" << nearest << '\n';
      }
      check(nearest == symbol, "constellation nearest-symbol round trip failed");
    }
  }
}

void test_qci_radial_constellations() {
  const std::array<std::pair<Modulation, Modulation>, 4> pairs = {{
      {Modulation::qam16, Modulation::qci16},
      {Modulation::qam64, Modulation::qci64},
      {Modulation::qam256, Modulation::qci256},
      {Modulation::qam1024, Modulation::qci1024},
  }};
  for (const auto [qam_mode, qci_mode] : pairs) {
    Constellation qam(qam_mode, ConstellationProfile::square_gray);
    Constellation qci(qci_mode);
    check(qam.size() == qci.size(), "QCI constellation size mismatch");
    check(bits_per_symbol(qam_mode) == bits_per_symbol(qci_mode), "QCI bits-per-symbol mismatch");
    for (std::uint32_t symbol = 0; symbol < qci.size(); ++symbol) {
      const auto qam_point = qam.map_symbol(symbol);
      const auto qci_point = qci.map_symbol(symbol);
      const auto qam_radius = std::hypot(qam_point.real(), qam_point.imag());
      const auto qci_radius = std::hypot(qci_point.real(), qci_point.imag());
      const auto expected_radius = std::sqrt(2.0F) * std::max(std::abs(qam_point.real()),
                                                              std::abs(qam_point.imag()));
      check(std::abs(qci_radius - expected_radius) < 1.0e-5F,
            "QCI radial map radius mismatch");
      check(qci.nearest_symbol(qci_point) == symbol, "QCI nearest-symbol round trip failed");
    }
  }
}

void test_config_validation() {
  ModemConfig cfg;
  cfg.sample_rate_hz = 48000.0;
  cfg.bandwidth_hz = 60000.0;
  bool threw = false;
  try {
    (void)describe(cfg);
  } catch (const std::invalid_argument&) {
    threw = true;
  }
  check(threw, "invalid bandwidth should throw");
}

void test_sample_formats() {
  const std::array<Complex, 3> in = {Complex{0.25F, -0.5F}, Complex{1.0F, -1.0F}, Complex{-0.125F, 0.75F}};
  std::array<std::uint8_t, 12> bytes{};
  std::array<Complex, 3> out{};
  const auto written = encode_samples(in, SampleFormat::sc16_iq, 1.0F, bytes);
  check(written == bytes.size(), "encoded sc16 byte count mismatch");
  const auto read = decode_samples(bytes, SampleFormat::sc16_iq, 1.0F, out);
  check(read == out.size(), "decoded sc16 sample count mismatch");
  for (std::size_t i = 0; i < in.size(); ++i) {
    check(std::abs(in[i].real() - out[i].real()) < 1.0e-4F, "sc16 real round trip mismatch");
    check(std::abs(in[i].imag() - out[i].imag()) < 1.0e-4F, "sc16 imag round trip mismatch");
  }
}

DelimitedMessage make_message(std::uint8_t delimiter, std::size_t body_bytes, std::uint8_t seed) {
  DelimitedMessage message;
  message.bytes.reserve(body_bytes + 1U);
  message.bytes.push_back(delimiter);
  for (std::size_t i = 0; i < body_bytes; ++i) {
    message.bytes.push_back(static_cast<std::uint8_t>(2U + ((seed + i * 17U) % 254U)));
  }
  return message;
}

void test_base254_varuint_and_zigzag() {
  const std::vector<std::uint64_t> unsigned_values = {
      0U,
      1U,
      2U,
      253U,
      254U,
      255U,
      254U * 254U - 1U,
      254U * 254U,
      1234567890123456789ULL,
      std::numeric_limits<std::uint64_t>::max(),
  };

  for (const auto value : unsigned_values) {
    const auto encoded = encode_base254_varuint(value);
    check(!encoded.empty(), "base254 varuint emitted empty encoding");
    for (const auto byte : encoded) {
      check(byte >= 2U, "base254 varuint emitted delimiter byte");
    }
    const auto decoded = decode_base254_varuint(encoded);
    check(decoded.has_value(), "base254 varuint did not decode");
    check(*decoded == value, "base254 varuint round trip mismatch");
    if (encoded.size() > 1U) {
      check(encoded.back() != 2U, "base254 varuint emitted non-canonical high zero");
    }
  }

  const std::vector<std::int64_t> signed_values = {
      0,
      -1,
      1,
      -2,
      2,
      123456789,
      -123456789,
      std::numeric_limits<std::int64_t>::max(),
      std::numeric_limits<std::int64_t>::min(),
  };

  for (const auto value : signed_values) {
    const auto encoded = encode_base254_zigzag(value);
    const auto decoded = decode_base254_zigzag(encoded);
    check(decoded.has_value(), "base254 zigzag did not decode");
    check(*decoded == value, "base254 zigzag round trip mismatch");
  }

  const std::array<std::uint8_t, 1> empty_digit = {0};
  check(!decode_base254_varuint(empty_digit).has_value(), "base254 varuint accepted delimiter byte");
  const std::array<std::uint8_t, 2> noncanonical = {2, 2};
  check(!decode_base254_varuint(noncanonical).has_value(), "base254 varuint accepted non-canonical high zero");
  const std::array<std::uint8_t, 11> overflow = {255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255};
  check(!decode_base254_varuint(overflow).has_value(), "base254 varuint accepted overflowing value");
}

void test_bank_symbol_integer_message_codec() {
  const std::vector<BankSymbolInteger> messages = {
      {.bank = 0, .symbol = 2, .value = 0},
      {.bank = 1, .symbol = 255, .value = -1},
      {.bank = 0, .symbol = 77, .value = 9876543210LL},
      {.bank = 1, .symbol = 128, .value = -9876543210LL},
      {.bank = 0, .symbol = 3, .value = std::numeric_limits<std::int64_t>::min()},
  };

  for (const auto& message : messages) {
    const auto encoded = encode_bank_symbol_integer(message);
    check(encoded.bytes.size() >= 3U, "integer message encoding too short");
    check(encoded.bytes[0] == message.bank, "integer message bank mismatch");
    check(encoded.bytes[1] == message.symbol, "integer message symbol mismatch");
    for (std::size_t i = 1; i < encoded.bytes.size(); ++i) {
      check(encoded.bytes[i] >= 2U, "integer message body emitted delimiter byte");
    }

    const auto decoded = decode_bank_symbol_integer(encoded);
    check(decoded.has_value(), "integer message did not decode");
    check(decoded->bank == message.bank, "integer message decoded bank mismatch");
    check(decoded->symbol == message.symbol, "integer message decoded symbol mismatch");
    check(decoded->value == message.value, "integer message decoded value mismatch");
  }

  const std::array<std::uint8_t, 3> invalid_bank = {2, 2, 2};
  const std::array<std::uint8_t, 3> invalid_symbol = {0, 1, 2};
  const std::array<std::uint8_t, 2> missing_varint = {0, 2};
  check(!decode_bank_symbol_integer(invalid_bank).has_value(), "integer message accepted invalid bank");
  check(!decode_bank_symbol_integer(invalid_symbol).has_value(), "integer message accepted invalid symbol");
  check(!decode_bank_symbol_integer(missing_varint).has_value(), "integer message accepted missing varint");

  bool threw = false;
  try {
    (void)encode_bank_symbol_integer(2, 2, 0);
  } catch (const std::invalid_argument&) {
    threw = true;
  }
  check(threw, "integer message encoder accepted invalid bank");

  threw = false;
  try {
    (void)encode_bank_symbol_integer(0, 1, 0);
  } catch (const std::invalid_argument&) {
    threw = true;
  }
  check(threw, "integer message encoder accepted invalid symbol");
}

std::vector<DelimitedMessage> make_boundary_messages() {
  std::vector<DelimitedMessage> messages;
  std::uint8_t delimiter = 0;
  std::uint8_t seed = 7;
  auto add_total_len = [&](std::size_t total_len) {
    check(total_len >= 2U, "test message must include delimiter and body");
    messages.push_back(make_message(delimiter, total_len - 1U, seed));
    delimiter = static_cast<std::uint8_t>(delimiter ^ 1U);
    seed = static_cast<std::uint8_t>(seed + 29U);
  };

  for (std::size_t i = 0; i < 10; ++i) {
    add_total_len(4);
  }
  add_total_len(3); // Starts at byte 40: previous message terminates at the start of the next frame.

  for (std::size_t i = 0; i < 12; ++i) {
    add_total_len(3);
  }
  add_total_len(4); // Starts at byte 79: delimiter is the last byte of the payload frame.

  for (std::size_t i = 0; i < 9; ++i) {
    add_total_len(3);
  }
  for (std::size_t i = 0; i < 2; ++i) {
    add_total_len(4);
  }
  add_total_len(4); // Starts at byte 118: partial short message crosses the 120-byte frame boundary.
  add_total_len(3);
  return messages;
}

std::vector<Complex> encode_frame(Modulation modulation, std::span<const std::uint8_t> payload) {
  FrameConfig cfg;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = modulation;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.modem.filter_span_symbols = 8;
  cfg.preamble_bytes = 96;
  cfg.carrier.open_threshold = 0.002F;
  cfg.carrier.close_threshold = 0.0005F;
  cfg.carrier.attack_samples = 4;

  FrameEncoder encoder(cfg);
  encoder.start_frame(static_cast<std::uint32_t>(payload.size()));
  std::vector<Complex> samples;
  std::array<Complex, 257> chunk{};
  std::size_t payload_offset = 0;

  for (std::size_t guard = 0; guard < 100000 && encoder.active(); ++guard) {
    FrameEncodeResult r;
    if (payload_offset < payload.size()) {
      r = encoder.push_payload(payload.subspan(payload_offset), chunk);
      payload_offset += r.consumed_payload_bytes;
    } else {
      r = encoder.drain(chunk);
    }
    samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(r.produced_samples));
  }

  check(!encoder.active(), "frame encoder did not complete");
  return samples;
}

void decode_frame(Modulation modulation,
                  std::span<const Complex> samples,
                  std::span<const std::uint8_t> expected,
                  std::uint8_t receiver_oversampling = 1,
                  std::size_t drop_samples = 0) {
  FrameConfig cfg;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = modulation;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.modem.filter_span_symbols = 8;
  cfg.modem.receiver_oversampling = receiver_oversampling;
  cfg.preamble_bytes = 96;
  cfg.carrier.open_threshold = 0.002F;
  cfg.carrier.close_threshold = 0.0005F;
  cfg.carrier.attack_samples = 4;
  cfg.carrier.preroll_samples = 96;

  FrameDecoder decoder(cfg);
  std::vector<std::uint8_t> decoded;
  bool complete = false;
  std::array<std::uint8_t, 9> out{};
  const auto input = samples.subspan(drop_samples);

  for (std::size_t offset = 0; offset < input.size();) {
    const auto n = std::min<std::size_t>(37, input.size() - offset);
    const auto r = decoder.push_samples(input.subspan(offset, n), out);
    offset += r.consumed_samples;
    decoded.insert(decoded.end(), out.begin(), out.begin() + static_cast<std::ptrdiff_t>(r.produced_payload_bytes));
    complete = complete || r.status == FrameStatus::frame_complete;
  }

  if (!complete || decoded != std::vector<std::uint8_t>(expected.begin(), expected.end())) {
    std::cerr << "decode failed for " << to_string(modulation)
              << " oversampling=" << static_cast<int>(receiver_oversampling)
              << " drop_samples=" << drop_samples
              << " complete=" << complete
              << " decoded_size=" << decoded.size()
              << " expected_size=" << expected.size() << '\n';
  }
  check(complete, "frame decoder did not report completion");
  check(decoded == std::vector<std::uint8_t>(expected.begin(), expected.end()), "frame payload mismatch");
}

void test_frame_loopback() {
  const std::string_view text = "hft over hf radio";
  const auto payload = std::span<const std::uint8_t>(
      reinterpret_cast<const std::uint8_t*>(text.data()), text.size());
  for (const auto modulation : {Modulation::qpsk, Modulation::qam64, Modulation::qci64}) {
    const auto samples = encode_frame(modulation, payload);
    check(!samples.empty(), "frame encoder produced no samples");
    decode_frame(modulation, samples, payload);
  }

  const auto samples = encode_frame(Modulation::qam64, payload);
  decode_frame(Modulation::qam64, samples, payload, 2);
  decode_frame(Modulation::qam64, samples, payload, 4);
  decode_frame(Modulation::qam64, samples, payload, 8);
}

void test_qam1024_modem_symbol_loopback() {
  for (const auto modulation : {Modulation::qam1024, Modulation::qci1024}) {
    ModemConfig cfg;
    cfg.sample_rate_hz = 48000.0;
    cfg.bandwidth_hz = 1200.0;
    cfg.modulation = modulation;
    cfg.rrc_rolloff = 0.35;
    cfg.filter_span_symbols = 32;
    cfg.tx_gain = 1.0F;
    cfg.decoder_agc = false;

    Constellation constellation(modulation);
    std::array<std::uint8_t, max_bits_per_symbol> symbol_bits{};
    const std::size_t guard_symbols = cfg.filter_span_symbols * 2U;
    const std::size_t payload_symbols = 96U;
    std::vector<std::uint8_t> bits;
    bits.reserve((payload_symbols + 2U * guard_symbols) * bits_per_symbol(modulation));
    for (std::uint32_t i = 0; i < payload_symbols + 2U * guard_symbols; ++i) {
      const auto in_guard = i < guard_symbols || i >= guard_symbols + payload_symbols;
      const auto symbol = in_guard ? 0U : static_cast<std::uint32_t>((i * 197U + 31U) % 1024U);
      constellation.symbol_to_bits(symbol, std::span<std::uint8_t>(symbol_bits).first(constellation.bits_per_symbol()));
      bits.insert(bits.end(), symbol_bits.begin(), symbol_bits.begin() + static_cast<std::ptrdiff_t>(constellation.bits_per_symbol()));
    }

    Encoder encoder(cfg);
    std::array<Complex, 4096> chunk{};
    std::vector<Complex> samples;
    const auto pushed = encoder.push_bits(bits, chunk);
    check(pushed.consumed == bits.size(), "1024-symbol raw modem did not consume all bits");
    samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(pushed.produced));
    for (;;) {
      const auto drained = encoder.drain(chunk);
      samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(drained.produced));
      if (drained.produced == 0U) {
        break;
      }
    }

    Decoder decoder(cfg);
    std::vector<std::uint8_t> decoded(bits.size() + max_bits_per_symbol * 8U);
    const auto result = decoder.push_samples(samples, decoded);
    const auto compare_begin = guard_symbols * constellation.bits_per_symbol();
    const auto compare_end = compare_begin + payload_symbols * constellation.bits_per_symbol();
    check(result.produced_bits >= compare_end, "1024-symbol raw modem produced too few decoded bits");
    for (std::size_t i = compare_begin; i < compare_end; ++i) {
      check(decoded[i] == bits[i], "1024-symbol raw modem bit mismatch");
    }
  }
}

void test_continuous_token_stream() {
  FrameConfig cfg;
  cfg.continuous_stream = true;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = Modulation::qam64;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.modem.filter_span_symbols = 8;
  cfg.modem.receiver_oversampling = 4;
  cfg.modem.symbol_confidence_threshold = 0.18F;
  cfg.preamble_bytes = 96;
  cfg.carrier.open_threshold = 0.002F;
  cfg.carrier.close_threshold = 0.0005F;
  cfg.carrier.attack_samples = 4;
  cfg.carrier.preroll_samples = 96;

  const std::string_view text = "continuous hf tokens";
  const auto payload = std::span<const std::uint8_t>(
      reinterpret_cast<const std::uint8_t*>(text.data()), text.size());

  FrameEncoder encoder(cfg);
  encoder.start_stream();
  std::vector<Complex> samples;
  std::array<Complex, 211> iq{};
  std::size_t payload_offset = 0;

  for (std::size_t guard = 0; guard < 100000 && (encoder.active() || payload_offset < payload.size()); ++guard) {
    FrameEncodeResult r;
    if (payload_offset < payload.size()) {
      r = encoder.push_tokens(payload.subspan(payload_offset), iq);
      payload_offset += r.consumed_payload_bytes;
    } else {
      r = encoder.drain(iq);
    }
    samples.insert(samples.end(), iq.begin(), iq.begin() + static_cast<std::ptrdiff_t>(r.produced_samples));
  }
  check(!encoder.active(), "continuous stream encoder did not drain for test close");

  FrameDecoder decoder(cfg);
  std::vector<Token> decoded;
  std::array<Token, 5> out{};
  for (std::size_t offset = 0; offset < samples.size() && decoded.size() < payload.size();) {
    const auto n = std::min<std::size_t>(29, samples.size() - offset);
    const auto r = decoder.push_samples(std::span<const Complex>(samples).subspan(offset, n), out);
    offset += r.consumed_samples;
    decoded.insert(decoded.end(), out.begin(), out.begin() + static_cast<std::ptrdiff_t>(r.produced_payload_bytes));
  }

  if (decoded.size() < payload.size()) {
    std::cerr << "continuous decoded_size=" << decoded.size()
              << " expected_size=" << payload.size()
              << " samples=" << samples.size() << '\n';
  }
  check(decoded.size() >= payload.size(), "continuous token stream produced too few tokens");
  bool saw_uncertain = false;
  for (std::size_t i = 0; i < payload.size(); ++i) {
    saw_uncertain = saw_uncertain || !decoded[i].certain;
    if (decoded[i].certain && decoded[i].value != payload[i]) {
      std::cerr << "certain continuous mismatch i=" << i
                << " got=" << static_cast<int>(decoded[i].value)
                << " expected=" << static_cast<int>(payload[i])
                << " confidence=" << decoded[i].confidence << '\n';
    }
    check(!decoded[i].certain || decoded[i].value == payload[i], "certain continuous token value mismatch");
  }
  check(saw_uncertain, "continuous stream should mark low-confidence startup tokens uncertain");
}

void test_uncertain_tokens() {
  const std::string_view text = "erasure beats bad data";
  const auto payload = std::span<const std::uint8_t>(
      reinterpret_cast<const std::uint8_t*>(text.data()), text.size());
  const auto samples = encode_frame(Modulation::qam64, payload);

  FrameConfig cfg;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = Modulation::qam64;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.modem.filter_span_symbols = 8;
  cfg.modem.receiver_oversampling = 4;
  cfg.modem.symbol_confidence_threshold = 1.0F;
  cfg.preamble_bytes = 96;
  cfg.carrier.open_threshold = 0.002F;
  cfg.carrier.close_threshold = 0.0005F;
  cfg.carrier.attack_samples = 4;
  cfg.carrier.preroll_samples = 96;

  FrameDecoder decoder(cfg);
  std::vector<Token> decoded;
  bool complete = false;
  std::array<Token, 7> out{};
  for (std::size_t offset = 0; offset < samples.size();) {
    const auto n = std::min<std::size_t>(31, samples.size() - offset);
    const auto r = decoder.push_samples(std::span<const Complex>(samples).subspan(offset, n), out);
    offset += r.consumed_samples;
    decoded.insert(decoded.end(), out.begin(), out.begin() + static_cast<std::ptrdiff_t>(r.produced_payload_bytes));
    complete = complete || r.status == FrameStatus::frame_complete;
  }

  check(complete, "token decoder did not report frame completion");
  check(decoded.size() == payload.size(), "token decoder payload size mismatch");
  bool saw_uncertain = false;
  for (std::size_t i = 0; i < payload.size(); ++i) {
    check(decoded[i].value == payload[i], "token decoder value mismatch");
    saw_uncertain = saw_uncertain || !decoded[i].certain;
  }
  check(saw_uncertain, "token decoder did not emit an uncertain token at strict threshold");
}

RfStreamConfig make_rf_config() {
  RfStreamConfig cfg;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = Modulation::qam64;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.modem.filter_span_symbols = 8;
  cfg.modem.receiver_oversampling = 1;
  cfg.expected_schedule_epoch = 0x1020304050607080ULL;
  cfg.acquisition_sequence = make_default_qpsk_sequence(64, 0xA5A50001U);
  cfg.equalizer_training_sequence = make_default_qpsk_sequence(32, 0x5A5A0002U);
  cfg.pilot_sequence = {0, 63};
  cfg.symbols_per_frame = 16;
  cfg.pilot_interval_symbols = 8;
  cfg.header_repetition = 3;
  cfg.acquisition_confidence_threshold = 0.25F;
  cfg.pilot_confidence_threshold = 0.08F;
  cfg.symbol_confidence_threshold = 0.08F;
  cfg.acquisition_sidelobe_guard_samples = 48;
  return cfg;
}

std::vector<std::uint32_t> make_rf_symbols(std::size_t count) {
  std::vector<std::uint32_t> symbols;
  symbols.reserve(count);
  for (std::size_t i = 0; i < count; ++i) {
    symbols.push_back(static_cast<std::uint32_t>((i * 17U + 5U) % 64U));
  }
  return symbols;
}

std::vector<Complex> encode_rf_stream(const RfStreamConfig& cfg,
                                      std::uint64_t frame_counter_start,
                                      std::span<const std::uint32_t> payload_symbols) {
  RfStreamEncoder encoder(cfg);
  encoder.start_epoch(frame_counter_start);
  std::vector<Complex> samples;
  std::array<Complex, 193> chunk{};
  std::size_t offset = 0;

  for (std::size_t guard = 0; guard < 100000 && (encoder.active() || offset < payload_symbols.size()); ++guard) {
    RfStreamEncodeResult r;
    if (offset < payload_symbols.size()) {
      r = encoder.push_symbols(payload_symbols.subspan(offset), chunk);
      offset += r.consumed_symbols;
    } else {
      r = encoder.drain(chunk);
    }
    samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(r.produced_samples));
  }

  check(!encoder.active(), "RF stream encoder did not drain for test close");
  return samples;
}

void push_rf_samples(RfStreamReceiver& receiver,
                     std::span<const Complex> samples,
                     std::vector<RfStreamSymbol>& decoded,
                     bool& acquisition_found,
                     bool& header_valid,
                     bool& lock_lost) {
  std::array<RfStreamSymbol, 128> out{};
  for (std::size_t offset = 0; offset < samples.size();) {
    const auto n = std::min<std::size_t>(157, samples.size() - offset);
    const auto r = receiver.push_samples(samples.subspan(offset, n), out);
    offset += r.consumed_samples;
    acquisition_found = acquisition_found || r.acquisition_found;
    header_valid = header_valid || r.header_valid;
    lock_lost = lock_lost || r.lock_lost;
    decoded.insert(decoded.end(), out.begin(), out.begin() + static_cast<std::ptrdiff_t>(r.produced_symbols));
  }
}

void test_rf_acquisition_correlator() {
  const auto cfg = make_rf_config();
  AcquisitionCorrelator correlator(cfg);
  std::vector<Complex> samples(17, Complex{0.0F, 0.0F});
  const auto reference = correlator.reference_samples();
  samples.insert(samples.end(), reference.begin(), reference.end());
  samples.insert(samples.end(), 31, Complex{0.0F, 0.0F});

  const auto result = correlator.scan(samples);
  check(result.found, "RF acquisition correlator did not find reference preamble");
  check(result.sample_index == 17, "RF acquisition correlator returned wrong sample index");
  check(result.peak_metric > 0.95F, "RF acquisition peak metric too low");
  check(result.confidence > 0.90F, "RF acquisition confidence too low");
}

void test_rf_stream_loopback() {
  const auto cfg = make_rf_config();
  const auto payload = make_rf_symbols(48);
  const auto samples = encode_rf_stream(cfg, 7000, payload);

  RfStreamReceiver receiver(cfg);
  std::vector<RfStreamSymbol> decoded;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  push_rf_samples(receiver, samples, decoded, acquisition_found, header_valid, lock_lost);

  check(acquisition_found, "RF stream receiver did not acquire preamble");
  check(header_valid, "RF stream receiver did not validate header");
  check(!lock_lost, "RF stream receiver lost lock in clean loopback");
  check(decoded.size() >= payload.size(), "RF stream receiver produced too few symbols");
  for (std::size_t i = 0; i < payload.size(); ++i) {
    if (decoded[i].value != payload[i]) {
      std::cerr << "RF mismatch i=" << i
                << " got=" << decoded[i].value
                << " expected=" << payload[i]
                << " confidence=" << decoded[i].confidence
                << " certain=" << decoded[i].certain << '\n';
    }
    check(decoded[i].value == payload[i], "RF stream decoded symbol mismatch");
    check(decoded[i].frame_counter == 7000 + (i / cfg.symbols_per_frame), "RF stream frame counter mismatch");
    check(decoded[i].frame_symbol_offset == i % cfg.symbols_per_frame, "RF stream frame offset mismatch");
  }
}

void test_rf_stream_qam1024_header_loopback() {
  auto cfg = make_rf_config();
  cfg.modem.modulation = Modulation::qam1024;
  cfg.pilot_sequence = {0, 1023};
  const std::vector<std::uint32_t> payload;
  const auto samples = encode_rf_stream(cfg, 7100, payload);

  RfStreamReceiver receiver(cfg);
  std::vector<RfStreamSymbol> decoded;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  push_rf_samples(receiver, samples, decoded, acquisition_found, header_valid, lock_lost);

  check(acquisition_found, "QAM1024 RF stream receiver did not acquire preamble");
  check(header_valid, "QAM1024 RF stream receiver did not validate header");
  check(!lock_lost, "QAM1024 RF stream receiver lost lock before payload");
  check(receiver.header().has_value(), "QAM1024 RF stream receiver did not expose validated header");
  check(receiver.header()->modulation == Modulation::qam1024, "QAM1024 RF stream header modulation mismatch");
}

void test_rf_stream_qci1024_header_loopback() {
  auto cfg = make_rf_config();
  cfg.modem.modulation = Modulation::qci1024;
  cfg.pilot_sequence = {0, 1023};
  const std::vector<std::uint32_t> payload;
  const auto samples = encode_rf_stream(cfg, 7200, payload);

  RfStreamReceiver receiver(cfg);
  std::vector<RfStreamSymbol> decoded;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  push_rf_samples(receiver, samples, decoded, acquisition_found, header_valid, lock_lost);

  check(acquisition_found, "QCI1024 RF stream receiver did not acquire preamble");
  check(header_valid, "QCI1024 RF stream receiver did not validate header");
  check(!lock_lost, "QCI1024 RF stream receiver lost lock before payload");
  check(receiver.header().has_value(), "QCI1024 RF stream receiver did not expose validated header");
  check(receiver.header()->modulation == Modulation::qci1024, "QCI1024 RF stream header modulation mismatch");
}

void test_rf_reacquire_after_lock_loss() {
  const auto cfg = make_rf_config();
  const auto first_payload = make_rf_symbols(40);
  const auto second_payload = make_rf_symbols(32);
  const auto first = encode_rf_stream(cfg, 8000, first_payload);
  const auto second = encode_rf_stream(cfg, 9000, second_payload);

  RfStreamReceiver receiver(cfg);
  std::vector<RfStreamSymbol> decoded;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  push_rf_samples(receiver, first, decoded, acquisition_found, header_valid, lock_lost);
  check(acquisition_found, "RF reacquire test did not acquire first stream");
  check(header_valid, "RF reacquire test did not validate first header");
  check(receiver.state() == RfStreamState::locked, "RF receiver not locked before simulated outage");

  std::vector<Complex> outage(4096, Complex{0.0F, 0.0F});
  push_rf_samples(receiver, outage, decoded, acquisition_found, header_valid, lock_lost);
  check(lock_lost, "RF receiver did not report lock loss during outage");
  check(receiver.state() == RfStreamState::search, "RF receiver did not return to acquisition search after lock loss");

  std::vector<RfStreamSymbol> second_decoded;
  bool second_acquired = false;
  bool second_header = false;
  bool second_lock_lost = false;
  push_rf_samples(receiver, second, second_decoded, second_acquired, second_header, second_lock_lost);
  check(second_acquired, "RF receiver did not reacquire second stream");
  check(second_header, "RF receiver did not validate second stream header");
  check(!second_lock_lost, "RF receiver lost lock after reacquisition");
  check(second_decoded.size() >= second_payload.size(), "RF receiver produced too few symbols after reacquisition");
  check(second_decoded.front().frame_counter == 9000, "RF reacquired stream frame counter mismatch");
  for (std::size_t i = 0; i < second_payload.size(); ++i) {
    check(second_decoded[i].value == second_payload[i], "RF reacquired stream symbol mismatch");
  }
}

void test_message_stream_delimiters_across_payload_frames() {
  const auto messages = make_boundary_messages();
  SpscRingBuffer<DelimitedMessage> input(messages.size() + 2U);
  SpscRingBuffer<DelimitedMessage> output(messages.size() + 2U);
  for (const auto& message : messages) {
    check(input.try_push(message), "message stream input push failed");
  }

  MessageStreamFramer framer;
  MessageStreamDeframer deframer;
  std::array<std::uint8_t, message_test_frame_bytes> payload{};
  std::vector<DelimitedMessage> received;

  auto pump_frame = [&] {
    const auto encoded = framer.next_payload_frame(input, payload);
    check(encoded.payload_bytes <= message_test_frame_bytes, "encoded message frame too large");
    const auto decoded = deframer.push_payload_frame(payload, output);
    check(!decoded.output_backpressure, "message deframer hit unexpected backpressure");
    DelimitedMessage out;
    while (output.try_pop(out)) {
      received.push_back(std::move(out));
    }
  };

  pump_frame();
  check(received.size() < messages.size(), "message stream completed too early after first frame");

  pump_frame();
  check(received.size() < messages.size(), "message stream completed too early after second frame");

  pump_frame();
  check(received.size() < messages.size(), "message stream completed too early after third frame");

  for (std::size_t guard = 0; guard < 8U && received.size() < messages.size(); ++guard) {
    pump_frame();
  }

  check(received.size() == messages.size(), "message deframer did not recover all boundary messages");
  for (std::size_t i = 0; i < messages.size(); ++i) {
    check(received[i].bytes == messages[i].bytes, "boundary message changed after frame crossing");
  }
}

void test_message_framer_active_bank_override() {
  SpscRingBuffer<DelimitedMessage> input(4);
  check(input.try_push(make_message(0, 3, 11)), "active-bank framer input push failed");

  MessageStreamFramer framer;
  framer.set_active_bank(1);
  std::array<std::uint8_t, 10> payload{};
  const auto encoded = framer.next_payload_frame(input, payload);

  check(encoded.consumed_messages == 1U, "active-bank framer did not consume message");
  check(encoded.payload_bytes == 8U, "active-bank framer payload size mismatch");
  check(encoded.padding_bytes == 2U, "active-bank framer padding size mismatch");
  check(payload[0] == 1U, "active-bank framer did not override delimiter");
  check(payload[1] >= 2U && payload[2] >= 2U && payload[3] >= 2U,
        "active-bank framer changed message body");
  check(payload[4] >= 2U && payload[5] >= 2U && payload[6] >= 2U && payload[7] >= 2U,
        "active-bank framer emitted delimiter inside CRC trailer");
  check(payload[8] == 1U && payload[9] == 1U, "active-bank framer did not pad with active delimiter");
}

void test_message_crc_trailer_rejects_corruption_and_allows_padding() {
  SpscRingBuffer<DelimitedMessage> input(2);
  SpscRingBuffer<DelimitedMessage> output(2);
  const auto source = make_message(0, 3, 17);
  check(input.try_push(source), "CRC test input push failed");

  MessageStreamFramer framer;
  MessageStreamDeframer deframer;
  std::array<std::uint8_t, 16> payload{};
  const auto encoded = framer.next_payload_frame(input, payload);
  check(encoded.payload_bytes == source.bytes.size() + 4U, "CRC test encoded size mismatch");
  auto decoded = deframer.push_payload_frame(payload, output);
  check(decoded.produced_messages == 1U, "CRC test did not emit verified message");
  DelimitedMessage message;
  check(output.try_pop(message), "CRC test output missing");
  check(message.bytes == source.bytes, "CRC test did not strip trailer");

  SpscRingBuffer<DelimitedMessage> corrupted_output(2);
  MessageStreamDeframer corrupted_deframer;
  payload[2] = payload[2] == 2U ? 3U : 2U;
  decoded = corrupted_deframer.push_payload_frame(payload, corrupted_output);
  check(decoded.produced_messages == 0U, "CRC test emitted corrupted message");
  check(corrupted_output.empty(), "CRC test corrupted output not empty");

  std::array<std::uint8_t, 8> padding{};
  MessageStreamDeframer padding_deframer;
  decoded = padding_deframer.push_payload_frame(padding, corrupted_output);
  check(decoded.produced_messages == 0U && corrupted_output.empty(),
        "CRC test emitted delimiter-only padding as a message");
}

void test_bid_message_transmit_intake() {
  // Simulated channel, deterministic source order. A standing bid is neither
  // transmitted nor billed until the framer claims it.
  auto bid = [](DelimitedMessage message, std::uint64_t price) {
    return BidMessage{.payload = std::move(message.bytes), .bid_price = price};
  };
  BidMessageTransmitIntake intake;
  TransmitMessageQueue queue(1);
  SpscRingBuffer<BidMessageLogRecord> logs(32);
  const auto low = make_message(0, 3, 10);
  const auto high = make_message(1, 1, 20);
  auto result = intake.submit(bid(low,100),queue,logs);
  check(result.queued_for_arbitration && !result.transmitted && logs.empty(),
        "standing candidate was declared sent before consumption");
  result = intake.submit(bid(high,100),queue,logs);
  check(result.pending_bids == 1U && queue.size_approx() == 1U, "auction queue grew beyond one winner");
  DelimitedMessage sent;
  check(queue.try_pop(sent) && sent.bytes == high.bytes, "ready higher bid per wire byte was not selected");
  check(queue.empty(), "displaced auction candidate remained queued");
  BidMessageLogRecord log;
  check(logs.try_pop(log) && log.status == BidMessageLogStatus::rejected && log.payload == low.bytes,
        "displaced bid did not receive a rejection");
  check(logs.try_pop(log) && log.status == BidMessageLogStatus::sent && log.payload == high.bytes,
        "selected bid was not logged on consumption");
  const auto old = encode_bank_symbol_integer(0,2,100);
  const auto fresh = encode_bank_symbol_integer(0,2,99); // Value may fall; time advances.
  (void)intake.submit(bid(old,1000),queue,logs);
  (void)intake.submit(bid(fresh,1),queue,logs);
  check(queue.try_pop(sent) && sent.bytes == fresh.bytes && queue.empty(),
        "superseded high bid displaced a fresher value of the same key");
  // After ownership transfers, a subsequent update belongs to the next airtime
  // decision; it cannot mutate a message already being serialized.
  (void)intake.submit(bid(old,1),queue,logs);
  check(sent.bytes == fresh.bytes, "producer changed an in-flight message");
  check(queue.try_pop(sent) && sent.bytes == old.bytes, "next update was lost");
}

void test_market_data_shared_memory_ring() {
  const auto suffix = std::chrono::steady_clock::now().time_since_epoch().count();
  const auto path = std::filesystem::temp_directory_path() /
                    ("goblin_cannon_market_data_shm_test_" + std::to_string(suffix));
  std::filesystem::remove(path);

  MarketDataShmConfig config;
  config.path = path;
  config.capacity = 2;
  config.payload_bytes = 16;
  MarketDataShmConsumer consumer(config);
  MarketDataShmProducer producer(path);

  const std::array<std::uint8_t, 3> payload = {0, 2, 3};
  check(producer.try_push(payload, 123U), "market shared-memory producer did not push payload");
  BidMessage message;
  check(consumer.try_pop(message), "market shared-memory consumer did not pop payload");
  check(message.payload == std::vector<std::uint8_t>(payload.begin(), payload.end()) &&
            message.bid_price == 123U && !message.has_client_id,
        "market shared-memory payload mismatch");

  const std::array<std::uint8_t, 2> low = {0, 4};
  const std::array<std::uint8_t, 2> high = {1, 5};
  const std::array<std::uint8_t, 2> overflow = {0, 6};
  check(producer.try_push(low, 100U), "market shared-memory low push failed");
  check(producer.try_push(high, 300U), "market shared-memory high push failed");
  check(!producer.try_push(overflow, 1U), "market shared-memory did not reject full ring");
  check(producer.stats().dropped_full == 1U, "market shared-memory full-drop stat mismatch");

  BidMessageTransmitIntake intake;
  TransmitMessageQueue transmit_queue(1);
  SpscRingBuffer<BidMessageLogRecord> log_queue(8);

  while (consumer.try_pop(message)) {
    (void)intake.submit(std::move(message), transmit_queue, log_queue);
  }
  DelimitedMessage transmitted;
  const auto pumped = intake.pump(transmit_queue, log_queue);
  check(pumped.pending_bids == 1U, "market shared-memory auction lost its standing winner");
  check(transmit_queue.try_pop(transmitted), "market shared-memory auction winner missing");
  check(transmitted.bytes == std::vector<std::uint8_t>(high.begin(), high.end()),
        "market shared-memory auction chose wrong winner");

  std::filesystem::remove(path);
}

void test_client_udp_message_handler() {
  check(client_id_to_symbol(0) == 256U - Clients, "client symbol base mismatch");
  check(client_id_to_symbol(Clients - 1U) == 255U, "last client symbol mismatch");
  check(market_symbol_count == total_symbol_count - Clients, "market symbol count mismatch");

  const auto config_path = std::filesystem::temp_directory_path() / "goblin_cannon_client_udp_test.conf";
  {
    std::ofstream out(config_path);
    out << "backend=kernel_udp\n"
        << "listen_ip=0.0.0.0\n"
        << "listen_port=9100\n"
        << "client.3.ip=192.0.2.3\n";
  }
  const auto parsed_config = load_client_udp_ingress_config(config_path);
  check(parsed_config.backend == ClientUdpBackend::kernel_udp, "client UDP config backend mismatch");
  check(parsed_config.listen_port == 9100U, "client UDP config listen port mismatch");
  check(parsed_config.authorized_client_ips[3] == "192.0.2.3", "client UDP config authorized IP mismatch");
  std::filesystem::remove(config_path);

  const auto latency_path = std::filesystem::temp_directory_path() / "goblin_cannon_client_latency_test.conf";
  {
    std::ofstream out(latency_path);
    out << "client.3.expected_latency_ns=123456\n"
        << "4=789\n";
  }
  const auto latencies = load_client_expected_latencies_ns_config(latency_path, 5'000'000U);
  check(latencies[0] == 5'000'000U && latencies[3] == 123456U && latencies[4] == 789U,
        "client latency config parse mismatch");
  std::filesystem::remove(latency_path);

  ClientUdpIngressConfig config;
  config.listen_port = 9100;
  config.authorized_client_ips[3] = "192.0.2.3";
  auto status_sink = std::make_shared<CapturingClientUdpStatusSink>();
  ClientUdpMessageHandler handler(config, status_sink);
  BidMessageTransmitIntake intake;
  TransmitMessageQueue transmit_queue(1);
  SpscRingBuffer<BidMessageLogRecord> log_queue(16);

  const std::array<std::uint8_t, 3> message = {0, 44, 45};
  auto result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.3", .port = 40000},
                                                          .payload = make_client_udp_payload(500, message)},
                                        intake,
                                        transmit_queue,
                                        log_queue);
  check(result.accepted && result.queued_for_arbitration && !result.transmitted, "client UDP handler did not admit a replaceable candidate");
  DelimitedMessage transmitted;
  check(transmit_queue.try_pop(transmitted), "client UDP handler transmit queue empty");
  check(transmitted.bytes.size() == message.size() + 1U, "client UDP transmitted message size mismatch");
  check(transmitted.bytes[0] == 0U, "client UDP transmitted delimiter mismatch");
  check(transmitted.bytes[1] == client_id_to_symbol(3), "client UDP did not map source to client symbol");
  check(transmitted.bytes[2] == 44U && transmitted.bytes[3] == 45U,
        "client UDP changed message body beyond symbol byte");

  BidMessageLogRecord log;
  check(log_queue.try_pop(log), "client UDP ingress log missing");
  check(log.event_type == LogEventType::udp_ingress &&
            log.raw_payload == make_client_udp_payload(500, message) &&
            log.payload == std::vector<std::uint8_t>(message.begin(), message.end()),
        "client UDP ingress log mismatch");
  check(log_queue.try_pop(log), "client UDP sent log missing");
  check(log.status == BidMessageLogStatus::sent &&
            log.event_type == LogEventType::udp_decision &&
            log.bid_price == 500U &&
            log.has_client_id &&
            log.client_id == 3U,
        "client UDP sent log mismatch");
  check(status_sink->records.size() == 1U &&
            status_sink->records[0].status == ClientUdpStatusCode::message_sent &&
            status_sink->records[0].bid_price == 500U,
        "client UDP sent status mismatch");

  const std::array<std::uint8_t, 3> low_message = {1, 50, 51};
  const std::array<std::uint8_t, 2> high_message = {1, 60};
  result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.3", .port = 40000},
                                                     .payload = make_client_udp_payload(300, low_message)},
                                   intake,
                                   transmit_queue,
                                   log_queue);
  check(result.queued_for_arbitration, "client UDP low backed-up bid not held");
  result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.3", .port = 40000},
                                                     .payload = make_client_udp_payload(280, high_message)},
                                   intake,
                                   transmit_queue,
                                   log_queue);
  check(result.queued_for_arbitration, "client UDP high backed-up bid did not replace standing bid");
  const auto pumped = intake.pump(transmit_queue, log_queue, &handler);
  check(pumped.pending_bids == 1U, "client UDP intake lost standing winner before consumption");
  check(transmit_queue.try_pop(transmitted), "client UDP standing winner missing");
  check(transmitted.bytes[1] == client_id_to_symbol(3), "client UDP standing winner client symbol mismatch");

  bool saw_rejected = false;
  bool saw_second_sent = false;
  while (log_queue.try_pop(log)) {
    saw_rejected = saw_rejected || (log.status == BidMessageLogStatus::rejected && log.bid_price == 300U &&
                                    log.winning_bid_price == 280U);
    saw_second_sent = saw_second_sent || (log.status == BidMessageLogStatus::sent && log.bid_price == 280U);
  }
  check(saw_rejected, "client UDP displaced bid was not logged rejected");
  check(saw_second_sent, "client UDP standing winner was not logged sent");
  const auto saw_lost_status = std::any_of(status_sink->records.begin(), status_sink->records.end(), [](const auto& record) {
    return record.status == ClientUdpStatusCode::insufficient_bid &&
           record.bid_price == 300U &&
           record.winning_bid_price == 280U;
  });
  check(saw_lost_status, "client UDP insufficient bid status missing");

  result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.99", .port = 41000},
                                                     .payload = make_client_udp_payload(100, message)},
                                   intake,
                                   transmit_queue,
                                   log_queue);
  check(result.unauthorized && result.rejected, "client UDP unauthorized source not rejected");
  const auto unauthorized_status_count = std::count_if(status_sink->records.begin(), status_sink->records.end(), [](const auto& record) {
    return record.status == ClientUdpStatusCode::unauthorized_source;
  });
  check(unauthorized_status_count == 0U, "client UDP sent status response to unauthorized source");

  const std::array<std::uint8_t, 3> invalid_message = {0, 0, 45};
  result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.3", .port = 40000},
                                                     .payload = make_client_udp_payload(101, invalid_message)},
                                   intake,
                                   transmit_queue,
                                   log_queue);
  check(result.invalid && result.rejected, "client UDP invalid message not rejected");

  const auto saw_invalid_status = std::any_of(status_sink->records.begin(), status_sink->records.end(), [](const auto& record) {
    return record.status == ClientUdpStatusCode::invalid_message_format && record.bid_price == 101U;
  });
  check(saw_invalid_status, "client UDP invalid message status missing");
}

void test_client_budget_accounting() {
  ClientBudgetsCents budgets{};
  budgets.fill(1'000U);
  ClientExpectedLatenciesNs latencies{};
  latencies.fill(5'000'000U);
  ClientBudgetAccounting accounting(budgets, latencies);

  BidMessage message{.payload = {0, client_id_to_symbol(3), 44, 45},
                     .bid_price = 300,
                     .client_id = 3,
                     .has_client_id = true};
  check(accounting.can_afford_bid(message), "accounting did not allow affordable bid");
  const auto reserved = accounting.reserve_sent_bid(message, 10'000'000U);
  check(reserved.accepted && reserved.remaining_budget_cents == 700U,
        "accounting did not reserve sent bid");
  check(accounting.outstanding_count() == 1U, "accounting outstanding count mismatch after reserve");

  const auto delivered = accounting.acknowledge_delivery(message.payload, 3, 15'000'200U);
  check(delivered.matched &&
            delivered.bid_cents == 300U &&
            delivered.matched_timestamp_ns == 10'000'000U &&
            delivered.remaining_budget_cents == 700U,
        "accounting did not match delivery acknowledgement");
  check(accounting.outstanding_count() == 0U, "accounting did not clear delivered outstanding message");

  check(accounting.reserve_sent_bid(message, 20'000'000U).accepted,
        "accounting did not reserve expiring bid");
  const auto refunds = accounting.expire(21'000'000'001U);
  check(refunds.size() == 1U &&
            refunds[0].event_type == LogEventType::budget_refund &&
            refunds[0].status == BidMessageLogStatus::expired_refunded &&
            refunds[0].bid_price == 300U &&
            refunds[0].remaining_budget_cents == 700U,
        "accounting did not refund expired outstanding message");

  const auto budget_path = std::filesystem::temp_directory_path() / "goblin_cannon_client_budget_test.conf";
  {
    std::ofstream out(budget_path);
    out << "client.3.budget_pennies=1234\n"
        << "4=5678\n";
  }
  const auto loaded = load_client_budgets_cents_config(budget_path);
  check(loaded[3] == 1234U && loaded[4] == 5678U, "client budget config parse mismatch");
  std::filesystem::remove(budget_path);

  const auto replay_path = std::filesystem::temp_directory_path() / "goblin_cannon_accounting_replay_test.jsonl";
  {
    std::ofstream out(replay_path);
    out << "{\"ts_ns\":100,\"event\":\"udp_decision\",\"status\":\"sent\","
           "\"payload_hex\":\"00ef2c2d\",\"bid_cents\":300,\"client_id\":3}\n";
  }
  ClientBudgetAccounting replayed(budgets, latencies);
  replayed.replay_jsonl_log(replay_path);
  check(replayed.remaining_budget_cents(3) == 700U &&
            replayed.outstanding_count() == 1U,
        "accounting replay did not reconstruct sent outstanding bid");
  std::filesystem::remove(replay_path);
}

void test_client_udp_budget_rejection() {
  ClientUdpIngressConfig config;
  config.listen_port = 9100;
  config.authorized_client_ips[3] = "192.0.2.3";
  auto status_sink = std::make_shared<CapturingClientUdpStatusSink>();

  ClientBudgetsCents budgets{};
  budgets.fill(0U);
  budgets[3] = 100U;
  ClientExpectedLatenciesNs latencies{};
  latencies.fill(5'000'000U);
  auto accounting = std::make_shared<ClientBudgetAccounting>(budgets, latencies);
  ClientUdpMessageHandler handler(config, status_sink, {}, accounting);
  BidMessageTransmitIntake intake;
  TransmitMessageQueue transmit_queue(1);
  SpscRingBuffer<BidMessageLogRecord> log_queue(8);

  const std::array<std::uint8_t, 2> message = {0, 44};
  const auto result = handler.handle_datagram(ClientUdpDatagram{.source = {.ip = "192.0.2.3", .port = 40000},
                                                                .payload = make_client_udp_payload(500, message)},
                                              intake,
                                              transmit_queue,
                                              log_queue);
  check(result.budget_rejected && !result.transmitted, "client UDP did not reject over-budget bid");
  check(transmit_queue.empty(), "client UDP transmitted over-budget bid");
  const auto saw_budget_status = std::any_of(status_sink->records.begin(), status_sink->records.end(), [](const auto& record) {
    return record.status == ClientUdpStatusCode::insufficient_budget && record.bid_price == 500U;
  });
  check(saw_budget_status, "client UDP did not send insufficient-budget status");

  bool saw_budget_log = false;
  BidMessageLogRecord log;
  while (log_queue.try_pop(log)) {
    saw_budget_log = saw_budget_log ||
                     (log.status == BidMessageLogStatus::budget_exhausted &&
                      log.has_client_id &&
                      log.client_id == 3U);
  }
  check(saw_budget_log, "client UDP did not log budget rejection");
}

void test_quote_udp_config_and_emitter() {
  const auto config_path = std::filesystem::temp_directory_path() / "goblin_cannon_quote_udp_test.conf";
  {
    std::ofstream out(config_path);
    out << "backend=kernel_udp\n"
        << "destination_ip=127.0.0.1\n"
        << "destination_port=9001\n"
        << "source_ip=0.0.0.0\n"
        << "source_port=0\n";
  }

  const auto config = load_quote_udp_sink_config(config_path);
  check(config.backend == QuoteUdpBackend::kernel_udp, "quote UDP config backend mismatch");
  check(config.destination_ip == "127.0.0.1", "quote UDP config destination IP mismatch");
  check(config.destination_port == 9001U, "quote UDP config destination port mismatch");
  const auto bad_payload = make_bad_message_udp_payload(1, 77, 123456U, 123499U);
  check(bad_payload[0] == 0U && bad_payload[1] == 1U && bad_payload[2] == 77U,
        "bad-message UDP payload header mismatch");
  check(read_u64_be(std::span<const std::uint8_t, 8>(bad_payload.data() + 3U, 8U)) == 123456U &&
            read_u64_be(std::span<const std::uint8_t, 8>(bad_payload.data() + 11U, 8U)) == 123499U,
        "bad-message UDP payload prices mismatch");

  auto control = std::make_shared<ReceiverControlState>();
  PriceBank prices{};
  for (std::size_t i = 0; i < prices.size(); ++i) {
    prices[i] = 100'000U + i;
  }
  check(control->update_bank(1, prices) == 1U, "quote emitter bank update failed");

  auto sink = std::make_shared<CapturingQuotePacketSink>();
  QuotePacketEmitter emitter(control, sink);

  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, -42));
  check(sink->packets.empty(), "quote emitter forwarded market message before any bank data");

  emitter.on_delimited_message(encode_bank_symbol_integer(1, 77, -42));

  check(sink->packets.size() == 1U, "quote emitter did not emit one packet");
  check(sink->packets[0][0] == 77U, "quote emitter packet symbol mismatch");
  const auto expected_price = control->price_units(1, 77) - 42U;
  check(read_u64_be(std::span<const std::uint8_t, 8>(sink->packets[0].data() + 1U, 8U)) == expected_price,
        "quote emitter packet price mismatch");

  const auto permissions = make_permission_mask({88});
  check(control->update_permissions(permissions) == 1U, "quote emitter permission update failed");
  emitter.on_delimited_message(encode_bank_symbol_integer(1, 77, -42));
  check(sink->packets.size() == 1U, "quote emitter forwarded denied symbol");

  emitter.on_delimited_message(encode_bank_symbol_integer(1, 88, 7));
  check(sink->packets.size() == 2U && sink->packets[1][0] == 88U, "quote emitter did not forward allowed symbol");

  std::filesystem::remove(config_path);
}

void test_quote_udp_bank_switch_requires_fresh_bank_update() {
  auto control = std::make_shared<ReceiverControlState>();
  PriceBank bank0{};
  PriceBank bank1{};
  for (std::size_t i = 0; i < bank0.size(); ++i) {
    bank0[i] = 200'000U + i;
    bank1[i] = 300'000U + i;
  }

  auto sink = std::make_shared<CapturingQuotePacketSink>();
  QuotePacketEmitter emitter(control, sink);

  check(control->update_bank(0, bank0) == 1U, "bank switch test bank0 update failed");
  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 1U && sink->packets.back()[0] == 77U,
        "bank switch test did not emit active bank0 message");

  emitter.on_delimited_message(encode_bank_symbol_integer(1, 77, 1));
  check(sink->packets.size() == 1U,
        "bank switch test forwarded bank1 before receiving fresh bank1 data");
  check(control->snapshot().active_market_bank == std::optional<std::uint8_t>(0),
        "bank switch test changed active bank before fresh data arrived");

  check(control->update_bank(1, bank1) == 1U, "bank switch test bank1 update failed");
  emitter.on_delimited_message(encode_bank_symbol_integer(1, 77, 1));
  check(sink->packets.size() == 2U && sink->packets.back()[0] == 77U,
        "bank switch test did not recover after late bank1 data");
  check(control->snapshot().active_market_bank == std::optional<std::uint8_t>(1),
        "bank switch test did not activate bank1 after fresh data");

  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 2U,
        "bank switch test forwarded stale switch back to bank0");

  check(control->update_bank(0, bank0) == 2U, "bank switch test second bank0 update failed");
  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 3U && sink->packets.back()[0] == 77U,
        "bank switch test did not recover after late bank0 data");

  emitter.on_delimited_message(encode_bank_symbol_integer(1, client_symbol_base, 1));
  check(sink->packets.size() == 3U,
        "bank switch test forwarded client symbol through quote UDP");
  check(control->snapshot().active_market_bank == std::optional<std::uint8_t>(0),
        "bank switch test client symbol affected market bank interlock");
}

void test_receiver_bank_cache_clear_stops_market_udp() {
  auto control = std::make_shared<ReceiverControlState>();
  PriceBank prices{};
  for (std::size_t i = 0; i < prices.size(); ++i) {
    prices[i] = 400'000U + i;
  }
  check(control->update_bank(0, prices) == 1U, "bank cache clear test bank update failed");

  auto sink = std::make_shared<CapturingQuotePacketSink>();
  QuotePacketEmitter emitter(control, sink);
  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 1U, "bank cache clear test did not emit with fresh bank");

  control->clear_banks();
  check(!control->has_bank(0), "bank cache clear test left bank0 defined");
  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 1U, "bank cache clear test emitted after clearing banks");

  check(control->update_bank(0, prices) == 2U, "bank cache clear test late bank update failed");
  emitter.on_delimited_message(encode_bank_symbol_integer(0, 77, 1));
  check(sink->packets.size() == 2U, "bank cache clear test did not resume after late bank data");
}

void test_receiver_default_client_permissions() {
  ReceiverControlState control;
  const auto client_id = static_cast<std::uint8_t>(7);
  const auto permissions = make_default_receiver_permission_mask(client_id);
  check(control.update_permissions(permissions) == 1U, "default client permission update failed");
  check(control.symbol_allowed(2), "default client permissions denied first market symbol");
  check(control.symbol_allowed(market_symbol_max_byte), "default client permissions denied last market symbol");
  check(control.symbol_allowed(client_id_to_symbol(client_id)), "default client permissions denied own client symbol");
  check(!control.symbol_allowed(client_id_to_symbol(6)), "default client permissions allowed another client symbol");
}

void test_message_deframer_drops_around_erasures() {
  MessageStreamDeframer deframer;
  SpscRingBuffer<DelimitedMessage> output(4);
  SpscRingBuffer<DelimitedMessage> framed_input(1);
  check(framed_input.try_push(DelimitedMessage{.bytes = {1, 7, 8}}), "erasure test framer input push failed");
  MessageStreamFramer framer;
  std::array<std::uint8_t, 8> framed_clear_message{};
  const auto framed = framer.next_payload_frame(framed_input, framed_clear_message);
  check(framed.consumed_messages == 1U && framed.payload_bytes == 7U,
        "erasure test did not frame CRC-protected message");
  std::vector<Token> tokens = {
      {.value = 0, .certain = true, .confidence = 1.0F},
      {.value = 2, .certain = true, .confidence = 1.0F},
      {.value = 3, .certain = true, .confidence = 1.0F},
      {.value = 99, .certain = false, .confidence = 0.0F},
      {.value = 4, .certain = true, .confidence = 1.0F},
      {.value = 5, .certain = true, .confidence = 1.0F},
  };
  for (const auto byte : framed_clear_message) {
    tokens.push_back({.value = byte, .certain = true, .confidence = 1.0F});
  }

  const auto decoded = deframer.push_payload_tokens(tokens, output);
  check(decoded.produced_messages == 1U, "deframer should emit only message with clear post-erasure delimiter");

  DelimitedMessage message;
  check(output.try_pop(message), "deframer did not output post-erasure message");
  const std::vector<std::uint8_t> expected = {1, 7, 8};
  check(message.bytes == expected, "deframer did not drop erased/undelimited text correctly");
  check(output.empty(), "deframer emitted extra message around erasure");
}

void exercise_convolutional_round_trip(PuncturedConvolutionalCodeConfig config) {
  Aes128Key key;
  for (std::size_t i = 0; i < key.bytes.size(); ++i) {
    key.bytes[i] = static_cast<std::uint8_t>(i * 7U + 5U);
  }
  const std::vector<std::uint8_t> payload = {0, 2, 3, 1, 4, 5, 6, 0, 7, 8};
  auto coded = convolutional_encode_bytes(payload, config);
  auto scrambled = aes128_ctr_xor_bits(coded, key);
  auto soft = hard_bits_to_soft(scrambled);
  auto descrambled = aes128_ctr_descramble_soft_bits(soft, key);
  SoftViterbiDecoder decoder(config);
  const auto decoded = decoder.decode_bytes(descrambled, payload.size());
  check(decoded.bytes.size() == payload.size(), "Viterbi decoded byte count mismatch");
  for (std::size_t i = 0; i < payload.size(); ++i) {
    check(decoded.bytes[i].value == payload[i], "Viterbi round trip byte mismatch");
    check(decoded.bytes[i].certain, "Viterbi clean round trip should be certain");
  }

  std::vector<std::uint8_t> stream_payload = payload;
  stream_payload.insert(stream_payload.end(), 16U, 0U);
  auto stream_coded = convolutional_encode_bytes(stream_payload, config);
  auto stream_scrambled = aes128_ctr_xor_bits(stream_coded, key);
  auto stream_soft = hard_bits_to_soft(stream_scrambled);
  auto stream_descrambled = aes128_ctr_descramble_soft_bits(stream_soft, key);
  StreamingSoftViterbiDecoder streaming_decoder(config);
  std::vector<Token> stream_tokens;
  for (std::size_t offset = 0; offset < stream_descrambled.size();) {
    const auto n = std::min<std::size_t>(7U, stream_descrambled.size() - offset);
    auto next = streaming_decoder.push(std::span<const SoftBit>(stream_descrambled).subspan(offset, n));
    stream_tokens.insert(stream_tokens.end(), next.begin(), next.end());
    offset += n;
  }
  check(stream_tokens.size() >= payload.size(), "streaming Viterbi did not emit enough delayed bytes");
  for (std::size_t i = 0; i < payload.size(); ++i) {
    check(stream_tokens[i].value == payload[i], "streaming Viterbi round trip byte mismatch");
    check(stream_tokens[i].certain, "streaming Viterbi clean round trip should be certain");
  }
}

void test_convolutional_viterbi_and_aes_ctr() {
  exercise_convolutional_round_trip(PuncturedConvolutionalCodeConfig::rate_1_2());
  exercise_convolutional_round_trip(PuncturedConvolutionalCodeConfig::rate_2_3());
  exercise_convolutional_round_trip(PuncturedConvolutionalCodeConfig::rate_3_4());

  auto config = PuncturedConvolutionalCodeConfig::rate_1_2();
  Aes128Key key;
  for (std::size_t i = 0; i < key.bytes.size(); ++i) {
    key.bytes[i] = static_cast<std::uint8_t>(i * 11U + 9U);
  }
  const std::vector<std::uint8_t> payload = {0, 2, 3, 4, 1, 5, 6, 7, 0, 8, 9};
  auto coded = convolutional_encode_bytes(payload, config);
  auto scrambled = aes128_ctr_xor_bits(coded, key);
  auto soft = hard_bits_to_soft(scrambled);
  for (std::size_t i = 24; i < 64 && i < soft.size(); ++i) {
    soft[i].certain = false;
    soft[i].confidence = 0.0F;
  }
  auto descrambled = aes128_ctr_descramble_soft_bits(soft, key);
  SoftViterbiDecoder decoder(config);
  const auto decoded = decoder.decode_bytes(descrambled, payload.size());
  const auto saw_uncertain = std::any_of(decoded.bytes.begin(), decoded.bytes.end(), [](const Token& token) {
    return !token.certain;
  });
  check(saw_uncertain, "Viterbi decoder should mark bytes uncertain through erased coded-bit section");
}

void test_realtime_message_pipeline_end_to_end() {
  auto rf_cfg = make_rf_config();
  rf_cfg.symbols_per_frame = 64;
  rf_cfg.pilot_interval_symbols = 32;

  RealtimePipelineConfig pipeline_cfg;
  pipeline_cfg.rf = rf_cfg;
  pipeline_cfg.convolutional = PuncturedConvolutionalCodeConfig::rate_1_2();
  pipeline_cfg.sync_timestamp.enabled = false;
  pipeline_cfg.frame_counter_start = 22000U;
  for (std::size_t i = 0; i < pipeline_cfg.aes_key.bytes.size(); ++i) {
    pipeline_cfg.aes_key.bytes[i] = static_cast<std::uint8_t>(i * 41U + 23U);
  }

  auto messages = make_boundary_messages();
  for (std::size_t i = 0; i < 520; ++i) {
    messages.push_back(make_message(static_cast<std::uint8_t>(i & 1U),
                                    2U + (i & 1U),
                                    static_cast<std::uint8_t>(i * 13U + 31U)));
  }

  SpscRingBuffer<DelimitedMessage> tx_messages(messages.size() + 8U);
  SpscRingBuffer<DelimitedMessage> rx_messages(messages.size() + 8U);
  for (const auto& message : messages) {
    check(tx_messages.try_push(message), "failed to queue realtime message");
  }

  RealtimeTransmitter transmitter(pipeline_cfg, tx_messages);
  RealtimeReceiver receiver(pipeline_cfg, rx_messages);

  std::vector<DelimitedMessage> received;
  std::array<Complex, 2048> samples{};
  for (std::size_t guard = 0; guard < 8000 && received.size() < messages.size(); ++guard) {
    const auto tx = transmitter.push_samples(samples);
    check(tx.produced_samples != 0U, "realtime transmitter stalled");
    const auto rx = receiver.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
    check(!rx.output_backpressure, "realtime receiver hit unexpected output backpressure");

    DelimitedMessage message;
    while (rx_messages.try_pop(message)) {
      received.push_back(std::move(message));
    }
  }

  check(received.size() == messages.size(), "realtime pipeline did not recover all messages across frames");
  for (std::size_t i = 0; i < messages.size(); ++i) {
    check(received[i].bytes == messages[i].bytes, "realtime pipeline message mismatch");
  }
}

RealtimePipelineConfig make_realtime_pipeline_config(bool timestamp_enabled,
                                                     double timestamp_threshold_seconds,
                                                     std::uint64_t frame_counter_start);

void test_realtime_integer_message_pipeline_end_to_end() {
  auto pipeline_cfg = make_realtime_pipeline_config(false, 1.0, 22500U);
  const std::vector<BankSymbolInteger> source = {
      {.bank = 0, .symbol = 2, .value = 0},
      {.bank = 1, .symbol = 9, .value = 17},
      {.bank = 0, .symbol = 254, .value = -18},
      {.bank = 1, .symbol = 255, .value = 1234567890123LL},
      {.bank = 0, .symbol = 33, .value = -1234567890123LL},
      {.bank = 1, .symbol = 44, .value = std::numeric_limits<std::int64_t>::min()},
  };

  SpscRingBuffer<DelimitedMessage> tx_messages(source.size() + 4U);
  SpscRingBuffer<DelimitedMessage> rx_messages(source.size() + 4U);
  for (const auto& message : source) {
    check(tx_messages.try_push(encode_bank_symbol_integer(message)), "failed to queue integer message");
  }

  RealtimeTransmitter transmitter(pipeline_cfg, tx_messages);
  RealtimeReceiver receiver(pipeline_cfg, rx_messages);

  std::vector<DelimitedMessage> received;
  std::array<Complex, 2048> samples{};
  for (std::size_t guard = 0; guard < 3000 && received.size() < source.size(); ++guard) {
    const auto tx = transmitter.push_samples(samples);
    check(tx.produced_samples != 0U, "integer realtime transmitter stalled");
    const auto rx = receiver.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
    check(!rx.output_backpressure, "integer realtime receiver hit unexpected output backpressure");

    DelimitedMessage message;
    while (rx_messages.try_pop(message)) {
      received.push_back(std::move(message));
    }
  }

  check(received.size() == source.size(), "integer realtime pipeline did not recover all messages");
  for (std::size_t i = 0; i < source.size(); ++i) {
    const auto decoded = decode_bank_symbol_integer(received[i]);
    check(decoded.has_value(), "integer realtime message did not decode");
    check(decoded->bank == source[i].bank, "integer realtime bank mismatch");
    check(decoded->symbol == source[i].symbol, "integer realtime symbol mismatch");
    check(decoded->value == source[i].value, "integer realtime value mismatch");
  }
}

RealtimePipelineConfig make_realtime_pipeline_config(bool timestamp_enabled,
                                                     double timestamp_threshold_seconds,
                                                     std::uint64_t frame_counter_start) {
  auto rf_cfg = make_rf_config();
  rf_cfg.symbols_per_frame = 64;
  rf_cfg.pilot_interval_symbols = 32;

  RealtimePipelineConfig pipeline_cfg;
  pipeline_cfg.rf = rf_cfg;
  pipeline_cfg.convolutional = PuncturedConvolutionalCodeConfig::rate_1_2();
  pipeline_cfg.sync_timestamp.enabled = timestamp_enabled;
  pipeline_cfg.sync_timestamp.max_clock_skew_seconds = timestamp_threshold_seconds;
  pipeline_cfg.frame_counter_start = frame_counter_start;
  for (std::size_t i = 0; i < pipeline_cfg.aes_key.bytes.size(); ++i) {
    pipeline_cfg.aes_key.bytes[i] = static_cast<std::uint8_t>(i * 53U + 17U);
  }
  return pipeline_cfg;
}

pb::Modulation to_proto_modulation(Modulation modulation) {
  switch (modulation) {
  case Modulation::qpsk:
    return pb::MODULATION_QPSK;
  case Modulation::psk8:
    return pb::MODULATION_8PSK;
  case Modulation::qam16:
    return pb::MODULATION_16QAM;
  case Modulation::qam64:
    return pb::MODULATION_64QAM;
  case Modulation::qam256:
    return pb::MODULATION_256QAM;
  case Modulation::qam1024:
    return pb::MODULATION_1024QAM;
  case Modulation::qci16:
    return pb::MODULATION_16QCI;
  case Modulation::qci64:
    return pb::MODULATION_64QCI;
  case Modulation::qci256:
    return pb::MODULATION_256QCI;
  case Modulation::qci1024:
    return pb::MODULATION_1024QCI;
  }
  return pb::MODULATION_UNSPECIFIED;
}

pb::RestartRequest make_restart_request(const ReceiverRestartConfig& restart) {
  pb::RestartRequest request;
  const auto& pipeline = restart.pipeline;
  const auto& rf = pipeline.rf;
  request.set_expected_schedule_epoch(rf.expected_schedule_epoch);
  request.set_modulation(to_proto_modulation(rf.modem.modulation));
  request.set_bandwidth_hz(rf.modem.bandwidth_hz);
  request.set_center_frequency_hz(restart.center_frequency_hz);
  request.set_sample_rate_hz(rf.modem.sample_rate_hz);
  if (rf.modem.symbol_rate_hz.has_value()) {
    request.set_symbol_rate_hz(*rf.modem.symbol_rate_hz);
  }
  request.set_receiver_oversampling(rf.modem.receiver_oversampling);
  request.set_symbols_per_frame(rf.symbols_per_frame);
  request.set_pilot_interval_symbols(rf.pilot_interval_symbols);
  request.set_header_repetition(rf.header_repetition);
  for (const auto symbol : rf.acquisition_sequence) {
    request.add_acquisition_sequence(symbol);
  }
  for (const auto symbol : rf.equalizer_training_sequence) {
    request.add_equalizer_training_sequence(symbol);
  }
  for (const auto symbol : rf.pilot_sequence) {
    request.add_pilot_sequence(symbol);
  }
  auto* fec = request.mutable_fec();
  fec->set_constraint_length(pipeline.convolutional.constraint_length);
  fec->set_generator0(pipeline.convolutional.generator0);
  fec->set_generator1(pipeline.convolutional.generator1);
  for (const auto keep : pipeline.convolutional.puncture_pattern) {
    fec->add_puncture_pattern(keep);
  }
  fec->set_decoded_bit_confidence_threshold(pipeline.convolutional.decoded_bit_confidence_threshold);
  request.set_sync_timestamp_enabled(pipeline.sync_timestamp.enabled);
  request.set_sync_timestamp_max_skew_seconds(pipeline.sync_timestamp.max_clock_skew_seconds);
  request.set_acquisition_confidence_threshold(rf.acquisition_confidence_threshold);
  request.set_pilot_confidence_threshold(rf.pilot_confidence_threshold);
  request.set_symbol_confidence_threshold(rf.symbol_confidence_threshold);
  request.set_frame_counter_start(pipeline.frame_counter_start);
  request.set_rrc_rolloff(rf.modem.rrc_rolloff);
  request.set_filter_span_symbols(static_cast<std::uint32_t>(rf.modem.filter_span_symbols));
  request.set_carrier_correction(rf.carrier_correction);
  request.set_adaptive_equalization(rf.adaptive_equalization);
  request.set_sample_clock_recovery(rf.sample_clock_recovery);
  request.set_recursive_equalization(rf.recursive_equalization);
  request.set_equalizer_delay_symbols(rf.equalizer_delay_symbols);
  request.set_compact_header(rf.compact_header);
  request.set_recovery_interval_frames(rf.recovery_interval_frames);
  request.set_fractionally_spaced_equalization(rf.fractionally_spaced_equalization);
  request.set_equalizer_reselect_interval(rf.equalizer_reselect_interval);
  request.set_message_sequence_numbers(pipeline.sequence_numbers);
  request.set_equalizer_feedforward_taps(rf.equalizer_feedforward_taps);
  request.set_equalizer_feedback_taps(rf.equalizer_feedback_taps);
  return request;
}

void test_receiver_control_state_and_restart_receiver() {
  auto pipeline_cfg = make_realtime_pipeline_config(false, 1.0, 24500U);
  ReceiverRestartConfig restart{.pipeline = pipeline_cfg, .center_frequency_hz = 14'200'000.0};
  auto control = std::make_shared<ReceiverControlState>();

  Aes128Key key;
  for (std::size_t i = 0; i < key.bytes.size(); ++i) {
    key.bytes[i] = static_cast<std::uint8_t>(0xA0U + i);
  }
  check(control->update_encryption_key(key) == 1U, "control key generation mismatch");
  const auto active = control->request_restart(restart);
  check(active.generation == 1U, "control restart generation mismatch");
  check(active.pipeline.aes_key.bytes == key.bytes, "control restart did not apply active key");

  PriceBank prices{};
  for (std::size_t i = 0; i < prices.size(); ++i) {
    prices[i] = 10'000U + i;
  }
  check(control->update_bank(1, prices) == 1U, "control bank generation mismatch");
  check(control->price_units(1, 2) == 10'000U, "control bank first symbol price mismatch");
  check(control->price_units(1, market_symbol_max_byte) == 10'000U + control_symbol_count - 1U,
        "control bank last symbol price mismatch");

  SpscRingBuffer<DelimitedMessage> rx_messages(8);
  ControlledRealtimeReceiver off_receiver(rx_messages);
  check(!off_receiver.active(), "default controlled receiver should start off");
  ControlledRealtimeReceiver controlled(control, rx_messages);
  check(controlled.active(), "controlled receiver did not apply pending restart");
  auto quote_sink = std::make_shared<CapturingQuotePacketSink>();
  QuotePacketEmitter quote_emitter(control, quote_sink);
  controlled.set_decoded_message_observer(&quote_emitter);

  SpscRingBuffer<DelimitedMessage> tx_messages(8);
  const auto expected = encode_bank_symbol_integer(1, 77, -42);
  check(tx_messages.try_push(expected), "failed to queue controlled receiver message");
  RealtimeTransmitter transmitter(active.pipeline, tx_messages);

  std::array<Complex, 2048> samples{};
  for (std::size_t guard = 0; guard < 2000 && rx_messages.empty(); ++guard) {
    const auto tx = transmitter.push_samples(samples);
    check(tx.produced_samples != 0U, "controlled transmitter stalled");
    const auto rx = controlled.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
    check(!rx.output_backpressure, "controlled receiver hit output backpressure");
  }

  DelimitedMessage received;
  check(rx_messages.try_pop(received), "controlled receiver did not emit message after restart");
  const auto decoded = decode_bank_symbol_integer(received);
  check(decoded.has_value(), "controlled receiver integer message did not decode");
  check(decoded->bank == 1U && decoded->symbol == 77U && decoded->value == -42,
        "controlled receiver integer message mismatch");
  check(quote_sink->packets.size() == 1U, "controlled receiver quote observer did not emit packet");
  check(quote_sink->packets[0][0] == 77U, "controlled receiver quote packet symbol mismatch");
  check(read_u64_be(std::span<const std::uint8_t, 8>(quote_sink->packets[0].data() + 1U, 8U)) ==
            control->price_units(1, 77) - 42U,
        "controlled receiver quote packet price mismatch");
}

void test_transmitter_control_state_and_use_bank() {
  auto pipeline_cfg = make_realtime_pipeline_config(false, 1.0, 25000U);
  auto control = std::make_shared<TransmitterControlState>();
  SpscRingBuffer<DelimitedMessage> tx_messages(8);
  ControlledRealtimeTransmitter controlled(control, tx_messages);
  check(!controlled.active(), "default controlled transmitter should start off");

  std::array<Complex, 256> cold_samples{};
  const auto cold = controlled.push_samples(cold_samples);
  check(cold.produced_samples == 0U, "off controlled transmitter produced samples");

  PriceBank prices{};
  for (std::size_t i = 0; i < prices.size(); ++i) {
    prices[i] = 20'000U + i;
  }
  check(control->update_bank(1, prices) == 1U, "transmitter bank update generation mismatch");
  check(control->price_units(1, 77) == 20'075U, "transmitter bank price mismatch");
  check(control->use_bank(1).generation == 1U, "transmitter active bank generation mismatch");

  TransmitterRestartConfig restart{.pipeline = pipeline_cfg, .center_frequency_hz = 7'050'000.0};
  const auto active = control->request_restart(restart);
  check(active.generation == 1U, "transmitter restart generation mismatch");

  const auto source = encode_bank_symbol_integer(0, 77, -42);
  check(tx_messages.try_push(source), "failed to queue controlled transmitter message");

  SpscRingBuffer<DelimitedMessage> rx_messages(8);
  RealtimeReceiver receiver(active.pipeline, rx_messages);
  std::array<Complex, 2048> samples{};
  for (std::size_t guard = 0; guard < 3000 && rx_messages.empty(); ++guard) {
    const auto tx = controlled.push_samples(samples);
    check(tx.produced_samples != 0U, "controlled transmitter did not start after restart");
    const auto rx = receiver.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
    check(!rx.output_backpressure, "controlled transmitter receiver hit backpressure");
  }

  DelimitedMessage received;
  check(rx_messages.try_pop(received), "controlled transmitter did not deliver message");
  const auto decoded = decode_bank_symbol_integer(received);
  check(decoded.has_value(), "controlled transmitter message did not decode");
  check(decoded->bank == 1U, "controlled transmitter did not apply UseBank delimiter override");
  check(decoded->symbol == 77U && decoded->value == -42, "controlled transmitter changed message body");
}

void test_receiver_control_grpc_server() {
  auto control = std::make_shared<ReceiverControlState>();
  ReceiverControlServer server(control, {.listen_address = "127.0.0.1:0"});
  server.start();
  check(server.running(), "gRPC control server did not start");

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::ReceiverControl::NewStub(channel);

  Aes128Key key;
  pb::EncryptionKeyUpdate key_request;
  for (std::size_t i = 0; i < key.bytes.size(); ++i) {
    key.bytes[i] = static_cast<std::uint8_t>(0x30U + i);
  }
  key_request.set_aes128_key(reinterpret_cast<const char*>(key.bytes.data()), key.bytes.size());
  pb::ControlAck ack;
  grpc::ClientContext key_context;
  auto status = stub->UpdateEncryptionKey(&key_context, key_request, &ack);
  check(status.ok(), "gRPC key update failed");
  check(ack.ok() && ack.generation() == 1U, "gRPC key update ack mismatch");
  check(control->aes_key().bytes == key.bytes, "gRPC key update state mismatch");

  pb::BankUpdate bank_request;
  bank_request.set_bank(0);
  for (std::uint64_t i = 0; i < control_symbol_count; ++i) {
    bank_request.add_prices_units(500'000U + i);
  }
  grpc::ClientContext bank_context;
  ack.Clear();
  status = stub->UpdateBank(&bank_context, bank_request, &ack);
  check(status.ok(), "gRPC bank update failed");
  check(ack.ok() && ack.generation() == 1U, "gRPC bank update ack mismatch");
  check(control->price_units(0, 2) == 500'000U, "gRPC bank first symbol mismatch");
  check(control->price_units(0, market_symbol_max_byte) == 500'000U + control_symbol_count - 1U,
        "gRPC bank last symbol mismatch");
  pb::BankSnapshot bank_snapshot;
  pb::BankSelect bank_select;
  bank_select.set_bank(0);
  grpc::ClientContext bank_snapshot_context;
  status = stub->GetBank(&bank_snapshot_context, bank_select, &bank_snapshot);
  check(status.ok(), "gRPC receiver GetBank failed");
  check(bank_snapshot.generation() == 1U &&
            bank_snapshot.prices_units_size() == static_cast<int>(control_symbol_count) &&
            bank_snapshot.prices_units(0) == 500'000U,
        "gRPC receiver GetBank snapshot mismatch");

  const auto permissions = make_permission_mask({2, 77, 255});
  pb::PermissionsUpdate permissions_request;
  permissions_request.set_allowed_symbol_mask(reinterpret_cast<const char*>(permissions.data()), permissions.size());
  grpc::ClientContext permissions_context;
  ack.Clear();
  status = stub->Permissions(&permissions_context, permissions_request, &ack);
  check(status.ok(), "gRPC receiver Permissions failed");
  check(ack.ok() && ack.generation() == 1U, "gRPC receiver Permissions ack mismatch");
  check(control->symbol_allowed(2) && control->symbol_allowed(77) && control->symbol_allowed(255),
        "gRPC receiver Permissions did not allow expected symbols");
  check(!control->symbol_allowed(78), "gRPC receiver Permissions allowed masked-out symbol");

  ReceiverRestartConfig restart{.pipeline = make_realtime_pipeline_config(false, 1.0, 26000U),
                                .center_frequency_hz = 7'100'000.0};
  restart.pipeline.rf.modem.modulation = Modulation::qam1024;
  restart.pipeline.rf.modem.sample_rate_hz = 48'000.0;
  restart.pipeline.rf.modem.bandwidth_hz = 48'000.0;
  restart.pipeline.rf.modem.symbol_rate_hz = 24'000.0;
  restart.pipeline.rf.modem.receiver_oversampling = 8;
  restart.pipeline.rf.pilot_sequence = {0, 1023};
  restart.pipeline.rf.carrier_correction = false;
  restart.pipeline.rf.adaptive_equalization = false;
  restart.pipeline.rf.sample_clock_recovery = false;
  restart.pipeline.rf.recursive_equalization = false;
  restart.pipeline.rf.equalizer_delay_symbols = 2;
  restart.pipeline.rf.compact_header = true;
  restart.pipeline.rf.recovery_interval_frames = 16;
  restart.pipeline.rf.fractionally_spaced_equalization = true;
  restart.pipeline.rf.equalizer_reselect_interval = 256;
  restart.pipeline.sequence_numbers = false;
  restart.pipeline.rf.equalizer_feedforward_taps = 5;
  restart.pipeline.rf.equalizer_feedback_taps = 0;
  auto restart_request = make_restart_request(restart);
  grpc::ClientContext restart_context;
  ack.Clear();
  status = stub->Restart(&restart_context, restart_request, &ack);
  check(status.ok(), "gRPC restart failed");
  check(ack.ok() && ack.generation() == 1U, "gRPC restart ack mismatch");
  const auto pending = control->take_pending_restart();
  check(pending.has_value(), "gRPC restart did not schedule pending receiver");
  check(pending->pipeline.rf.compact_header && pending->pipeline.rf.recovery_interval_frames == 16 &&
        pending->pipeline.rf.fractionally_spaced_equalization && pending->pipeline.rf.equalizer_reselect_interval == 256,
        "gRPC restart lost the recovery/equalizer configuration");
  check(pending->center_frequency_hz == restart.center_frequency_hz, "gRPC restart frequency mismatch");
  check(pending->pipeline.rf.modem.modulation == restart.pipeline.rf.modem.modulation,
        "gRPC restart modulation mismatch");
  check(pending->pipeline.rf.modem.bandwidth_hz == restart.pipeline.rf.modem.bandwidth_hz,
        "gRPC restart bandwidth mismatch");
  check(pending->pipeline.rf.modem.bandwidth_hz == 48'000.0,
        "gRPC restart did not preserve 48 kHz bandwidth");
  check(pending->pipeline.rf.modem.symbol_rate_hz.has_value() &&
            *pending->pipeline.rf.modem.symbol_rate_hz == 24'000.0,
        "gRPC restart did not preserve explicit 24 ksym/s symbol rate");
  check(pending->pipeline.rf.modem.receiver_oversampling == 8U,
        "gRPC restart did not preserve 8x receiver oversampling");
  check(!pending->pipeline.rf.carrier_correction && !pending->pipeline.rf.adaptive_equalization &&
            !pending->pipeline.rf.sample_clock_recovery &&
            !pending->pipeline.rf.recursive_equalization && !pending->pipeline.sequence_numbers &&
            pending->pipeline.rf.equalizer_delay_symbols == 2U &&
            pending->pipeline.rf.equalizer_feedforward_taps == 5U &&
            pending->pipeline.rf.equalizer_feedback_taps == 0U,
        "gRPC restart did not preserve explicit tracking settings, including false and zero");
  check(pending->pipeline.convolutional.generator0 == restart.pipeline.convolutional.generator0,
        "gRPC restart FEC generator mismatch");
  check(pending->pipeline.aes_key.bytes == key.bytes, "gRPC restart did not use active AES key");
  check(!control->has_bank(0), "gRPC receiver restart did not clear bank cache");

  auto invalid_tracking = restart_request;
  invalid_tracking.set_equalizer_feedforward_taps(0);
  grpc::ClientContext invalid_tracking_context;
  ack.Clear();
  status = stub->Restart(&invalid_tracking_context, invalid_tracking, &ack);
  check(!status.ok() && status.error_code() == grpc::StatusCode::INVALID_ARGUMENT,
        "gRPC restart accepted zero feedforward taps");
  check(!control->take_pending_restart().has_value(), "invalid tracking settings scheduled a restart");

  auto legacy_restart = restart_request;
  legacy_restart.clear_carrier_correction();
  legacy_restart.clear_adaptive_equalization();
  legacy_restart.clear_sample_clock_recovery();
  legacy_restart.clear_recursive_equalization();
  legacy_restart.clear_equalizer_delay_symbols();
  legacy_restart.clear_compact_header();
  legacy_restart.clear_recovery_interval_frames();
  legacy_restart.clear_fractionally_spaced_equalization();
  legacy_restart.clear_equalizer_reselect_interval();
  legacy_restart.clear_message_sequence_numbers();
  legacy_restart.clear_equalizer_feedforward_taps();
  legacy_restart.clear_equalizer_feedback_taps();
  grpc::ClientContext legacy_restart_context;
  ack.Clear();
  status = stub->Restart(&legacy_restart_context, legacy_restart, &ack);
  check(status.ok(), "gRPC restart rejected a client without tracking fields");
  const auto legacy_pending = control->take_pending_restart();
  check(legacy_pending.has_value() && !legacy_pending->pipeline.rf.compact_header &&
        legacy_pending->pipeline.rf.recovery_interval_frames == 0 &&
        !legacy_pending->pipeline.rf.fractionally_spaced_equalization && legacy_pending->pipeline.rf.equalizer_reselect_interval == 0,
        "omitted recovery fields changed the legacy wire configuration");
  check(legacy_pending.has_value() && legacy_pending->pipeline.rf.carrier_correction &&
            legacy_pending->pipeline.rf.adaptive_equalization &&
            legacy_pending->pipeline.rf.sample_clock_recovery &&
            !legacy_pending->pipeline.rf.recursive_equalization && legacy_pending->pipeline.sequence_numbers &&
            legacy_pending->pipeline.rf.equalizer_delay_symbols == 0U &&
            legacy_pending->pipeline.rf.equalizer_feedforward_taps == 3U &&
            legacy_pending->pipeline.rf.equalizer_feedback_taps == 4U,
        "omitted gRPC tracking fields did not preserve modem defaults");

  pb::BankUpdate bad_bank_request;
  bad_bank_request.set_bank(2);
  grpc::ClientContext bad_bank_context;
  ack.Clear();
  status = stub->UpdateBank(&bad_bank_context, bad_bank_request, &ack);
  check(!status.ok() && status.error_code() == grpc::StatusCode::INVALID_ARGUMENT,
        "gRPC bank update accepted invalid bank");

  pb::PermissionsUpdate bad_permissions_request;
  bad_permissions_request.set_allowed_symbol_mask("short");
  grpc::ClientContext bad_permissions_context;
  ack.Clear();
  status = stub->Permissions(&bad_permissions_context, bad_permissions_request, &ack);
  check(!status.ok() && status.error_code() == grpc::StatusCode::INVALID_ARGUMENT,
        "gRPC receiver Permissions accepted invalid mask size");

  server.stop();
  check(!server.running(), "gRPC control server did not stop");
}

void test_transmitter_control_grpc_server() {
  auto control = std::make_shared<TransmitterControlState>();
  auto transmit_queue = std::make_shared<TransmitMessageQueue>(4);
  TransmitterControlServer server(control, {.listen_address = "127.0.0.1:0", .transmit_queue = transmit_queue});
  server.start();
  check(server.running(), "gRPC transmitter control server did not start");

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::TransmitterControl::NewStub(channel);

  Aes128Key key;
  pb::EncryptionKeyUpdate key_request;
  for (std::size_t i = 0; i < key.bytes.size(); ++i) {
    key.bytes[i] = static_cast<std::uint8_t>(0x50U + i);
  }
  key_request.set_aes128_key(reinterpret_cast<const char*>(key.bytes.data()), key.bytes.size());
  pb::ControlAck ack;
  grpc::ClientContext key_context;
  auto status = stub->UpdateEncryptionKey(&key_context, key_request, &ack);
  check(status.ok(), "gRPC transmitter key update failed");
  check(control->aes_key().bytes == key.bytes, "gRPC transmitter key update state mismatch");

  pb::BankUpdate bank_request;
  bank_request.set_bank(1);
  for (std::uint64_t i = 0; i < control_symbol_count; ++i) {
    bank_request.add_prices_units(600'000U + i);
  }
  grpc::ClientContext bank_context;
  ack.Clear();
  status = stub->UpdateBank(&bank_context, bank_request, &ack);
  check(status.ok(), "gRPC transmitter bank update failed");
  check(control->price_units(1, market_symbol_max_byte) == 600'000U + control_symbol_count - 1U,
        "gRPC transmitter bank state mismatch");
  pb::BankSnapshot bank_snapshot;
  pb::BankSelect bank_select;
  bank_select.set_bank(1);
  grpc::ClientContext bank_snapshot_context;
  status = stub->GetBank(&bank_snapshot_context, bank_select, &bank_snapshot);
  check(status.ok(), "gRPC transmitter GetBank failed");
  check(bank_snapshot.generation() == 1U &&
            bank_snapshot.prices_units_size() == static_cast<int>(control_symbol_count) &&
            bank_snapshot.prices_units(control_symbol_count - 1U) == 600'000U + control_symbol_count - 1U,
        "gRPC transmitter GetBank snapshot mismatch");

  pb::UseBankRequest use_bank;
  use_bank.set_bank(1);
  grpc::ClientContext use_bank_context;
  ack.Clear();
  status = stub->UseBank(&use_bank_context, use_bank, &ack);
  check(status.ok(), "gRPC transmitter UseBank failed");
  check(control->active_bank().bank == 1U, "gRPC transmitter active bank mismatch");

  pb::TransmitMessage transmit_message;
  const std::array<std::uint8_t, 3> payload = {1, 77, 2};
  transmit_message.set_payload(reinterpret_cast<const char*>(payload.data()), payload.size());
  grpc::ClientContext transmit_context;
  ack.Clear();
  status = stub->EnqueueMessage(&transmit_context, transmit_message, &ack);
  check(status.ok() && ack.ok(), "gRPC transmitter EnqueueMessage failed");
  DelimitedMessage queued;
  check(transmit_queue->try_pop(queued) && queued.bytes == std::vector<std::uint8_t>(payload.begin(), payload.end()),
        "gRPC transmitter EnqueueMessage payload mismatch");

  pb::TransmitMessage stale_client_message;
  const std::array<std::uint8_t, 3> client_payload = {1, client_id_to_symbol(0), 2};
  stale_client_message.set_payload(reinterpret_cast<const char*>(client_payload.data()), client_payload.size());
  grpc::ClientContext stale_client_context;
  ack.Clear();
  status = stub->EnqueueMessage(&stale_client_context, stale_client_message, &ack);
  check(!status.ok() && status.error_code() == grpc::StatusCode::FAILED_PRECONDITION,
        "gRPC transmitter accepted stale client-specific message");

  control->register_receiver_client(0);
  grpc::ClientContext live_client_context;
  ack.Clear();
  status = stub->EnqueueMessage(&live_client_context, stale_client_message, &ack);
  check(status.ok() && ack.ok(), "gRPC transmitter rejected live client-specific message");
  check(transmit_queue->try_pop(queued) &&
            queued.bytes == std::vector<std::uint8_t>(client_payload.begin(), client_payload.end()),
        "gRPC transmitter live client-specific payload mismatch");

  ReceiverRestartConfig restart{.pipeline = make_realtime_pipeline_config(false, 1.0, 26500U),
                                .center_frequency_hz = 7'200'000.0};
  restart.pipeline.rf.modem.sample_rate_hz = 48'000.0;
  restart.pipeline.rf.modem.bandwidth_hz = 48'000.0;
  restart.pipeline.rf.modem.symbol_rate_hz = 24'000.0;
  restart.pipeline.rf.modem.receiver_oversampling = 8;
  const auto restart_request = make_restart_request(restart);
  grpc::ClientContext restart_context;
  ack.Clear();
  status = stub->Restart(&restart_context, restart_request, &ack);
  check(status.ok(), "gRPC transmitter restart failed");
  const auto pending = control->take_pending_restart();
  check(pending.has_value(), "gRPC transmitter restart did not schedule pending transmitter");
  check(pending->center_frequency_hz == restart.center_frequency_hz, "gRPC transmitter restart frequency mismatch");
  check(pending->pipeline.rf.modem.bandwidth_hz == 48'000.0 &&
            pending->pipeline.rf.modem.symbol_rate_hz.has_value() &&
            *pending->pipeline.rf.modem.symbol_rate_hz == 24'000.0,
        "gRPC transmitter restart did not preserve 48 kHz bandwidth and explicit symbol rate");
  check(pending->pipeline.rf.modem.receiver_oversampling == 8U,
        "gRPC transmitter restart did not preserve 8x receiver oversampling");
  check(pending->pipeline.aes_key.bytes == key.bytes, "gRPC transmitter restart did not use active AES key");

  pb::UseBankRequest bad_use_bank;
  bad_use_bank.set_bank(2);
  grpc::ClientContext bad_use_bank_context;
  ack.Clear();
  status = stub->UseBank(&bad_use_bank_context, bad_use_bank, &ack);
  check(!status.ok() && status.error_code() == grpc::StatusCode::INVALID_ARGUMENT,
        "gRPC transmitter UseBank accepted invalid bank");

  server.stop();
  check(!server.running(), "gRPC transmitter control server did not stop");
}

void test_transmitter_receiver_session_stream_and_bank_switch() {
  auto control = std::make_shared<TransmitterControlState>();
  auto transmit_queue = std::make_shared<TransmitMessageQueue>(4);
  TransmitterControlServer server(control, {.listen_address = "127.0.0.1:0", .transmit_queue = transmit_queue});
  server.start();

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::TransmitterControl::NewStub(channel);

  pb::BankUpdate bank0;
  bank0.set_bank(0);
  for (std::uint64_t i = 0; i < control_symbol_count; ++i) {
    bank0.add_prices_units(700'000U + i);
  }
  pb::ControlAck ack;
  grpc::ClientContext bank0_context;
  auto status = stub->UpdateBank(&bank0_context, bank0, &ack);
  check(status.ok() && ack.ok(), "session stream test bank0 update failed");

  grpc::ClientContext stream_context;
  stream_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(3));
  auto stream = stub->ReceiverSession(&stream_context);
  pb::ReceiverSessionClientMessage hello;
  hello.mutable_hello()->set_client_id(4);
  check(stream->Write(hello), "session stream test failed to write hello");

  bool saw_bank0 = false;
  bool saw_heartbeat = false;
  for (int i = 0; i < 3 && !(saw_bank0 && saw_heartbeat); ++i) {
    pb::ReceiverSessionServerMessage message;
    check(stream->Read(&message), "session stream test failed before initial messages");
    if (message.has_bank_update()) {
      saw_bank0 = message.bank_update().bank() == 0U &&
                  message.bank_update().generation() == 1U &&
                  message.bank_update().prices_units_size() == static_cast<int>(control_symbol_count) &&
                  message.bank_update().prices_units(0) == 700'000U;
    } else if (message.has_heartbeat()) {
      saw_heartbeat = true;
    }
  }
  check(saw_bank0, "session stream test did not deliver active bank cache first");
  check(saw_heartbeat, "session stream test did not deliver transmitter heartbeat");
  check(control->receiver_client_alive(4), "session stream test did not mark client alive");

  pb::BankUpdate bank1;
  bank1.set_bank(1);
  for (std::uint64_t i = 0; i < control_symbol_count; ++i) {
    bank1.add_prices_units(800'000U + i);
  }
  grpc::ClientContext bank1_context;
  ack.Clear();
  status = stub->UpdateBank(&bank1_context, bank1, &ack);
  check(status.ok() && ack.ok(), "session stream test bank1 update failed");

  pb::ReceiverSessionClientMessage heartbeat;
  heartbeat.mutable_heartbeat()->set_unix_micros(1);
  check(stream->Write(heartbeat), "session stream test failed to write receiver heartbeat");

  bool saw_bank1 = false;
  const auto bank1_deadline = std::chrono::steady_clock::now() + std::chrono::seconds(2);
  while (!saw_bank1 && std::chrono::steady_clock::now() < bank1_deadline) {
    pb::ReceiverSessionServerMessage message;
    check(stream->Read(&message), "session stream test ended before next bank cache");
    if (message.has_bank_update() && message.bank_update().bank() == 1U) {
      saw_bank1 = message.bank_update().generation() == 1U &&
                  message.bank_update().prices_units(0) == 800'000U;
    }
  }
  check(saw_bank1, "session stream test did not deliver next-bank cache");

  grpc::ClientContext switch_context;
  pb::BankSwitchRequest switch_request;
  ack.Clear();
  status = stub->BankSwitch(&switch_context, switch_request, &ack);
  check(status.ok() && ack.ok(), "session stream test bank switch failed");
  check(control->active_bank().bank == 1U, "session stream test did not switch transmitter bank");

  stream->WritesDone();
  (void)stream->Finish();
  server.stop();
}

void test_transmitter_receiver_session_broadcasts_canonical_messages() {
  auto control = std::make_shared<TransmitterControlState>();
  auto canonical = std::make_shared<CanonicalMessageBroadcaster>();
  TransmitterControlServer server(control,
                                  {.listen_address = "127.0.0.1:0",
                                   .canonical_messages = canonical});
  server.start();

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::TransmitterControl::NewStub(channel);

  grpc::ClientContext context_a;
  grpc::ClientContext context_b;
  context_a.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(5));
  context_b.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(5));
  auto stream_a = stub->ReceiverSession(&context_a);
  auto stream_b = stub->ReceiverSession(&context_b);

  pb::ReceiverSessionClientMessage hello_a;
  hello_a.mutable_hello()->set_client_id(1);
  pb::ReceiverSessionClientMessage hello_b;
  hello_b.mutable_hello()->set_client_id(2);
  check(stream_a->Write(hello_a), "canonical broadcast test failed to write hello A");
  check(stream_b->Write(hello_b), "canonical broadcast test failed to write hello B");

  const auto wait_for_heartbeat = [](auto& stream, const char* failure) {
    for (int i = 0; i < 4; ++i) {
      pb::ReceiverSessionServerMessage message;
      check(stream->Read(&message), failure);
      if (message.has_heartbeat()) {
        return;
      }
    }
    check(false, failure);
  };
  wait_for_heartbeat(stream_a, "canonical broadcast test no heartbeat A");
  wait_for_heartbeat(stream_b, "canonical broadcast test no heartbeat B");

  std::vector<DelimitedMessage> expected;
  expected.reserve(130);
  for (std::size_t i = 0; i < 130U; ++i) {
    expected.push_back(make_message(static_cast<std::uint8_t>(i & 1U),
                                    2U,
                                    static_cast<std::uint8_t>(10U + i)));
    canonical->on_delimited_message(expected.back());
  }

  auto read_canonical_payloads = [](auto& stream) {
    std::vector<std::vector<std::uint8_t>> payloads;
    std::size_t largest_batch = 0;
    while (payloads.size() < 130U) {
      pb::ReceiverSessionServerMessage message;
      check(stream->Read(&message), "canonical broadcast test stream ended before payloads");
      if (!message.has_canonical_messages()) {
        continue;
      }
      const auto& batch = message.canonical_messages();
      largest_batch = std::max(largest_batch, static_cast<std::size_t>(batch.payload_size()));
      for (const auto& payload : batch.payload()) {
        payloads.emplace_back(payload.begin(), payload.end());
      }
    }
    check(largest_batch <= 128U, "canonical broadcast test exceeded max batch size");
    return payloads;
  };

  const auto payloads_a = read_canonical_payloads(stream_a);
  const auto payloads_b = read_canonical_payloads(stream_b);
  check(payloads_a.size() == expected.size(), "canonical broadcast test receiver A count mismatch");
  check(payloads_b.size() == expected.size(), "canonical broadcast test receiver B count mismatch");
  for (std::size_t i = 0; i < expected.size(); ++i) {
    check(payloads_a[i] == expected[i].bytes, "canonical broadcast test receiver A payload mismatch");
    check(payloads_b[i] == expected[i].bytes, "canonical broadcast test receiver B payload mismatch");
  }

  stream_a->WritesDone();
  stream_b->WritesDone();
  (void)stream_a->Finish();
  (void)stream_b->Finish();
  server.stop();
}

void test_receiver_session_logs_client_and_signal_events() {
  auto control = std::make_shared<TransmitterControlState>();
  auto transmit_queue = std::make_shared<TransmitMessageQueue>(4);
  auto log_queue = std::make_shared<SpscRingBuffer<BidMessageLogRecord>>(16);
  std::array<std::uint64_t, Clients> expected_latencies{};
  expected_latencies.fill(5'000'000U);
  expected_latencies[4] = 123456U;
  TransmitterControlServer server(control,
                                  {.listen_address = "127.0.0.1:0",
                                   .transmit_queue = transmit_queue,
                                   .log_queue = log_queue,
                                   .client_expected_latency_ns = expected_latencies});
  server.start();

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::TransmitterControl::NewStub(channel);
  grpc::ClientContext stream_context;
  stream_context.set_deadline(std::chrono::system_clock::now() + std::chrono::seconds(3));
  auto stream = stub->ReceiverSession(&stream_context);

  pb::ReceiverSessionClientMessage hello;
  hello.mutable_hello()->set_client_id(4);
  check(stream->Write(hello), "receiver session log test failed to write hello");

  pb::ReceiverSessionClientMessage client_message;
  const std::array<std::uint8_t, 4> wire = {1, client_id_to_symbol(4), 55, 56};
  auto* decoded = client_message.mutable_client_message();
  decoded->set_receiver_unix_nanos(epoch_nanos_for_test() - 1000U);
  decoded->set_client_id(4);
  decoded->set_wire_payload(reinterpret_cast<const char*>(wire.data()), wire.size());
  check(stream->Write(client_message), "receiver session log test failed to write client message");

  pb::ReceiverSessionClientMessage signal_message;
  auto* signal = signal_message.mutable_signal_event();
  signal->set_receiver_unix_nanos(epoch_nanos_for_test() - 2000U);
  signal->set_event_type("fec_erasure");
  signal->set_detail("test");
  signal->set_metric(0.25);
  signal->set_count(7);
  check(stream->Write(signal_message), "receiver session log test failed to write signal event");

  bool saw_client = false;
  bool saw_signal = false;
  const auto deadline = std::chrono::steady_clock::now() + std::chrono::seconds(1);
  while ((!saw_client || !saw_signal) && std::chrono::steady_clock::now() < deadline) {
    BidMessageLogRecord record;
    while (log_queue->try_pop(record)) {
      if (record.event_type == LogEventType::receiver_client_message) {
        saw_client = record.has_client_id &&
                     record.client_id == 4U &&
                     record.payload == std::vector<std::uint8_t>(wire.begin(), wire.end()) &&
                     record.expected_latency_ns == 123456U &&
                     record.observed_latency_ns != 0U;
      } else if (record.event_type == LogEventType::receiver_signal) {
        saw_signal = record.event_name == "fec_erasure" &&
                     record.detail == "test" &&
                     record.count == 7U &&
                     record.observed_latency_ns != 0U;
      }
    }
    if (!saw_client || !saw_signal) {
      std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
  }
  check(saw_client, "receiver session did not log client message event");
  check(saw_signal, "receiver session did not log signal event");

  stream->WritesDone();
  (void)stream->Finish();
  server.stop();
}

void test_transmitter_bank_switch_price_provider() {
  auto control = std::make_shared<TransmitterControlState>();
  auto provider = [](std::uint8_t next_bank) -> std::optional<PriceBank> {
    PriceBank prices{};
    for (std::size_t i = 0; i < prices.size(); ++i) {
      prices[i] = 900'000U + next_bank * 10'000U + i;
    }
    return prices;
  };
  TransmitterControlServer server(control, {.listen_address = "127.0.0.1:0", .bank_price_provider = provider});
  server.start();

  auto channel = grpc::CreateChannel(server.bound_address(), grpc::InsecureChannelCredentials());
  auto stub = pb::TransmitterControl::NewStub(channel);
  pb::BankSwitchRequest request;
  pb::ControlAck ack;
  grpc::ClientContext context;
  const auto status = stub->BankSwitch(&context, request, &ack);
  check(status.ok() && ack.ok(), "bank switch provider test RPC failed");
  check(control->active_bank().bank == 1U, "bank switch provider test did not switch to bank1");
  check(control->price_units(1, 2) == 910'000U, "bank switch provider test did not update next-bank prices");

  server.stop();
}

void test_realtime_timestamp_accepts_fresh_stream() {
  auto pipeline_cfg = make_realtime_pipeline_config(true, 5.0, 23000U);
  const auto expected = make_message(0, 3, 19);

  SpscRingBuffer<DelimitedMessage> tx_messages(4);
  SpscRingBuffer<DelimitedMessage> rx_messages(4);
  check(tx_messages.try_push(expected), "failed to queue timestamp fresh message");

  RealtimeTransmitter transmitter(pipeline_cfg, tx_messages);
  RealtimeReceiver receiver(pipeline_cfg, rx_messages);
  std::array<Complex, 2048> samples{};
  bool timestamp_valid = false;

  for (std::size_t guard = 0; guard < 2000 && rx_messages.empty(); ++guard) {
    const auto tx = transmitter.push_samples(samples);
    check(tx.produced_samples != 0U, "timestamp fresh transmitter stalled");
    const auto rx = receiver.push_samples(std::span<const Complex>(samples).first(tx.produced_samples));
    check(!rx.replay_rejected, "fresh timestamp stream was rejected");
    timestamp_valid = timestamp_valid || rx.timestamp_valid;
  }

  check(timestamp_valid, "fresh timestamp was not validated");
  DelimitedMessage received;
  check(rx_messages.try_pop(received), "fresh timestamp stream did not emit message");
  check(received.bytes == expected.bytes, "fresh timestamp stream message mismatch");
}

void test_realtime_timestamp_rejects_stale_stream() {
  auto pipeline_cfg = make_realtime_pipeline_config(true, 0.1, 24000U);
  SpscRingBuffer<DelimitedMessage> tx_messages(4);
  SpscRingBuffer<DelimitedMessage> rx_messages(4);
  check(tx_messages.try_push(make_message(1, 3, 41)), "failed to queue timestamp stale message");

  RealtimeTransmitter transmitter(pipeline_cfg, tx_messages);
  std::vector<Complex> held_samples;
  std::array<Complex, 2048> chunk{};
  std::size_t emitted_bytes = 0;
  for (std::size_t guard = 0; guard < 64 && emitted_bytes < 24U; ++guard) {
    const auto tx = transmitter.push_samples(chunk);
    check(tx.produced_samples != 0U, "timestamp stale transmitter stalled");
    emitted_bytes += tx.emitted_bytes;
    held_samples.insert(held_samples.end(),
                        chunk.begin(),
                        chunk.begin() + static_cast<std::ptrdiff_t>(tx.produced_samples));
  }
  check(emitted_bytes >= 8U, "timestamp stale stream did not include sync timestamp bytes");

  std::this_thread::sleep_for(std::chrono::milliseconds(200));

  RealtimeReceiver receiver(pipeline_cfg, rx_messages);
  bool rejected = false;
  for (std::size_t offset = 0; offset < held_samples.size() && !rejected;) {
    const auto n = std::min<std::size_t>(held_samples.size() - offset, 1024U);
    const auto rx = receiver.push_samples(std::span<const Complex>(held_samples).subspan(offset, n));
    offset += rx.consumed_samples;
    rejected = rejected || rx.replay_rejected;
    if (rx.consumed_samples == 0U) {
      break;
    }
  }

  check(rejected, "stale timestamp stream was not rejected");
  check(rx_messages.empty(), "stale timestamp stream emitted a message");
}

struct RoutePoint {
  double latitude_degrees;
  double longitude_degrees;
};

struct RouteEstimate {
  double great_circle_km;
  double northern_vertex_latitude_degrees;
  double sky_path_km;
  double propagation_seconds;
  double ideal_fiber_seconds;
};

RouteEstimate estimate_route(RoutePoint from, RoutePoint to, std::size_t skips) {
  constexpr double earth_radius_km = 6371.0;
  constexpr double virtual_layer_height_km = 300.0;
  constexpr double light_speed_km_per_second = 299792.458;
  constexpr double fiber_refractive_index = 1.468;
  const auto radians = [](double degrees) { return degrees * std::numbers::pi / 180.0; };
  const auto unit_vector = [&](RoutePoint point) {
    const auto latitude = radians(point.latitude_degrees);
    const auto longitude = radians(point.longitude_degrees);
    return std::array<double, 3>{std::cos(latitude) * std::cos(longitude),
                                 std::cos(latitude) * std::sin(longitude),
                                 std::sin(latitude)};
  };

  check(skips > 0U, "route model requires at least one skip");
  const auto a = unit_vector(from);
  const auto b = unit_vector(to);
  const auto dot = std::clamp(a[0] * b[0] + a[1] * b[1] + a[2] * b[2], -1.0, 1.0);
  const auto central_angle = std::acos(dot);
  const std::array<double, 3> normal = {a[1] * b[2] - a[2] * b[1],
                                        a[2] * b[0] - a[0] * b[2],
                                        a[0] * b[1] - a[1] * b[0]};
  const auto normal_length = std::hypot(normal[0], normal[1], normal[2]);
  const auto northern_vertex = std::acos(std::abs(normal[2]) / normal_length);
  const auto great_circle_km = earth_radius_km * central_angle;
  const auto half_skip_angle = central_angle / (2.0 * static_cast<double>(skips));
  const auto layer_radius_km = earth_radius_km + virtual_layer_height_km;
  const auto skip_leg_km = std::sqrt(earth_radius_km * earth_radius_km +
                                     layer_radius_km * layer_radius_km -
                                     2.0 * earth_radius_km * layer_radius_km *
                                         std::cos(half_skip_angle));
  const auto sky_path_km = 2.0 * static_cast<double>(skips) * skip_leg_km;

  return {.great_circle_km = great_circle_km,
          .northern_vertex_latitude_degrees = northern_vertex * 180.0 / std::numbers::pi,
          .sky_path_km = sky_path_km,
          .propagation_seconds = sky_path_km / light_speed_km_per_second,
          .ideal_fiber_seconds = great_circle_km * fiber_refractive_index / light_speed_km_per_second};
}

void test_route_planning_model() {
  const auto chicago_shanghai =
      estimate_route({41.8781, -87.6298}, {31.2304, 121.4737}, 4U);
  check(std::abs(chicago_shanghai.great_circle_km - 11356.633) < 0.001,
        "Chicago-Shanghai great-circle distance mismatch");
  check(std::abs(chicago_shanghai.northern_vertex_latitude_degrees - 71.533836) < 0.000001,
        "Chicago-Shanghai northern vertex mismatch");
  check(std::abs(chicago_shanghai.sky_path_km - 11842.653) < 0.001,
        "Chicago-Shanghai sky-path distance mismatch");
  check(std::abs(chicago_shanghai.propagation_seconds - 0.039502838) < 0.000000001,
        "Chicago-Shanghai propagation mismatch");
  check(std::abs(chicago_shanghai.ideal_fiber_seconds - 0.055610261) < 0.000000001,
        "Chicago-Shanghai fiber floor mismatch");

  const auto new_york_london =
      estimate_route({40.7128, -74.0060}, {51.5074, -0.1278}, 2U);
  check(std::abs(new_york_london.great_circle_km - 5570.222) < 0.001,
        "New York-London great-circle distance mismatch");
  check(std::abs(new_york_london.sky_path_km - 5813.713) < 0.001,
        "New York-London sky-path distance mismatch");
  check(std::abs(new_york_london.propagation_seconds - 0.019392460) < 0.000000001,
        "New York-London propagation mismatch");
  check(std::abs(new_york_london.ideal_fiber_seconds - 0.027275823) < 0.000000001,
        "New York-London fiber floor mismatch");

  const auto chicago_london =
      estimate_route({41.8781, -87.6298}, {51.5074, -0.1278}, 2U);
  check(std::abs(chicago_london.great_circle_km - 6352.978) < 0.001,
        "Chicago-London great-circle distance mismatch");
  check(std::abs(chicago_london.propagation_seconds - 0.021995616) < 0.000000001,
        "Chicago-London propagation mismatch");
}

void test_convolutional_latency_estimates() {
  auto rf = make_rf_config();
  rf.modem.bandwidth_hz = 24000.0;
  const auto symbol_rate = derived_symbol_rate_hz(rf.modem);
  check(std::abs(symbol_rate - 19200.0) < 0.000001, "24 kHz derived symbol rate mismatch");

  const auto q64_byte = estimate_convolutional_latency(
      1, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q64_byte.coded_bits == 16U, "rate 1/2 one-byte coded bit count mismatch");
  check(q64_byte.qam_symbols == 3U, "rate 1/2 Q64 one-byte symbol count mismatch");
  check(q64_byte.encode_decode_latency_seconds > 0.00030 && q64_byte.encode_decode_latency_seconds < 0.00033,
        "rate 1/2 Q64 one-byte latency mismatch");

  const auto q64_message = estimate_convolutional_latency(
      4, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q64_message.coded_bits == 64U, "rate 1/2 four-byte coded bit count mismatch");
  check(q64_message.qam_symbols == 11U, "rate 1/2 Q64 four-byte symbol count mismatch");
  check(q64_message.encode_decode_latency_seconds > 0.00113 && q64_message.encode_decode_latency_seconds < 0.00116,
        "rate 1/2 Q64 four-byte latency mismatch");

  const auto q64_message_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q64_message_with_next_delimiter.coded_bits == 80U,
        "rate 1/2 five-byte coded bit count mismatch");
  check(q64_message_with_next_delimiter.qam_symbols == 14U,
        "rate 1/2 Q64 five-byte symbol count mismatch");
  check(q64_message_with_next_delimiter.encode_decode_latency_seconds > 0.00144 &&
            q64_message_with_next_delimiter.encode_decode_latency_seconds < 0.00147,
        "rate 1/2 Q64 five-byte latency mismatch");

  const auto q16_message = estimate_convolutional_latency(
      4, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam16)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q16_message.qam_symbols == 16U, "rate 1/2 Q16 four-byte symbol count mismatch");
  check(q16_message.encode_decode_latency_seconds > 0.00165 && q16_message.encode_decode_latency_seconds < 0.00168,
        "rate 1/2 Q16 four-byte latency mismatch");

  const auto q16_message_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam16)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q16_message_with_next_delimiter.qam_symbols == 20U,
        "rate 1/2 Q16 five-byte symbol count mismatch");
  check(q16_message_with_next_delimiter.encode_decode_latency_seconds > 0.00207 &&
            q16_message_with_next_delimiter.encode_decode_latency_seconds < 0.00210,
        "rate 1/2 Q16 five-byte latency mismatch");

  auto rf_10khz = make_rf_config();
  rf_10khz.modem.bandwidth_hz = 10000.0;
  const auto symbol_rate_10khz = derived_symbol_rate_hz(rf_10khz.modem);
  check(std::abs(symbol_rate_10khz - 8000.0) < 0.000001,
        "10 kHz derived symbol rate mismatch");
  check(std::abs(symbol_rate_10khz * static_cast<double>(bits_per_symbol(Modulation::qam16)) * 0.5 -
                     16000.0) < 0.000001,
        "10 kHz rate 1/2 Q16 throughput mismatch");

  const auto q16_10khz_message_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam16)), symbol_rate_10khz,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q16_10khz_message_with_next_delimiter.coded_bits == 80U,
        "10 kHz rate 1/2 Q16 five-byte coded bit count mismatch");
  check(q16_10khz_message_with_next_delimiter.qam_symbols == 20U,
        "10 kHz rate 1/2 Q16 five-byte symbol count mismatch");
  check(q16_10khz_message_with_next_delimiter.encode_decode_latency_seconds > 0.00499 &&
            q16_10khz_message_with_next_delimiter.encode_decode_latency_seconds < 0.00501,
        "10 kHz rate 1/2 Q16 five-byte latency mismatch");

  const auto q64_punctured = estimate_convolutional_latency(
      4, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_2_3());
  check(q64_punctured.coded_bits == 48U, "rate 2/3 four-byte coded bit count mismatch");
  check(q64_punctured.qam_symbols == 8U, "rate 2/3 Q64 four-byte symbol count mismatch");

  const auto q64_punctured_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_2_3());
  check(q64_punctured_with_next_delimiter.coded_bits == 60U,
        "rate 2/3 five-byte coded bit count mismatch");
  check(q64_punctured_with_next_delimiter.qam_symbols == 10U,
        "rate 2/3 Q64 five-byte symbol count mismatch");

  const auto q64_punctured_3_4_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam64)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_3_4());
  check(q64_punctured_3_4_with_next_delimiter.coded_bits == 54U,
        "rate 3/4 five-byte coded bit count mismatch");
  check(q64_punctured_3_4_with_next_delimiter.qam_symbols == 9U,
        "rate 3/4 Q64 five-byte symbol count mismatch");

  const auto q1024_message_with_next_delimiter = estimate_convolutional_latency(
      5, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam1024)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q1024_message_with_next_delimiter.coded_bits == 80U,
        "rate 1/2 Q1024 five-byte coded bit count mismatch");
  check(q1024_message_with_next_delimiter.qam_symbols == 8U,
        "rate 1/2 Q1024 five-byte symbol count mismatch");
  check(q1024_message_with_next_delimiter.encode_decode_latency_seconds > 0.00082 &&
            q1024_message_with_next_delimiter.encode_decode_latency_seconds < 0.00085,
        "rate 1/2 Q1024 five-byte latency mismatch");

  const auto q1024_timestamp = estimate_convolutional_latency(
      8, static_cast<std::uint8_t>(bits_per_symbol(Modulation::qam1024)), symbol_rate,
      PuncturedConvolutionalCodeConfig::rate_1_2());
  check(q1024_timestamp.coded_bits == 128U, "rate 1/2 Q1024 timestamp coded bit count mismatch");
  check(q1024_timestamp.qam_symbols == 13U, "rate 1/2 Q1024 timestamp symbol count mismatch");
}

} // namespace

int main() {
  test_constellations();
  test_qci_radial_constellations();
  test_config_validation();
  test_sample_formats();
  test_base254_varuint_and_zigzag();
  test_bank_symbol_integer_message_codec();
  test_frame_loopback();
  test_qam1024_modem_symbol_loopback();
  test_continuous_token_stream();
  test_uncertain_tokens();
  test_rf_acquisition_correlator();
  test_rf_stream_loopback();
  test_rf_stream_qam1024_header_loopback();
  test_rf_stream_qci1024_header_loopback();
  test_rf_reacquire_after_lock_loss();
  test_message_stream_delimiters_across_payload_frames();
  test_message_framer_active_bank_override();
  test_message_crc_trailer_rejects_corruption_and_allows_padding();
  test_bid_message_transmit_intake();
  test_market_data_shared_memory_ring();
  test_client_udp_message_handler();
  test_client_budget_accounting();
  test_client_udp_budget_rejection();
  test_quote_udp_config_and_emitter();
  test_quote_udp_bank_switch_requires_fresh_bank_update();
  test_receiver_bank_cache_clear_stops_market_udp();
  test_receiver_default_client_permissions();
  test_message_deframer_drops_around_erasures();
  test_convolutional_viterbi_and_aes_ctr();
  test_realtime_message_pipeline_end_to_end();
  test_realtime_integer_message_pipeline_end_to_end();
  test_receiver_control_state_and_restart_receiver();
  test_transmitter_control_state_and_use_bank();
  test_receiver_control_grpc_server();
  test_transmitter_control_grpc_server();
  test_transmitter_receiver_session_stream_and_bank_switch();
  test_transmitter_receiver_session_broadcasts_canonical_messages();
  test_receiver_session_logs_client_and_signal_events();
  test_transmitter_bank_switch_price_provider();
  test_realtime_timestamp_accepts_fresh_stream();
  test_realtime_timestamp_rejects_stale_stream();
  test_route_planning_model();
  test_convolutional_latency_estimates();
  std::cout << "goblin_cannon_tests passed\n";
  return 0;
}
