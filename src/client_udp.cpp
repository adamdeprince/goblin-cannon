#include "goblin_cannon/client_udp.hpp"

#include "goblin_cannon/control_server.hpp"

#include <arpa/inet.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <poll.h>
#include <sys/socket.h>
#include <unistd.h>

#include <algorithm>
#include <cerrno>
#include <charconv>
#include <chrono>
#include <cstring>
#include <fstream>
#include <stdexcept>
#include <string_view>

namespace goblin_cannon {

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
    throw std::invalid_argument("invalid integer for " + std::string(key));
  }
  return out;
}

std::uint64_t parse_u64(std::string_view value, std::string_view key) {
  const auto text = trim(value);
  std::uint64_t out = 0;
  const auto* first = text.data();
  const auto* last = text.data() + text.size();
  const auto parsed = std::from_chars(first, last, out);
  if (parsed.ec != std::errc{} || parsed.ptr != last) {
    throw std::invalid_argument("invalid integer for " + std::string(key));
  }
  return out;
}

std::uint16_t parse_u16(std::string_view value, std::string_view key) {
  const auto out = parse_u32(value, key);
  if (out > 0xFFFFU) {
    throw std::invalid_argument("integer out of range for " + std::string(key));
  }
  return static_cast<std::uint16_t>(out);
}

std::uint32_t read_u32_be(std::span<const std::uint8_t> bytes) {
  return (static_cast<std::uint32_t>(bytes[0]) << 24U) |
         (static_cast<std::uint32_t>(bytes[1]) << 16U) |
         (static_cast<std::uint32_t>(bytes[2]) << 8U) |
         static_cast<std::uint32_t>(bytes[3]);
}

void write_u32_be(std::span<std::uint8_t, 4> out, std::uint32_t value) {
  out[0] = static_cast<std::uint8_t>((value >> 24U) & 0xFFU);
  out[1] = static_cast<std::uint8_t>((value >> 16U) & 0xFFU);
  out[2] = static_cast<std::uint8_t>((value >> 8U) & 0xFFU);
  out[3] = static_cast<std::uint8_t>(value & 0xFFU);
}

std::uint64_t current_epoch_nanos() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

bool is_valid_client_message_payload(std::span<const std::uint8_t> payload) noexcept {
  if (payload.size() < 2U || payload.size() > 9U) {
    return false;
  }
  if (payload[0] != 0U && payload[0] != 1U) {
    return false;
  }
  return std::all_of(payload.begin() + 1, payload.end(), [](std::uint8_t byte) {
    return byte != 0U && byte != 1U;
  });
}

BidMessageLogRecord make_udp_ingress_log(const ClientUdpDatagram& datagram,
                                         std::uint32_t bid_price,
                                         std::optional<std::uint8_t> client_id) {
  BidMessageLogRecord record;
  record.event_type = LogEventType::udp_ingress;
  record.local_timestamp_ns = current_epoch_nanos();
  record.payload = datagram.payload.size() >= 4U
      ? std::vector<std::uint8_t>(datagram.payload.begin() + 4, datagram.payload.end())
      : std::vector<std::uint8_t>{};
  record.raw_payload = datagram.payload;
  record.bid_price = bid_price;
  record.client_id = client_id.value_or(0);
  record.has_client_id = client_id.has_value();
  record.reply_ip = datagram.source.ip;
  record.reply_port = datagram.source.port;
  return record;
}

BidMessageLogRecord make_status_log(const ClientUdpDatagram& datagram,
                                    BidMessageLogStatus status,
                                    std::uint32_t bid_price,
                                    std::uint32_t winning_bid_price,
                                    std::optional<std::uint8_t> client_id) {
  const auto payload_begin = datagram.payload.size() >= 4U ? datagram.payload.begin() + 4 : datagram.payload.begin();
  BidMessageLogRecord record;
  record.event_type = LogEventType::udp_decision;
  record.local_timestamp_ns = current_epoch_nanos();
  record.payload = std::vector<std::uint8_t>(payload_begin, datagram.payload.end());
  record.raw_payload = datagram.payload;
  record.status = status;
  record.bid_price = bid_price;
  record.winning_bid_price = winning_bid_price;
  record.client_id = client_id.value_or(0);
  record.has_client_id = client_id.has_value();
  record.reply_ip = datagram.source.ip;
  record.reply_port = datagram.source.port;
  return record;
}

ClientUdpStatusCode status_code_for_log(BidMessageLogStatus status) {
  switch (status) {
  case BidMessageLogStatus::sent:
    return ClientUdpStatusCode::message_sent;
  case BidMessageLogStatus::rejected:
    return ClientUdpStatusCode::insufficient_bid;
  case BidMessageLogStatus::invalid_message_format:
    return ClientUdpStatusCode::invalid_message_format;
  case BidMessageLogStatus::unauthorized_source:
    return ClientUdpStatusCode::unauthorized_source;
  case BidMessageLogStatus::budget_exhausted:
    return ClientUdpStatusCode::insufficient_budget;
  case BidMessageLogStatus::expired_refunded:
  case BidMessageLogStatus::delivery_matched:
  case BidMessageLogStatus::delivery_unmatched:
    break;
  }
  return ClientUdpStatusCode::invalid_message_format;
}

void validate_ingress_config(const ClientUdpIngressConfig& config) {
  if (config.listen_port == 0U) {
    throw std::invalid_argument("client UDP listen_port is required");
  }
}

} // namespace

KernelClientUdpStatusSink::KernelClientUdpStatusSink() {
  socket_fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd_ < 0) {
    throw std::runtime_error(std::string("failed to create client status UDP socket: ") + std::strerror(errno));
  }
}

KernelClientUdpStatusSink::~KernelClientUdpStatusSink() {
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
}

KernelClientUdpStatusSink::KernelClientUdpStatusSink(KernelClientUdpStatusSink&& other) noexcept
    : socket_fd_(other.socket_fd_) {
  other.socket_fd_ = -1;
}

KernelClientUdpStatusSink& KernelClientUdpStatusSink::operator=(KernelClientUdpStatusSink&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
  socket_fd_ = other.socket_fd_;
  other.socket_fd_ = -1;
  return *this;
}

void KernelClientUdpStatusSink::send_client_status(const ClientEndpoint& endpoint,
                                                   ClientUdpStatusCode status,
                                                   std::uint32_t bid_price,
                                                   std::uint32_t winning_bid_price) {
  const auto payload = encode_client_udp_status(status, bid_price, winning_bid_price);
  sockaddr_in destination{};
  destination.sin_family = AF_INET;
  destination.sin_port = htons(endpoint.port);
  if (::inet_pton(AF_INET, endpoint.ip.c_str(), &destination.sin_addr) != 1) {
    throw std::invalid_argument("invalid client status destination IP");
  }
  const auto sent = ::sendto(socket_fd_,
                             payload.data(),
                             payload.size(),
                             0,
                             reinterpret_cast<const sockaddr*>(&destination),
                             sizeof(destination));
  if (sent != static_cast<ssize_t>(payload.size())) {
    throw std::runtime_error(std::string("failed to send client status UDP packet: ") + std::strerror(errno));
  }
}

ClientUdpMessageHandler::ClientUdpMessageHandler(ClientUdpIngressConfig config,
                                                 std::shared_ptr<ClientUdpStatusSink> status_sink,
                                                 std::shared_ptr<TransmitterControlState> control,
                                                 std::shared_ptr<BidBudgetAccountant> accountant)
    : config_(std::move(config)),
      status_sink_(std::move(status_sink)),
      control_(std::move(control)),
      accountant_(std::move(accountant)) {
  validate_ingress_config(config_);
  if (!status_sink_) {
    throw std::invalid_argument("ClientUdpMessageHandler requires status sink");
  }
  // Precompute parsed source addresses so the per-packet path avoids
  // inet_ntop / std::string compare. Anything malformed in config drops a
  // zero address, which never matches a real client source.
  for (std::size_t i = 0; i < config_.authorized_client_ips.size(); ++i) {
    in_addr addr{};
    if (!config_.authorized_client_ips[i].empty() &&
        ::inet_pton(AF_INET, config_.authorized_client_ips[i].c_str(), &addr) == 1) {
      authorized_client_addrs_[i] = addr.s_addr;
      authorized_client_present_[i] = true;
    } else {
      authorized_client_addrs_[i] = 0U;
      authorized_client_present_[i] = false;
    }
  }
}

ClientUdpHandleResult ClientUdpMessageHandler::handle_datagram(const ClientUdpDatagram& datagram,
                                                               std::uint32_t source_addr_be,
                                                               BidMessageTransmitIntake& intake,
                                                               TransmitMessageQueue& transmit_queue,
                                                               SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  ClientUdpHandleResult result;
  const auto client_id = source_addr_be != 0U
      ? client_id_for_source_addr(source_addr_be)
      : client_id_for_source(datagram.source.ip);
  const auto bid = datagram.payload.size() >= 4U
      ? read_u32_be(std::span<const std::uint8_t>(datagram.payload).first(4U))
      : 0U;
  result.bid_price = bid;
  if (!log_status(make_udp_ingress_log(datagram, bid, client_id), log_queue)) {
    result.log_backpressure = true;
  }

  if (!client_id.has_value()) {
    result.unauthorized = true;
    result.rejected = true;
    result.log_backpressure = !log_status(
        make_status_log(datagram, BidMessageLogStatus::unauthorized_source, bid, 0U, std::nullopt),
        log_queue) || result.log_backpressure;
    return result;
  }
  result.client_id = *client_id;
  if (control_ && !control_->receiver_client_alive(*client_id)) {
    result.rejected = true;
    result.log_backpressure = !log_status(
        make_status_log(datagram, BidMessageLogStatus::rejected, bid, 0U, client_id),
        log_queue) || result.log_backpressure;
    return result;
  }

  if (datagram.payload.size() < 6U || datagram.payload.size() > 13U ||
      !is_valid_client_message_payload(std::span<const std::uint8_t>(datagram.payload).subspan(4U))) {
    result.invalid = true;
    result.rejected = true;
    result.log_backpressure = !log_status(
        make_status_log(datagram, BidMessageLogStatus::invalid_message_format, bid, 0U, client_id),
        log_queue) || result.log_backpressure;
    return result;
  }

  const auto udp_message = std::span<const std::uint8_t>(datagram.payload).subspan(4U);
  std::vector<std::uint8_t> message_payload;
  message_payload.reserve(udp_message.size() + 1U);
  message_payload.push_back(udp_message[0]);
  message_payload.push_back(client_id_to_symbol(*client_id));
  message_payload.insert(message_payload.end(), udp_message.begin() + 1, udp_message.end());
  const auto intake_result = intake.submit(BidMessage{.payload = std::move(message_payload),
                                                      .bid_price = bid,
                                                      .client_id = *client_id,
                                                      .has_client_id = true,
                                                      .reply_ip = datagram.source.ip,
                                                      .reply_port = datagram.source.port},
                                           transmit_queue,
                                           log_queue,
                                           this,
                                           accountant_.get());
  result.accepted = !intake_result.log_backpressure;
  result.transmitted = intake_result.transmitted;
  result.queued_for_arbitration = intake_result.queued_for_arbitration;
  result.log_backpressure = result.log_backpressure || intake_result.log_backpressure;
  result.transmit_backpressure = intake_result.transmit_backpressure;
  result.budget_rejected = intake_result.budget_rejected;
  result.rejected = intake_result.budget_rejected;
  return result;
}

ClientUdpHandleResult ClientUdpMessageHandler::handle_datagram(const ClientUdpDatagram& datagram,
                                                               BidMessageTransmitIntake& intake,
                                                               TransmitMessageQueue& transmit_queue,
                                                               SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  return handle_datagram(datagram, 0U, intake, transmit_queue, log_queue);
}

BidMessageIntakeResult ClientUdpMessageHandler::pump_pending(BidMessageTransmitIntake& intake,
                                                             TransmitMessageQueue& transmit_queue,
                                                             SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  return intake.pump(transmit_queue, log_queue, this, accountant_.get());
}

void ClientUdpMessageHandler::on_bid_message_log(const BidMessageLogRecord& record) {
  if (record.event_type != LogEventType::udp_decision) {
    return;
  }
  if (record.reply_ip.empty() || record.reply_port == 0U) {
    return;
  }
  if (record.status == BidMessageLogStatus::unauthorized_source) {
    return;
  }
  status_sink_->send_client_status({.ip = record.reply_ip, .port = record.reply_port},
                                   status_code_for_log(record.status),
                                   static_cast<std::uint32_t>(record.bid_price),
                                   static_cast<std::uint32_t>(record.winning_bid_price));
}

std::optional<std::uint8_t> ClientUdpMessageHandler::client_id_for_source(std::string_view ip) const noexcept {
  for (std::size_t i = 0; i < config_.authorized_client_ips.size(); ++i) {
    if (!config_.authorized_client_ips[i].empty() && config_.authorized_client_ips[i] == ip) {
      return static_cast<std::uint8_t>(i);
    }
  }
  return std::nullopt;
}

std::optional<std::uint8_t> ClientUdpMessageHandler::client_id_for_source_addr(std::uint32_t addr) const noexcept {
  for (std::size_t i = 0; i < authorized_client_addrs_.size(); ++i) {
    if (authorized_client_present_[i] && authorized_client_addrs_[i] == addr) {
      return static_cast<std::uint8_t>(i);
    }
  }
  return std::nullopt;
}

bool ClientUdpMessageHandler::log_status(BidMessageLogRecord record,
                                         SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  if (log_queue.full()) {
    return false;
  }
  const auto copy = record;
  if (!log_queue.try_push(std::move(record))) {
    return false;
  }
  on_bid_message_log(copy);
  return true;
}

ClientUdpIngressSocket::ClientUdpIngressSocket(ClientUdpIngressConfig config,
                                               std::shared_ptr<ClientUdpStatusSink> status_sink,
                                               std::shared_ptr<TransmitterControlState> control,
                                               std::shared_ptr<BidBudgetAccountant> accountant)
    : handler_(config, std::move(status_sink), std::move(control), std::move(accountant)) {
  validate_ingress_config(config);
  if (config.backend == ClientUdpBackend::dpdk) {
    throw std::runtime_error("DPDK client UDP ingress requested, but goblin_cannon was built without DPDK support");
  }

  socket_fd_ = ::socket(AF_INET, SOCK_DGRAM, 0);
  if (socket_fd_ < 0) {
    throw std::runtime_error(std::string("failed to create client UDP ingress socket: ") + std::strerror(errno));
  }
  sockaddr_in address{};
  address.sin_family = AF_INET;
  address.sin_port = htons(config.listen_port);
  if (::inet_pton(AF_INET, config.listen_ip.c_str(), &address.sin_addr) != 1) {
    ::close(socket_fd_);
    socket_fd_ = -1;
    throw std::invalid_argument("invalid client UDP listen_ip");
  }
  if (::bind(socket_fd_, reinterpret_cast<sockaddr*>(&address), sizeof(address)) != 0) {
    ::close(socket_fd_);
    socket_fd_ = -1;
    throw std::runtime_error(std::string("failed to bind client UDP ingress socket: ") + std::strerror(errno));
  }
  const auto flags = ::fcntl(socket_fd_, F_GETFL, 0);
  if (flags >= 0) {
    (void)::fcntl(socket_fd_, F_SETFL, flags | O_NONBLOCK);
  }
}

ClientUdpIngressSocket::~ClientUdpIngressSocket() {
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
}

ClientUdpIngressSocket::ClientUdpIngressSocket(ClientUdpIngressSocket&& other) noexcept
    : handler_(std::move(other.handler_)),
      socket_fd_(other.socket_fd_) {
  other.socket_fd_ = -1;
}

ClientUdpIngressSocket& ClientUdpIngressSocket::operator=(ClientUdpIngressSocket&& other) noexcept {
  if (this == &other) {
    return *this;
  }
  if (socket_fd_ >= 0) {
    ::close(socket_fd_);
  }
  handler_ = std::move(other.handler_);
  socket_fd_ = other.socket_fd_;
  other.socket_fd_ = -1;
  return *this;
}

ClientUdpHandleResult ClientUdpIngressSocket::poll_once(BidMessageTransmitIntake& intake,
                                                        TransmitMessageQueue& transmit_queue,
                                                        SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  std::array<std::uint8_t, 1500> bytes{};
  sockaddr_in source{};
  socklen_t source_size = sizeof(source);
  const auto n = ::recvfrom(socket_fd_,
                            bytes.data(),
                            bytes.size(),
                            0,
                            reinterpret_cast<sockaddr*>(&source),
                            &source_size);
  if (n < 0) {
    if (errno == EAGAIN || errno == EWOULDBLOCK) {
      return {};
    }
    throw std::runtime_error(std::string("failed to receive client UDP datagram: ") + std::strerror(errno));
  }

  char ip[INET_ADDRSTRLEN]{};
  if (::inet_ntop(AF_INET, &source.sin_addr, ip, sizeof(ip)) == nullptr) {
    throw std::runtime_error("failed to format client UDP source address");
  }
  return handler_.handle_datagram(
      ClientUdpDatagram{.source = {.ip = ip, .port = ntohs(source.sin_port)},
                        .payload = std::vector<std::uint8_t>(bytes.begin(), bytes.begin() + n)},
      source.sin_addr.s_addr,
      intake,
      transmit_queue,
      log_queue);
}

BidMessageIntakeResult ClientUdpIngressSocket::pump_pending(BidMessageTransmitIntake& intake,
                                                            TransmitMessageQueue& transmit_queue,
                                                            SpscRingBuffer<BidMessageLogRecord>& log_queue) {
  return handler_.pump_pending(intake, transmit_queue, log_queue);
}

bool ClientUdpIngressSocket::wait_for_data(int timeout_ms) const noexcept {
  if (socket_fd_ < 0) {
    return false;
  }
  pollfd pfd{.fd = socket_fd_, .events = POLLIN, .revents = 0};
  int rc = 0;
  do {
    rc = ::poll(&pfd, 1, timeout_ms);
  } while (rc < 0 && errno == EINTR);
  return rc > 0 && (pfd.revents & POLLIN) != 0;
}

ClientUdpIngressConfig load_client_udp_ingress_config(const std::filesystem::path& path) {
  std::ifstream in(path);
  if (!in) {
    throw std::runtime_error("failed to open client UDP ingress config file");
  }

  ClientUdpIngressConfig config;
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
        throw std::invalid_argument("invalid client UDP ingress config line " + std::to_string(line_number));
      }
      continue;
    }
    const auto key = trim(std::string_view(line).substr(0, equals));
    const auto value = trim(std::string_view(line).substr(equals + 1U));
    if (key == "backend") {
      if (value == "kernel_udp") {
        config.backend = ClientUdpBackend::kernel_udp;
      } else if (value == "dpdk") {
        config.backend = ClientUdpBackend::dpdk;
      } else {
        throw std::invalid_argument("client UDP backend must be kernel_udp or dpdk");
      }
    } else if (key == "listen_ip") {
      config.listen_ip = value;
    } else if (key == "listen_port") {
      config.listen_port = parse_u16(value, key);
    } else if (key.starts_with("client.") && key.ends_with(".ip")) {
      const auto id_text = std::string_view(key).substr(7U, key.size() - 10U);
      const auto id = parse_u32(id_text, key);
      if (id >= Clients) {
        throw std::invalid_argument("client UDP config client id outside Clients range");
      }
      config.authorized_client_ips[id] = value;
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
    } else {
      throw std::invalid_argument("unknown client UDP ingress config key: " + key);
    }
  }
  validate_ingress_config(config);
  return config;
}

ClientExpectedLatenciesNs load_client_expected_latencies_ns_config(const std::filesystem::path& path,
                                                                   std::uint64_t default_latency_ns) {
  std::ifstream in(path);
  if (!in) {
    throw std::runtime_error("failed to open client expected latency config file");
  }

  ClientExpectedLatenciesNs latencies{};
  latencies.fill(default_latency_ns);
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
        throw std::invalid_argument("invalid client latency config line " + std::to_string(line_number));
      }
      continue;
    }
    const auto key = trim(std::string_view(line).substr(0, equals));
    const auto value = trim(std::string_view(line).substr(equals + 1U));
    if (key.starts_with("client.") && key.ends_with(".expected_latency_ns")) {
      const auto id_text = std::string_view(key).substr(7U, key.size() - 27U);
      const auto id = parse_u32(id_text, key);
      if (id >= Clients) {
        throw std::invalid_argument("client latency config client id outside Clients range");
      }
      latencies[id] = parse_u64(value, key);
    } else {
      const auto id = parse_u32(key, key);
      if (id >= Clients) {
        throw std::invalid_argument("client latency config client id outside Clients range");
      }
      latencies[id] = parse_u64(value, key);
    }
  }
  return latencies;
}

std::array<std::uint8_t, 9> encode_client_udp_status(ClientUdpStatusCode status,
                                                     std::uint32_t bid_price,
                                                     std::uint32_t winning_bid_price) {
  std::array<std::uint8_t, 9> payload{};
  payload[0] = static_cast<std::uint8_t>(status);
  write_u32_be(std::span<std::uint8_t, 4>(payload.data() + 1U, 4U), bid_price);
  write_u32_be(std::span<std::uint8_t, 4>(payload.data() + 5U, 4U), winning_bid_price);
  return payload;
}

} // namespace goblin_cannon
