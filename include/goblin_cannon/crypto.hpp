#pragma once

#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <span>

namespace goblin_cannon {

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
