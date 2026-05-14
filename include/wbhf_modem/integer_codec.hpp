#pragma once

#include "wbhf_modem/message_stream.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <vector>

namespace wbhf_modem {

inline constexpr std::uint8_t base254_min_byte = 2;
inline constexpr std::uint8_t base254_max_byte = 255;
inline constexpr std::uint16_t base254_radix = 254;

struct BankSymbolInteger {
  std::uint8_t bank = 0;
  std::uint8_t symbol = base254_min_byte;
  std::int64_t value = 0;
};

[[nodiscard]] bool is_base254_digit(std::uint8_t byte) noexcept;
[[nodiscard]] std::uint64_t zigzag_encode_i64(std::int64_t value) noexcept;
[[nodiscard]] std::int64_t zigzag_decode_i64(std::uint64_t value) noexcept;

void append_base254_varuint(std::uint64_t value, std::vector<std::uint8_t>& out);
[[nodiscard]] std::vector<std::uint8_t> encode_base254_varuint(std::uint64_t value);
[[nodiscard]] std::optional<std::uint64_t> decode_base254_varuint(std::span<const std::uint8_t> bytes) noexcept;

void append_base254_zigzag(std::int64_t value, std::vector<std::uint8_t>& out);
[[nodiscard]] std::vector<std::uint8_t> encode_base254_zigzag(std::int64_t value);
[[nodiscard]] std::optional<std::int64_t> decode_base254_zigzag(std::span<const std::uint8_t> bytes) noexcept;

[[nodiscard]] DelimitedMessage encode_bank_symbol_integer(std::uint8_t bank,
                                                          std::uint8_t symbol,
                                                          std::int64_t value);
[[nodiscard]] DelimitedMessage encode_bank_symbol_integer(const BankSymbolInteger& message);
[[nodiscard]] std::optional<BankSymbolInteger> decode_bank_symbol_integer(
    const DelimitedMessage& message) noexcept;
[[nodiscard]] std::optional<BankSymbolInteger> decode_bank_symbol_integer(
    std::span<const std::uint8_t> bytes) noexcept;

} // namespace wbhf_modem
