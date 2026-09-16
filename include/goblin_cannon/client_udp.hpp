#pragma once

#include "goblin_cannon/message_stream.hpp"
#include "goblin_cannon/symbols.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <memory>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace goblin_cannon {

class TransmitterControlState;

enum class ClientUdpBackend {
  kernel_udp,
  dpdk,
};

enum class ClientUdpStatusCode : std::uint8_t {
  message_sent = 1,
  insufficient_bid = 2,
  invalid_message_format = 3,
  unauthorized_source = 4,
  insufficient_budget = 5,
};

struct ClientEndpoint {
  std::string ip;
  std::uint16_t port = 0;
};

struct ClientUdpIngressConfig {
  ClientUdpBackend backend = ClientUdpBackend::kernel_udp;
  std::string listen_ip = "0.0.0.0";
  std::uint16_t listen_port = 0;
  std::array<std::string, Clients> authorized_client_ips = {};

  std::vector<std::string> dpdk_eal_args;
  std::uint16_t dpdk_port_id = 0;
  std::uint16_t dpdk_queue_id = 0;
  std::uint32_t dpdk_mbuf_count = 8192;
  std::uint32_t dpdk_mempool_cache_size = 256;
  std::uint16_t dpdk_burst_size = 32;
};

using ClientExpectedLatenciesNs = std::array<std::uint64_t, Clients>;

struct ClientUdpDatagram {
  ClientEndpoint source;
  std::vector<std::uint8_t> payload;
};

struct ClientUdpHandleResult {
  bool accepted = false;
  bool transmitted = false;
  bool queued_for_arbitration = false;
  bool rejected = false;
  bool invalid = false;
  bool unauthorized = false;
  bool log_backpressure = false;
  bool transmit_backpressure = false;
  bool budget_rejected = false;
  std::uint8_t client_id = 0;
  std::uint32_t bid_price = 0;
};

class ClientUdpStatusSink {
public:
  virtual ~ClientUdpStatusSink() = default;
  virtual void send_client_status(const ClientEndpoint& endpoint,
                                  ClientUdpStatusCode status,
                                  std::uint32_t bid_price,
                                  std::uint32_t winning_bid_price) = 0;
};

class KernelClientUdpStatusSink final : public ClientUdpStatusSink {
public:
  KernelClientUdpStatusSink();
  ~KernelClientUdpStatusSink() override;

  KernelClientUdpStatusSink(const KernelClientUdpStatusSink&) = delete;
  KernelClientUdpStatusSink& operator=(const KernelClientUdpStatusSink&) = delete;
  KernelClientUdpStatusSink(KernelClientUdpStatusSink&&) noexcept;
  KernelClientUdpStatusSink& operator=(KernelClientUdpStatusSink&&) noexcept;

  void send_client_status(const ClientEndpoint& endpoint,
                          ClientUdpStatusCode status,
                          std::uint32_t bid_price,
                          std::uint32_t winning_bid_price) override;

private:
  int socket_fd_ = -1;
};

class ClientUdpMessageHandler final : public BidMessageLogObserver {
public:
  explicit ClientUdpMessageHandler(ClientUdpIngressConfig config,
                                   std::shared_ptr<ClientUdpStatusSink> status_sink,
                                   std::shared_ptr<TransmitterControlState> control = {},
                                   std::shared_ptr<BidBudgetAccountant> accountant = {});

  [[nodiscard]] ClientUdpHandleResult handle_datagram(const ClientUdpDatagram& datagram,
                                                      BidMessageTransmitIntake& intake,
                                                      TransmitMessageQueue& transmit_queue,
                                                      SpscRingBuffer<BidMessageLogRecord>& log_queue);
  // Hot-path overload: caller provides the parsed network-order source addr
  // so we skip the string-keyed authorized-client scan.
  [[nodiscard]] ClientUdpHandleResult handle_datagram(const ClientUdpDatagram& datagram,
                                                      std::uint32_t source_addr_be,
                                                      BidMessageTransmitIntake& intake,
                                                      TransmitMessageQueue& transmit_queue,
                                                      SpscRingBuffer<BidMessageLogRecord>& log_queue);
  [[nodiscard]] BidMessageIntakeResult pump_pending(BidMessageTransmitIntake& intake,
                                                    TransmitMessageQueue& transmit_queue,
                                                    SpscRingBuffer<BidMessageLogRecord>& log_queue);
  void on_bid_message_log(const BidMessageLogRecord& record) override;
  // Lookup by parsed source address (network-byte-order uint32) — avoids the
  // inet_ntop + std::string compare on the per-packet hot path.
  [[nodiscard]] std::optional<std::uint8_t> client_id_for_source_addr(std::uint32_t addr) const noexcept;

private:
  [[nodiscard]] std::optional<std::uint8_t> client_id_for_source(std::string_view ip) const noexcept;
  [[nodiscard]] bool log_status(BidMessageLogRecord record,
                                SpscRingBuffer<BidMessageLogRecord>& log_queue);

  ClientUdpIngressConfig config_;
  std::shared_ptr<ClientUdpStatusSink> status_sink_;
  std::shared_ptr<TransmitterControlState> control_;
  std::shared_ptr<BidBudgetAccountant> accountant_;
  // Precomputed authorized-source-address table (network byte order); a
  // zero-byte string in config maps to absent.
  std::array<std::uint32_t, Clients> authorized_client_addrs_ = {};
  std::array<bool, Clients> authorized_client_present_ = {};
};

class ClientUdpIngressSocket {
public:
  ClientUdpIngressSocket(ClientUdpIngressConfig config,
                         std::shared_ptr<ClientUdpStatusSink> status_sink,
                         std::shared_ptr<TransmitterControlState> control = {},
                         std::shared_ptr<BidBudgetAccountant> accountant = {});
  ~ClientUdpIngressSocket();

  ClientUdpIngressSocket(const ClientUdpIngressSocket&) = delete;
  ClientUdpIngressSocket& operator=(const ClientUdpIngressSocket&) = delete;
  ClientUdpIngressSocket(ClientUdpIngressSocket&&) noexcept;
  ClientUdpIngressSocket& operator=(ClientUdpIngressSocket&&) noexcept;

  [[nodiscard]] ClientUdpHandleResult poll_once(BidMessageTransmitIntake& intake,
                                                TransmitMessageQueue& transmit_queue,
                                                SpscRingBuffer<BidMessageLogRecord>& log_queue);
  [[nodiscard]] BidMessageIntakeResult pump_pending(BidMessageTransmitIntake& intake,
                                                    TransmitMessageQueue& transmit_queue,
                                                    SpscRingBuffer<BidMessageLogRecord>& log_queue);

  // Block (without external locks) until the socket has a datagram readable
  // or timeout_ms elapses; returns true if data is readable.
  bool wait_for_data(int timeout_ms) const noexcept;

private:
  ClientUdpMessageHandler handler_;
  int socket_fd_ = -1;
};

[[nodiscard]] ClientUdpIngressConfig load_client_udp_ingress_config(const std::filesystem::path& path);
[[nodiscard]] ClientExpectedLatenciesNs load_client_expected_latencies_ns_config(
    const std::filesystem::path& path,
    std::uint64_t default_latency_ns = 5'000'000U);
[[nodiscard]] std::array<std::uint8_t, 9> encode_client_udp_status(ClientUdpStatusCode status,
                                                                   std::uint32_t bid_price,
                                                                   std::uint32_t winning_bid_price);

} // namespace goblin_cannon
