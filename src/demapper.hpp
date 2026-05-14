#pragma once

#include <complex>
#include <cstddef>
#include <span>

namespace wbhf_modem::detail {

using Complex = std::complex<float>;

struct NearestSymbolDecision {
  std::size_t symbol = 0;
  float nearest_distance = 0.0F;
  float next_distance = 0.0F;
};

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

} // namespace wbhf_modem::detail
