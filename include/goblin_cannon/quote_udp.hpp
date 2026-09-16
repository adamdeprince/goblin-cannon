#pragma once

#include "goblin_cannon/control_server.hpp"
#include "goblin_cannon/message_stream.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <span>
#include <string>
#include <vector>

namespace goblin_cannon {

using QuoteUdpPayload = std::array<std::uint8_t, 9>;
using BadMessageUdpPayload = std::array<std::uint8_t, 19>;

enum class QuoteUdpBackend {
  kernel_udp,
  dpdk,
};

struct QuoteUdpSinkConfig {
  QuoteUdpBackend backend = QuoteUdpBackend::kernel_udp;
  std::string destination_ip;
  std::uint16_t destination_port = 0;
  std::string source_ip = "0.0.0.0";
  std::uint16_t source_port = 0;

  std::vector<std::string> dpdk_eal_args;
  std::uint16_t dpdk_port_id = 0;
  std::uint16_t dpdk_queue_id = 0;
  std::uint32_t dpdk_mbuf_count = 8192;
  std::uint32_t dpdk_mempool_cache_size = 256;
  std::uint16_t dpdk_burst_size = 32;
  std::string dpdk_source_mac;
  std::string dpdk_destination_mac;
};

class QuotePacketSink {
public:
  virtual ~QuotePacketSink() = default;
  virtual void send_packet(std::span<const std::uint8_t> payload) = 0;
  virtual void send_quote_packet(std::span<const std::uint8_t, 9> payload);
  virtual void send_bad_message_packet(std::span<const std::uint8_t, 19> payload);
};

class KernelUdpQuotePacketSink final : public QuotePacketSink {
public:
  explicit KernelUdpQuotePacketSink(const QuoteUdpSinkConfig& config);
  ~KernelUdpQuotePacketSink() override;

  KernelUdpQuotePacketSink(const KernelUdpQuotePacketSink&) = delete;
  KernelUdpQuotePacketSink& operator=(const KernelUdpQuotePacketSink&) = delete;
  KernelUdpQuotePacketSink(KernelUdpQuotePacketSink&&) noexcept;
  KernelUdpQuotePacketSink& operator=(KernelUdpQuotePacketSink&&) noexcept;

  void send_packet(std::span<const std::uint8_t> payload) override;

private:
  int socket_fd_ = -1;
  std::array<std::uint8_t, 16> destination_storage_{};
  std::uint32_t destination_size_ = 0;
};

class DpdkQuotePacketSink final : public QuotePacketSink {
public:
  explicit DpdkQuotePacketSink(const QuoteUdpSinkConfig& config);
  void send_packet(std::span<const std::uint8_t> payload) override;

private:
  QuoteUdpSinkConfig config_;
};

[[nodiscard]] QuoteUdpSinkConfig load_quote_udp_sink_config(const std::filesystem::path& path);
[[nodiscard]] std::shared_ptr<QuotePacketSink> make_quote_packet_sink(const QuoteUdpSinkConfig& config);

class QuotePacketEmitter final : public DelimitedMessageObserver {
public:
  QuotePacketEmitter(std::shared_ptr<ReceiverControlState> control,
                     std::shared_ptr<QuotePacketSink> sink);

  void on_delimited_message(const DelimitedMessage& message) override;

private:
  std::shared_ptr<ReceiverControlState> control_;
  std::shared_ptr<QuotePacketSink> sink_;
};

[[nodiscard]] QuoteUdpPayload make_quote_udp_payload(std::uint8_t symbol, std::uint64_t price_units);
[[nodiscard]] BadMessageUdpPayload make_bad_message_udp_payload(std::uint8_t bank,
                                                                std::uint8_t symbol,
                                                                std::uint64_t base_price_units,
                                                                std::uint64_t reconstructed_price_units);

} // namespace goblin_cannon
