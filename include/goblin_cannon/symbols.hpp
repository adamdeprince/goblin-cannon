#pragma once

#include <cstddef>
#include <cstdint>
#include <stdexcept>
#include <string>

namespace goblin_cannon {

inline constexpr std::size_t Clients = 20;
inline constexpr std::uint8_t symbol_min_byte = 2;
inline constexpr std::uint8_t symbol_max_byte = 255;
inline constexpr std::size_t total_symbol_count = 254;
inline constexpr std::size_t symbol_permission_mask_bytes = (total_symbol_count + 7U) / 8U;
inline constexpr std::size_t market_symbol_count = total_symbol_count - Clients;
inline constexpr std::uint8_t client_symbol_base = 256 - Clients;
inline constexpr std::uint8_t market_symbol_max_byte = client_symbol_base - 1;

[[nodiscard]] inline bool is_symbol_byte(std::uint8_t symbol) noexcept {
  return symbol >= symbol_min_byte;
}

[[nodiscard]] inline bool is_market_symbol_byte(std::uint8_t symbol) noexcept {
  return symbol >= symbol_min_byte && symbol <= market_symbol_max_byte;
}

[[nodiscard]] inline bool is_client_symbol_byte(std::uint8_t symbol) noexcept {
  return symbol >= client_symbol_base;
}

[[nodiscard]] inline std::uint8_t market_symbol_to_index(std::uint8_t symbol) {
  if (!is_market_symbol_byte(symbol)) {
    throw std::invalid_argument("market symbol byte must be in [" +
                                std::to_string(symbol_min_byte) +
                                ", " +
                                std::to_string(market_symbol_max_byte) +
                                "]");
  }
  return static_cast<std::uint8_t>(symbol - symbol_min_byte);
}

[[nodiscard]] inline std::uint8_t client_id_to_symbol(std::uint8_t client_id) {
  if (client_id >= Clients) {
    throw std::invalid_argument("client id outside configured client symbol range");
  }
  return static_cast<std::uint8_t>(client_symbol_base + client_id);
}

[[nodiscard]] inline std::uint8_t client_symbol_to_id(std::uint8_t symbol) {
  if (!is_client_symbol_byte(symbol)) {
    throw std::invalid_argument("symbol byte is not a client symbol");
  }
  return static_cast<std::uint8_t>(symbol - client_symbol_base);
}

} // namespace goblin_cannon
