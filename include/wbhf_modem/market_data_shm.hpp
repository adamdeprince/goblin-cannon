#pragma once

#include "wbhf_modem/message_stream.hpp"

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <span>

namespace wbhf_modem {

inline constexpr std::uint32_t market_data_shm_magic = 0x544B4D57U;
inline constexpr std::uint32_t market_data_shm_version = 1U;
inline constexpr std::size_t market_data_shm_header_bytes = 128U;
inline constexpr std::size_t market_data_shm_slot_metadata_bytes = 24U;

struct MarketDataShmConfig {
  std::filesystem::path path = "/dev/shm/wbhf_market_data_ring";
  std::uint32_t capacity = 256;
  std::uint32_t payload_bytes = 64;
};

struct MarketDataShmStats {
  std::uint64_t read_seq = 0;
  std::uint64_t write_seq = 0;
  std::uint64_t dropped_full = 0;
  std::uint64_t dropped_oversize = 0;
  std::uint64_t invalid_records = 0;
};

class MarketDataShmConsumer {
public:
  explicit MarketDataShmConsumer(MarketDataShmConfig config);
  ~MarketDataShmConsumer();

  MarketDataShmConsumer(const MarketDataShmConsumer&) = delete;
  MarketDataShmConsumer& operator=(const MarketDataShmConsumer&) = delete;
  MarketDataShmConsumer(MarketDataShmConsumer&&) noexcept = delete;
  MarketDataShmConsumer& operator=(MarketDataShmConsumer&&) noexcept = delete;

  [[nodiscard]] bool try_pop(BidMessage& out);
  [[nodiscard]] MarketDataShmStats stats() const noexcept;
  [[nodiscard]] std::uint32_t capacity() const noexcept { return capacity_; }
  [[nodiscard]] std::uint32_t payload_bytes() const noexcept { return payload_bytes_; }
  [[nodiscard]] std::uint32_t slot_stride() const noexcept { return slot_stride_; }

private:
  void initialize(MarketDataShmConfig config);
  void close() noexcept;

  int fd_ = -1;
  std::uint8_t* data_ = nullptr;
  std::size_t mapped_bytes_ = 0;
  std::uint32_t capacity_ = 0;
  std::uint32_t payload_bytes_ = 0;
  std::uint32_t slot_stride_ = 0;
};

class MarketDataShmProducer {
public:
  explicit MarketDataShmProducer(std::filesystem::path path);
  ~MarketDataShmProducer();

  MarketDataShmProducer(const MarketDataShmProducer&) = delete;
  MarketDataShmProducer& operator=(const MarketDataShmProducer&) = delete;
  MarketDataShmProducer(MarketDataShmProducer&&) noexcept = delete;
  MarketDataShmProducer& operator=(MarketDataShmProducer&&) noexcept = delete;

  [[nodiscard]] bool try_push(std::span<const std::uint8_t> payload, std::uint64_t bid_cents);
  [[nodiscard]] MarketDataShmStats stats() const noexcept;
  [[nodiscard]] std::uint32_t capacity() const noexcept { return capacity_; }
  [[nodiscard]] std::uint32_t payload_bytes() const noexcept { return payload_bytes_; }
  [[nodiscard]] std::uint32_t slot_stride() const noexcept { return slot_stride_; }

private:
  void open_existing(const std::filesystem::path& path);
  void close() noexcept;

  int fd_ = -1;
  std::uint8_t* data_ = nullptr;
  std::size_t mapped_bytes_ = 0;
  std::uint32_t capacity_ = 0;
  std::uint32_t payload_bytes_ = 0;
  std::uint32_t slot_stride_ = 0;
};

} // namespace wbhf_modem
