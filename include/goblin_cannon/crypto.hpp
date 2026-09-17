#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>
#include <string>
#include <atomic>
#include <vector>

namespace goblin_cannon {

struct Aes256Key { std::array<std::uint8_t, 32> bytes{}; };
using GcmNonce = std::array<std::uint8_t, 12>;
using GcmTag = std::array<std::uint8_t, 16>;

// Provision once for a transmitter/key domain. Missing, truncated or damaged
// state is fatal: replacing/restoring this file requires a NEW encryption key.
void initialize_transmitter_epoch_store(const std::string& path);
class TransmitterEpoch {
public:
  [[nodiscard]] static std::shared_ptr<TransmitterEpoch> reserve(const std::string& path,
                                                               std::uint64_t minimum = 1);
  [[nodiscard]] std::uint64_t value() const noexcept { return value_; }
  // A copied configuration must never instantiate two senders with one epoch.
  void claim();
private:
  explicit TransmitterEpoch(std::uint64_t value) : value_(value) {}
  std::uint64_t value_;
  std::atomic<bool> claimed_{false};
};
[[nodiscard]] GcmNonce message_nonce(std::uint64_t epoch, std::uint32_t sequence);

// OpenSSL contexts and key schedules are retained. Only the explicit nonce is
// changed per record. Decryption uses private scratch space until Final succeeds.
class Aes256Gcm {
public:
  explicit Aes256Gcm(const Aes256Key& key);
  ~Aes256Gcm();
  Aes256Gcm(const Aes256Gcm&) = delete;
  Aes256Gcm& operator=(const Aes256Gcm&) = delete;
  void seal(const GcmNonce&, std::span<const std::uint8_t> ad,
            std::span<const std::uint8_t> plain, std::vector<std::uint8_t>& cipher, GcmTag& tag);
  [[nodiscard]] bool open(const GcmNonce&, std::span<const std::uint8_t> ad,
                          std::span<const std::uint8_t> cipher, const GcmTag& tag,
                          std::vector<std::uint8_t>& plain);
private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

// Legacy bit-stream test helpers. Production messages use AES-256-GCM above.
inline constexpr std::size_t aes128_key_bytes = 16;
inline constexpr std::size_t aes128_block_bytes = 16;

struct Aes128Key {
  std::array<std::uint8_t, aes128_key_bytes> bytes{};
};

using Aes128CtrCounter = std::array<std::uint8_t, aes128_block_bytes>;

class Aes128CtrKeystream {
public:
  explicit Aes128CtrKeystream(Aes128Key key, Aes128CtrCounter initial_counter = {});
  ~Aes128CtrKeystream();

  Aes128CtrKeystream(const Aes128CtrKeystream&) = delete;
  Aes128CtrKeystream& operator=(const Aes128CtrKeystream&) = delete;
  Aes128CtrKeystream(Aes128CtrKeystream&&) noexcept;
  Aes128CtrKeystream& operator=(Aes128CtrKeystream&&) noexcept;

  void generate(std::span<std::uint8_t> out);
  void xor_bytes(std::span<const std::uint8_t> in, std::span<std::uint8_t> out);

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace goblin_cannon
