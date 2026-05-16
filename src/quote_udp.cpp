#include "wbhf_modem/quote_udp.hpp"

#include "wbhf_modem/integer_codec.hpp"
#include "wbhf_modem/symbols.hpp"

#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <charconv>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string_view>

namespace wbhf_modem {

namespace {

std::string trim(std::string_view value) {
  const auto begin = value.find_first_not_of(" \t\r\n");
  if (begin == std::string_view::npos) {
    return {};
  }
  const auto end = value.find_last_not_of(" \t\r\n");
  return std::string(value.substr(begin, end - begin + 1U));
}

std::uint32_t parse_u32(std::string_view value, std::string_view key) {
  const auto text = trim(value);
  std::uint32_t out = 0;
  const auto* first = text.data();
  const auto* last = text.data() + text.size();
  const auto parsed = std::from_chars(first, last, out);
  if (parsed.ec != std::errc{} || parsed.ptr != last) {
    throw std::invalid_argument(std::string("invalid integer for ") + std::string(key));
  }
  return out;
}

std::uint16_t parse_u16(std::string_view value, std::string_view key) {
  const auto out = parse_u32(value, key);
  if (out > std::numeric_limits<std::uint16_t>::max()) {
    throw std::invalid_argument(std::string("integer out of range for ") + std::string(key));
  }
  return static_cast<std::uint16_t>(out);
}

void validate_quote_config(const QuoteUdpSinkConfig& config) {
  if (config.destination_ip.empty()) {
    throw std::invalid_argument("quote UDP destination_ip is required");
  }
  if (config.destination_port == 0U) {
    throw std::invalid_argument("quote UDP destination_port is required");
  }
  if (config.backend == QuoteUdpBackend::dpdk) {
    if (config.source_ip.empty()) {
      throw std::invalid_argument("DPDK quote UDP source_ip is required");
    }
    if (config.dpdk_source_mac.empty() || config.dpdk_destination_mac.empty()) {
      throw std::invalid_argument("DPDK quote UDP source/destination MAC addresses are required");
    }
    if (config.dpdk_burst_size == 0U || config.dpdk_mbuf_count == 0U) {
      throw std::invalid_argument("DPDK quote UDP mbuf_count and burst_size must be positive");
    }
  }
}

void write_u64_be(std::span<std::uint8_t, 8> out, std::uint64_t value) {
  for (std::size_t i = 0; i < out.size(); ++i) {
    const auto shift = static_cast<unsigned>((out.size() - i - 1U) * 8U);
    out[i] = static_cast<std::uint8_t>((value >> shift) & 0xFFU);
  }
}

template <std::size_t N>
void write_u64_be_at(std::array<std::uint8_t, N>& out, std::size_t offset, std::uint64_t value) {
  write_u64_be(std::span<std::uint8_t, 8>(out.data() + offset, 8U), value);
}

std::uint64_t checked_add_price_delta(std::uint64_t base, std::int64_t delta) {
  if (delta >= 0) {
    const auto unsigned_delta = static_cast<std::uint64_t>(delta);
    if (base > std::numeric_limits<std::uint64_t>::max() - unsigned_delta) {
      throw std::overflow_error("quote price delta overflows uint64");
    }
    return base + unsigned_delta;
  }

  const auto magnitude = static_cast<std::uint64_t>(-(delta + 1)) + 1U;
  if (base < magnitude) {
    throw std::underflow_error("quote price delta makes price negative");
  }
  return base - magnitude;
}

} // namespace

void QuotePacketSink::send_quote_packet(std::span<const std::uint8_t, 9> payload) {
  send_packet(payload);
}

void QuotePacketSink::send_bad_message_packet(std::span<const std::uint8_t, 19> payload) {
  send_packet(payload);
}

KernelUdpQuotePacketSink::KernelUdpQuotePacketSink(const QuoteUdpSinkConfig& config) {
  validate_quote_config(config);
  socket_fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd_ < 0) {
    throw std::runtime_error(std::string("failed to create UDP socket: ") + std::strerror(errno));
  }

  sockaddr_in source{};
  source.sin_family = AF_INET;
  source.sin_port = htons(config.source_port);
  if (::inet_pton(AF_INET, config.source_ip.c_str(), &source.sin_addr) != 1) {
    ::close(socket_fd_);
    socket_fd_ = -1;
    throw std::invalid_argument("invalid quote UDP source_ip");
  }
  if (::bind(socket_fd_, reinterpret_cast<sockaddr*>(&source), sizeof(source)) != 0) {
    ::close(socket_fd_);
    socket_fd_ = -1;
    throw std::runtime_error(std::string("failed to bind UDP socket: ") + std::strerror(errno));
  }

  sockaddr_in destination{};
  destination.sin_family = AF_INET;
  destination.sin_port = htons(config.destination_port);
  if (::inet_pton(AF_INET, config.destination_ip.c_str(), &destination.sin_addr) != 1) {
    ::close(socket_fd_);
    socket_fd_ = -1;
    throw std::invalid_argument("invalid quote UDP destination_ip");
  }
  static_assert(sizeof(destination) <= std::tuple_size_v<decltype(destination_storage_)>);
  std::memcpy(destination_storage_.data(), &destination, sizeof(destination));
  destination_size_ = sizeof(destination);
}

KernelUdpQuotePacketSink::~KernelUdpQuotePacketSink() {
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
}

KernelUdpQuotePacketSink::KernelUdpQuotePacketSink(KernelUdpQuotePacketSink&& other) noexcept
    : socket_fd_(other.socket_fd_),
      destination_storage_(other.destination_storage_),
      destination_size_(other.destination_size_) {
  other.socket_fd_ = -1;
  other.destination_size_ = 0;
}

KernelUdpQuotePacketSink& KernelUdpQuotePacketSink::operator=(KernelUdpQuotePacketSink&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
  socket_fd_ = other.socket_fd_;
  destination_storage_ = other.destination_storage_;
  destination_size_ = other.destination_size_;
  other.socket_fd_ = -1;
  other.destination_size_ = 0;
  return *this;
}

void KernelUdpQuotePacketSink::send_packet(std::span<const std::uint8_t> payload) {
  const auto sent = ::sendto(socket_fd_,
                             payload.data(),
                             payload.size(),
                             0,
                             reinterpret_cast<const sockaddr*>(destination_storage_.data()),
                             destination_size_);
  if (sent != static_cast<ssize_t>(payload.size())) {
    throw std::runtime_error(std::string("failed to send quote UDP packet: ") + std::strerror(errno));
  }
}

DpdkQuotePacketSink::DpdkQuotePacketSink(const QuoteUdpSinkConfig& config)
    : config_(config) {
  validate_quote_config(config_);
#ifndef WBHF_MODEM_HAS_DPDK
  throw std::runtime_error("DPDK quote UDP backend requested, but wbhf_modem was built without DPDK support");
#endif
}

void DpdkQuotePacketSink::send_packet(std::span<const std::uint8_t>) {
#ifndef WBHF_MODEM_HAS_DPDK
  throw std::runtime_error("DPDK quote UDP backend requested, but wbhf_modem was built without DPDK support");
#endif
}

QuoteUdpSinkConfig load_quote_udp_sink_config(const std::filesystem::path& path) {
  std::ifstream in(path);
  if (!in) {
    throw std::runtime_error("failed to open quote UDP config file");
  }

  QuoteUdpSinkConfig config;
  std::string line;
  std::size_t line_number = 0;
  while (std::getline(in, line)) {
    ++line_number;
    const auto comment = line.find('#');
    if (comment != std::string::npos) {
      line.resize(comment);
    }
    const auto equals = line.find('=');
    if (equals == std::string::npos) {
      if (!trim(line).empty()) {
        throw std::invalid_argument("invalid quote UDP config line " + std::to_string(line_number));
      }
      continue;
    }

    const auto key = trim(std::string_view(line).substr(0, equals));
    const auto value = trim(std::string_view(line).substr(equals + 1U));
    if (key == "backend") {
      if (value == "kernel_udp") {
        config.backend = QuoteUdpBackend::kernel_udp;
      } else if (value == "dpdk") {
        config.backend = QuoteUdpBackend::dpdk;
      } else {
        throw std::invalid_argument("quote UDP backend must be kernel_udp or dpdk");
      }
    } else if (key == "destination_ip") {
      config.destination_ip = value;
    } else if (key == "destination_port") {
      config.destination_port = parse_u16(value, key);
    } else if (key == "source_ip") {
      config.source_ip = value;
    } else if (key == "source_port") {
      config.source_port = parse_u16(value, key);
    } else if (key == "dpdk.eal_arg") {
      config.dpdk_eal_args.push_back(value);
    } else if (key == "dpdk.port_id") {
      config.dpdk_port_id = parse_u16(value, key);
    } else if (key == "dpdk.queue_id") {
      config.dpdk_queue_id = parse_u16(value, key);
    } else if (key == "dpdk.mbuf_count") {
      config.dpdk_mbuf_count = parse_u32(value, key);
    } else if (key == "dpdk.mempool_cache_size") {
      config.dpdk_mempool_cache_size = parse_u32(value, key);
    } else if (key == "dpdk.burst_size") {
      config.dpdk_burst_size = parse_u16(value, key);
    } else if (key == "dpdk.source_mac") {
      config.dpdk_source_mac = value;
    } else if (key == "dpdk.destination_mac") {
      config.dpdk_destination_mac = value;
    } else {
      throw std::invalid_argument("unknown quote UDP config key: " + key);
    }
  }

  validate_quote_config(config);
  return config;
}

std::shared_ptr<QuotePacketSink> make_quote_packet_sink(const QuoteUdpSinkConfig& config) {
  switch (config.backend) {
  case QuoteUdpBackend::kernel_udp:
    return std::make_shared<KernelUdpQuotePacketSink>(config);
  case QuoteUdpBackend::dpdk:
    return std::make_shared<DpdkQuotePacketSink>(config);
  }
  throw std::invalid_argument("unknown quote UDP backend");
}

QuotePacketEmitter::QuotePacketEmitter(std::shared_ptr<ReceiverControlState> control,
                                       std::shared_ptr<QuotePacketSink> sink)
    : control_(std::move(control)),
      sink_(std::move(sink)) {
  if (!control_) {
    throw std::invalid_argument("QuotePacketEmitter requires receiver control state");
  }
  if (!sink_) {
    throw std::invalid_argument("QuotePacketEmitter requires packet sink");
  }
}

void QuotePacketEmitter::on_delimited_message(const DelimitedMessage& message) {
  const auto decoded = decode_bank_symbol_integer(message);
  if (!decoded.has_value()) {
    throw std::invalid_argument("quote emitter received malformed integer message");
  }
  if (!control_->accept_received_symbol(decoded->bank, decoded->symbol)) {
    return;
  }
  if (!control_->symbol_allowed(decoded->symbol)) {
    return;
  }
  if (!is_market_symbol_byte(decoded->symbol)) {
    return;
  }
  const auto base = control_->price_units(decoded->bank, decoded->symbol);
  const auto price = checked_add_price_delta(base, decoded->value);
  const auto payload = make_quote_udp_payload(decoded->symbol, price);
  sink_->send_quote_packet(payload);
}

QuoteUdpPayload make_quote_udp_payload(std::uint8_t symbol, std::uint64_t price_units) {
  QuoteUdpPayload payload{};
  payload[0] = symbol;
  write_u64_be(std::span<std::uint8_t, 8>(payload.data() + 1U, 8U), price_units);
  return payload;
}

BadMessageUdpPayload make_bad_message_udp_payload(std::uint8_t bank,
                                                  std::uint8_t symbol,
                                                  std::uint64_t base_price_units,
                                                  std::uint64_t reconstructed_price_units) {
  BadMessageUdpPayload payload{};
  payload[0] = 0U;
  payload[1] = bank;
  payload[2] = symbol;
  write_u64_be_at(payload, 3U, base_price_units);
  write_u64_be_at(payload, 11U, reconstructed_price_units);
  return payload;
}

} // namespace wbhf_modem
