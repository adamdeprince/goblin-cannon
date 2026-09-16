#include "goblin_cannon/integer_codec.hpp"

#include <limits>
#include <stdexcept>
#include <utility>

namespace goblin_cannon {

namespace {

bool is_bank(std::uint8_t byte) noexcept {
  return byte == 0U || byte == 1U;
}

void validate_bank_symbol(std::uint8_t bank, std::uint8_t symbol) {
  if (!is_bank(bank)) {
    throw std::invalid_argument("bank delimiter must be byte 0 or 1");
  }
  if (!is_base254_digit(symbol)) {
    throw std::invalid_argument("symbol byte must be in [2, 255]");
  }
}

} // namespace

bool is_base254_digit(std::uint8_t byte) noexcept {
  return byte >= base254_min_byte;
}

std::uint64_t zigzag_encode_i64(std::int64_t value) noexcept {
  const auto unsigned_value = static_cast<std::uint64_t>(value);
  const auto sign = value < 0 ? std::numeric_limits<std::uint64_t>::max() : 0U;
  return (unsigned_value << 1U) ^ sign;
}

std::int64_t zigzag_decode_i64(std::uint64_t value) noexcept {
  const auto magnitude = value >> 1U;
  if ((value & 1U) == 0U) {
    return static_cast<std::int64_t>(magnitude);
  }
  return static_cast<std::int64_t>(-static_cast<std::int64_t>(magnitude) - 1);
}

void append_base254_varuint(std::uint64_t value, std::vector<std::uint8_t>& out) {
  do {
    const auto digit = static_cast<std::uint8_t>(value % base254_radix);
    out.push_back(static_cast<std::uint8_t>(base254_min_byte + digit));
    value /= base254_radix;
  } while (value != 0U);
}

std::vector<std::uint8_t> encode_base254_varuint(std::uint64_t value) {
  std::vector<std::uint8_t> out;
  append_base254_varuint(value, out);
  return out;
}

std::optional<std::uint64_t> decode_base254_varuint(std::span<const std::uint8_t> bytes) noexcept {
  if (bytes.empty()) {
    return std::nullopt;
  }

  const auto high_digit = static_cast<std::uint8_t>(bytes.back() - base254_min_byte);
  if (bytes.size() > 1U && high_digit == 0U) {
    return std::nullopt;
  }

  std::uint64_t value = 0;
  std::uint64_t multiplier = 1;
  constexpr auto max = std::numeric_limits<std::uint64_t>::max();

  for (std::size_t i = 0; i < bytes.size(); ++i) {
    const auto byte = bytes[i];
    if (!is_base254_digit(byte)) {
      return std::nullopt;
    }

    const auto digit = static_cast<std::uint64_t>(byte - base254_min_byte);
    if (digit != 0U && multiplier > (max - value) / digit) {
      return std::nullopt;
    }
    value += digit * multiplier;

    if (i + 1U < bytes.size()) {
      if (multiplier > max / base254_radix) {
        return std::nullopt;
      }
      multiplier *= base254_radix;
    }
  }

  return value;
}

void append_base254_zigzag(std::int64_t value, std::vector<std::uint8_t>& out) {
  append_base254_varuint(zigzag_encode_i64(value), out);
}

std::vector<std::uint8_t> encode_base254_zigzag(std::int64_t value) {
  return encode_base254_varuint(zigzag_encode_i64(value));
}

std::optional<std::int64_t> decode_base254_zigzag(std::span<const std::uint8_t> bytes) noexcept {
  const auto decoded = decode_base254_varuint(bytes);
  if (!decoded.has_value()) {
    return std::nullopt;
  }
  return zigzag_decode_i64(*decoded);
}

DelimitedMessage encode_bank_symbol_integer(std::uint8_t bank,
                                            std::uint8_t symbol,
                                            std::int64_t value) {
  validate_bank_symbol(bank, symbol);

  DelimitedMessage message;
  message.bytes.reserve(3);
  message.bytes.push_back(bank);
  message.bytes.push_back(symbol);
  append_base254_zigzag(value, message.bytes);
  return message;
}

DelimitedMessage encode_bank_symbol_integer(const BankSymbolInteger& message) {
  return encode_bank_symbol_integer(message.bank, message.symbol, message.value);
}

std::optional<BankSymbolInteger> decode_bank_symbol_integer(const DelimitedMessage& message) noexcept {
  return decode_bank_symbol_integer(std::span<const std::uint8_t>(message.bytes));
}

std::optional<BankSymbolInteger> decode_bank_symbol_integer(std::span<const std::uint8_t> bytes) noexcept {
  if (bytes.size() < 3U || !is_bank(bytes[0]) || !is_base254_digit(bytes[1])) {
    return std::nullopt;
  }
  const auto value = decode_base254_zigzag(bytes.subspan(2));
  if (!value.has_value()) {
    return std::nullopt;
  }
  return BankSymbolInteger{.bank = bytes[0], .symbol = bytes[1], .value = *value};
}

} // namespace goblin_cannon
