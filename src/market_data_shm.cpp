#include "wbhf_modem/market_data_shm.hpp"

#include <algorithm>
#include <cerrno>
#include <cstring>
#include <stdexcept>
#include <string>
#include <utility>

#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

namespace wbhf_modem {

namespace {

constexpr std::size_t magic_offset = 0U;
constexpr std::size_t version_offset = 4U;
constexpr std::size_t capacity_offset = 8U;
constexpr std::size_t payload_bytes_offset = 12U;
constexpr std::size_t slot_stride_offset = 16U;
constexpr std::size_t read_seq_offset = 24U;
constexpr std::size_t write_seq_offset = 32U;
constexpr std::size_t dropped_full_offset = 40U;
constexpr std::size_t dropped_oversize_offset = 48U;
constexpr std::size_t invalid_records_offset = 56U;

constexpr std::size_t slot_seq_offset = 0U;
constexpr std::size_t slot_bid_offset = 8U;
constexpr std::size_t slot_size_offset = 16U;
constexpr std::size_t slot_flags_offset = 20U;
constexpr std::size_t slot_payload_offset = 24U;

std::string errno_message(const std::string& prefix) {
  return prefix + ": " + std::strerror(errno);
}

std::uint32_t align64(std::uint32_t value) noexcept {
  return (value + 63U) & ~std::uint32_t{63U};
}

std::uint32_t load_u32(const std::uint8_t* data, std::size_t offset) noexcept {
  std::uint32_t value = 0;
  std::memcpy(&value, data + offset, sizeof(value));
  return value;
}

void store_u32(std::uint8_t* data, std::size_t offset, std::uint32_t value) noexcept {
  std::memcpy(data + offset, &value, sizeof(value));
}

std::uint64_t load_u64(const std::uint8_t* data, std::size_t offset) noexcept {
  const auto* value = reinterpret_cast<const std::uint64_t*>(data + offset);
  return __atomic_load_n(value, __ATOMIC_ACQUIRE);
}

void store_u64(std::uint8_t* data, std::size_t offset, std::uint64_t value) noexcept {
  auto* target = reinterpret_cast<std::uint64_t*>(data + offset);
  __atomic_store_n(target, value, __ATOMIC_RELEASE);
}

std::uint64_t fetch_add_u64(std::uint8_t* data, std::size_t offset, std::uint64_t delta) noexcept {
  auto* target = reinterpret_cast<std::uint64_t*>(data + offset);
  return __atomic_fetch_add(target, delta, __ATOMIC_ACQ_REL);
}

std::size_t total_bytes(std::uint32_t capacity, std::uint32_t slot_stride) noexcept {
  return market_data_shm_header_bytes + static_cast<std::size_t>(capacity) * slot_stride;
}

std::size_t slot_offset(std::uint64_t sequence,
                        std::uint32_t capacity,
                        std::uint32_t slot_stride) noexcept {
  return market_data_shm_header_bytes +
         static_cast<std::size_t>(sequence % capacity) * static_cast<std::size_t>(slot_stride);
}

void validate_dimensions(std::uint32_t capacity, std::uint32_t payload_bytes) {
  if (capacity == 0U) {
    throw std::invalid_argument("market data shared-memory capacity must be positive");
  }
  if (payload_bytes < 2U) {
    throw std::invalid_argument("market data shared-memory payload bytes must be at least 2");
  }
}

void validate_header(const std::uint8_t* data, std::size_t mapped_bytes) {
  if (mapped_bytes < market_data_shm_header_bytes) {
    throw std::runtime_error("market data shared-memory file is too small");
  }
  if (load_u32(data, magic_offset) != market_data_shm_magic) {
    throw std::runtime_error("market data shared-memory ring is not initialized");
  }
  if (load_u32(data, version_offset) != market_data_shm_version) {
    throw std::runtime_error("market data shared-memory version mismatch");
  }
  const auto capacity = load_u32(data, capacity_offset);
  const auto payload_bytes = load_u32(data, payload_bytes_offset);
  const auto slot_stride = load_u32(data, slot_stride_offset);
  validate_dimensions(capacity, payload_bytes);
  if (slot_stride != align64(static_cast<std::uint32_t>(market_data_shm_slot_metadata_bytes) + payload_bytes)) {
    throw std::runtime_error("market data shared-memory slot stride mismatch");
  }
  if (mapped_bytes < total_bytes(capacity, slot_stride)) {
    throw std::runtime_error("market data shared-memory file does not contain the configured ring");
  }
}

} // namespace

MarketDataShmConsumer::MarketDataShmConsumer(MarketDataShmConfig config) {
  initialize(std::move(config));
}

MarketDataShmConsumer::~MarketDataShmConsumer() {
  close();
}

void MarketDataShmConsumer::initialize(MarketDataShmConfig config) {
  validate_dimensions(config.capacity, config.payload_bytes);
  capacity_ = config.capacity;
  payload_bytes_ = config.payload_bytes;
  slot_stride_ = align64(static_cast<std::uint32_t>(market_data_shm_slot_metadata_bytes) + payload_bytes_);
  mapped_bytes_ = total_bytes(capacity_, slot_stride_);

  if (config.path.has_parent_path()) {
    std::filesystem::create_directories(config.path.parent_path());
  }

  fd_ = ::open(config.path.c_str(), O_RDWR | O_CREAT | O_CLOEXEC, 0600);
  if (fd_ < 0) {
    throw std::runtime_error(errno_message("failed to open market data shared-memory ring"));
  }
  if (::ftruncate(fd_, static_cast<off_t>(mapped_bytes_)) != 0) {
    close();
    throw std::runtime_error(errno_message("failed to size market data shared-memory ring"));
  }
  data_ = static_cast<std::uint8_t*>(::mmap(nullptr, mapped_bytes_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
  if (data_ == MAP_FAILED) {
    data_ = nullptr;
    close();
    throw std::runtime_error(errno_message("failed to map market data shared-memory ring"));
  }

  std::memset(data_, 0, mapped_bytes_);
  store_u32(data_, version_offset, market_data_shm_version);
  store_u32(data_, capacity_offset, capacity_);
  store_u32(data_, payload_bytes_offset, payload_bytes_);
  store_u32(data_, slot_stride_offset, slot_stride_);
  store_u64(data_, read_seq_offset, 0U);
  store_u64(data_, write_seq_offset, 0U);
  store_u32(data_, magic_offset, market_data_shm_magic);
}

bool MarketDataShmConsumer::try_pop(BidMessage& out) {
  const auto read_seq = load_u64(data_, read_seq_offset);
  const auto write_seq = load_u64(data_, write_seq_offset);
  if (read_seq == write_seq) {
    return false;
  }

  const auto offset = slot_offset(read_seq, capacity_, slot_stride_);
  const auto committed_seq = load_u64(data_, offset + slot_seq_offset);
  if (committed_seq != read_seq + 1U) {
    fetch_add_u64(data_, invalid_records_offset, 1U);
    return false;
  }

  const auto payload_size = load_u32(data_, offset + slot_size_offset);
  (void)load_u32(data_, offset + slot_flags_offset);
  if (payload_size == 0U || payload_size > payload_bytes_) {
    fetch_add_u64(data_, invalid_records_offset, 1U);
    store_u64(data_, read_seq_offset, read_seq + 1U);
    return false;
  }

  out.payload.resize(payload_size);
  std::copy_n(data_ + offset + slot_payload_offset,
              static_cast<std::ptrdiff_t>(payload_size),
              out.payload.begin());
  out.bid_price = load_u64(data_, offset + slot_bid_offset);
  out.client_id = 0;
  out.has_client_id = false;
  out.reply_ip.clear();
  out.reply_port = 0;
  store_u64(data_, read_seq_offset, read_seq + 1U);
  return true;
}

MarketDataShmStats MarketDataShmConsumer::stats() const noexcept {
  return {.read_seq = load_u64(data_, read_seq_offset),
          .write_seq = load_u64(data_, write_seq_offset),
          .dropped_full = load_u64(data_, dropped_full_offset),
          .dropped_oversize = load_u64(data_, dropped_oversize_offset),
          .invalid_records = load_u64(data_, invalid_records_offset)};
}

void MarketDataShmConsumer::close() noexcept {
  if (data_ != nullptr) {
    (void)::munmap(data_, mapped_bytes_);
    data_ = nullptr;
  }
  if (fd_ >= 0) {
    (void)::close(fd_);
    fd_ = -1;
  }
}

MarketDataShmProducer::MarketDataShmProducer(std::filesystem::path path) {
  open_existing(path);
}

MarketDataShmProducer::~MarketDataShmProducer() {
  close();
}

void MarketDataShmProducer::open_existing(const std::filesystem::path& path) {
  fd_ = ::open(path.c_str(), O_RDWR | O_CLOEXEC);
  if (fd_ < 0) {
    throw std::runtime_error(errno_message("failed to open existing market data shared-memory ring"));
  }

  struct stat info {};
  if (::fstat(fd_, &info) != 0) {
    close();
    throw std::runtime_error(errno_message("failed to stat market data shared-memory ring"));
  }
  if (info.st_size <= 0) {
    close();
    throw std::runtime_error("market data shared-memory ring is empty");
  }
  mapped_bytes_ = static_cast<std::size_t>(info.st_size);
  data_ = static_cast<std::uint8_t*>(::mmap(nullptr, mapped_bytes_, PROT_READ | PROT_WRITE, MAP_SHARED, fd_, 0));
  if (data_ == MAP_FAILED) {
    data_ = nullptr;
    close();
    throw std::runtime_error(errno_message("failed to map existing market data shared-memory ring"));
  }
  validate_header(data_, mapped_bytes_);
  capacity_ = load_u32(data_, capacity_offset);
  payload_bytes_ = load_u32(data_, payload_bytes_offset);
  slot_stride_ = load_u32(data_, slot_stride_offset);
}

bool MarketDataShmProducer::try_push(std::span<const std::uint8_t> payload, std::uint64_t bid_cents) {
  if (payload.size() > payload_bytes_) {
    fetch_add_u64(data_, dropped_oversize_offset, 1U);
    return false;
  }
  if (payload.size() < 2U) {
    fetch_add_u64(data_, invalid_records_offset, 1U);
    return false;
  }

  const auto read_seq = load_u64(data_, read_seq_offset);
  const auto write_seq = load_u64(data_, write_seq_offset);
  if (write_seq - read_seq >= capacity_) {
    fetch_add_u64(data_, dropped_full_offset, 1U);
    return false;
  }

  const auto offset = slot_offset(write_seq, capacity_, slot_stride_);
  store_u64(data_, offset + slot_seq_offset, 0U);
  store_u64(data_, offset + slot_bid_offset, bid_cents);
  store_u32(data_, offset + slot_size_offset, static_cast<std::uint32_t>(payload.size()));
  store_u32(data_, offset + slot_flags_offset, 0U);
  std::copy(payload.begin(), payload.end(), data_ + offset + slot_payload_offset);
  store_u64(data_, offset + slot_seq_offset, write_seq + 1U);
  store_u64(data_, write_seq_offset, write_seq + 1U);
  return true;
}

MarketDataShmStats MarketDataShmProducer::stats() const noexcept {
  return {.read_seq = load_u64(data_, read_seq_offset),
          .write_seq = load_u64(data_, write_seq_offset),
          .dropped_full = load_u64(data_, dropped_full_offset),
          .dropped_oversize = load_u64(data_, dropped_oversize_offset),
          .invalid_records = load_u64(data_, invalid_records_offset)};
}

void MarketDataShmProducer::close() noexcept {
  if (data_ != nullptr) {
    (void)::munmap(data_, mapped_bytes_);
    data_ = nullptr;
  }
  if (fd_ >= 0) {
    (void)::close(fd_);
    fd_ = -1;
  }
}

} // namespace wbhf_modem
