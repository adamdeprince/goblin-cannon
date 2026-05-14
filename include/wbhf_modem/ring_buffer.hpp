#pragma once

#include <atomic>
#include <cstddef>
#include <optional>
#include <span>
#include <stdexcept>
#include <type_traits>
#include <utility>
#include <vector>

namespace wbhf_modem {

template <typename T>
class SpscRingBuffer {
public:
  explicit SpscRingBuffer(std::size_t capacity)
      : slots_(capacity + 1U) {
    if (capacity == 0) {
      throw std::invalid_argument("SpscRingBuffer capacity must be positive");
    }
  }

  SpscRingBuffer(const SpscRingBuffer&) = delete;
  SpscRingBuffer& operator=(const SpscRingBuffer&) = delete;

  [[nodiscard]] std::size_t capacity() const noexcept { return slots_.size() - 1U; }

  [[nodiscard]] bool empty() const noexcept {
    return read_.load(std::memory_order_acquire) == write_.load(std::memory_order_acquire);
  }

  [[nodiscard]] bool full() const noexcept {
    const auto next = increment(write_.load(std::memory_order_relaxed));
    return next == read_.load(std::memory_order_acquire);
  }

  [[nodiscard]] std::size_t size_approx() const noexcept {
    const auto read = read_.load(std::memory_order_acquire);
    const auto write = write_.load(std::memory_order_acquire);
    return write >= read ? write - read : slots_.size() - read + write;
  }

  bool try_push(const T& value) {
    const auto write = write_.load(std::memory_order_relaxed);
    const auto next = increment(write);
    if (next == read_.load(std::memory_order_acquire)) {
      return false;
    }
    slots_[write] = value;
    write_.store(next, std::memory_order_release);
    return true;
  }

  bool try_push(T&& value) {
    const auto write = write_.load(std::memory_order_relaxed);
    const auto next = increment(write);
    if (next == read_.load(std::memory_order_acquire)) {
      return false;
    }
    slots_[write] = std::move(value);
    write_.store(next, std::memory_order_release);
    return true;
  }

  std::size_t try_push(std::span<const T> values) {
    std::size_t pushed = 0;
    while (pushed < values.size() && try_push(values[pushed])) {
      ++pushed;
    }
    return pushed;
  }

  bool try_pop(T& out) {
    const auto read = read_.load(std::memory_order_relaxed);
    if (read == write_.load(std::memory_order_acquire)) {
      return false;
    }
    out = std::move(slots_[read]);
    read_.store(increment(read), std::memory_order_release);
    return true;
  }

  [[nodiscard]] std::optional<T> try_pop() {
    T value{};
    if (!try_pop(value)) {
      return std::nullopt;
    }
    return value;
  }

  std::size_t try_pop(std::span<T> out) {
    std::size_t popped = 0;
    while (popped < out.size() && try_pop(out[popped])) {
      ++popped;
    }
    return popped;
  }

private:
  [[nodiscard]] std::size_t increment(std::size_t index) const noexcept {
    ++index;
    return index == slots_.size() ? 0U : index;
  }

  std::vector<T> slots_;
  alignas(64) std::atomic<std::size_t> read_ = 0;
  alignas(64) std::atomic<std::size_t> write_ = 0;
};

} // namespace wbhf_modem
