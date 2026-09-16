#pragma once

#include <complex>
#include <cstddef>
#include <span>

namespace goblin_cannon::detail {

using Complex = std::complex<float>;

struct NearestSymbolDecision {
  std::size_t symbol = 0;
  float nearest_distance = 0.0F;
  float next_distance = 0.0F;
};

// Public dispatch entry points. Each picks the best implementation at the
// first call based on __builtin_cpu_supports.
std::size_t nearest_symbol(float sample_i,
                            float sample_q,
                            std::span<const float> constellation_i,
                            std::span<const float> constellation_q) noexcept;

NearestSymbolDecision nearest_symbol_decision(float sample_i,
                                              float sample_q,
                                              std::span<const float> constellation_i,
                                              std::span<const float> constellation_q) noexcept;

// Implementation labels for tests and diagnostics.
enum class DemapperIsa {
  scalar,
  avx2,
  avx512,
};

DemapperIsa active_demapper_isa() noexcept;

// Per-ISA kernels. Each compiled in its own translation unit with the
// matching -m flags; safe to link on hosts that don't support the ISA as
// long as the function is never actually called on those hosts.

std::size_t nearest_symbol_scalar(float sample_i,
                                  float sample_q,
                                  std::span<const float> constellation_i,
                                  std::span<const float> constellation_q) noexcept;

NearestSymbolDecision nearest_symbol_decision_scalar(float sample_i,
                                                     float sample_q,
                                                     std::span<const float> constellation_i,
                                                     std::span<const float> constellation_q) noexcept;

std::size_t nearest_symbol_avx2(float sample_i,
                                float sample_q,
                                std::span<const float> constellation_i,
                                std::span<const float> constellation_q) noexcept;

NearestSymbolDecision nearest_symbol_decision_avx2(float sample_i,
                                                   float sample_q,
                                                   std::span<const float> constellation_i,
                                                   std::span<const float> constellation_q) noexcept;

std::size_t nearest_symbol_avx512(float sample_i,
                                  float sample_q,
                                  std::span<const float> constellation_i,
                                  std::span<const float> constellation_q) noexcept;

NearestSymbolDecision nearest_symbol_decision_avx512(float sample_i,
                                                     float sample_q,
                                                     std::span<const float> constellation_i,
                                                     std::span<const float> constellation_q) noexcept;

float dot_product_avx512(std::span<const Complex> samples,
                         std::span<const float> taps,
                         std::size_t sample_offset) noexcept;

} // namespace goblin_cannon::detail
