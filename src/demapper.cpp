#include "demapper.hpp"

#include <atomic>
#include <limits>

namespace wbhf_modem::detail {

namespace {

DemapperIsa pick_isa() noexcept {
#if defined(__GNUC__) || defined(__clang__)
  if (__builtin_cpu_supports("avx512f") &&
      __builtin_cpu_supports("avx512dq") &&
      __builtin_cpu_supports("avx512bw") &&
      __builtin_cpu_supports("avx512vl")) {
    return DemapperIsa::avx512;
  }
  if (__builtin_cpu_supports("avx2") && __builtin_cpu_supports("fma")) {
    return DemapperIsa::avx2;
  }
#endif
  return DemapperIsa::scalar;
}

const DemapperIsa kSelectedIsa = pick_isa();

} // namespace

DemapperIsa active_demapper_isa() noexcept {
  return kSelectedIsa;
}

std::size_t nearest_symbol(float sample_i,
                            float sample_q,
                            std::span<const float> constellation_i,
                            std::span<const float> constellation_q) noexcept {
  switch (kSelectedIsa) {
    case DemapperIsa::avx512:
      return nearest_symbol_avx512(sample_i, sample_q, constellation_i, constellation_q);
    case DemapperIsa::avx2:
      return nearest_symbol_avx2(sample_i, sample_q, constellation_i, constellation_q);
    case DemapperIsa::scalar:
      break;
  }
  return nearest_symbol_scalar(sample_i, sample_q, constellation_i, constellation_q);
}

NearestSymbolDecision nearest_symbol_decision(float sample_i,
                                              float sample_q,
                                              std::span<const float> constellation_i,
                                              std::span<const float> constellation_q) noexcept {
  switch (kSelectedIsa) {
    case DemapperIsa::avx512:
      return nearest_symbol_decision_avx512(sample_i, sample_q, constellation_i, constellation_q);
    case DemapperIsa::avx2:
      return nearest_symbol_decision_avx2(sample_i, sample_q, constellation_i, constellation_q);
    case DemapperIsa::scalar:
      break;
  }
  return nearest_symbol_decision_scalar(sample_i, sample_q, constellation_i, constellation_q);
}

// Scalar fallback. Works on any host (AVX baseline or below). Auto-vectorized
// by the compiler at whatever ISA the TU is built with.
std::size_t nearest_symbol_scalar(float sample_i,
                                  float sample_q,
                                  std::span<const float> constellation_i,
                                  std::span<const float> constellation_q) noexcept {
  float best = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;
  const auto n = constellation_i.size();
  for (std::size_t i = 0; i < n; ++i) {
    const float di = sample_i - constellation_i[i];
    const float dq = sample_q - constellation_q[i];
    const float dist = di * di + dq * dq;
    if (dist < best) {
      best = dist;
      best_symbol = i;
    }
  }
  return best_symbol;
}

NearestSymbolDecision nearest_symbol_decision_scalar(float sample_i,
                                                     float sample_q,
                                                     std::span<const float> constellation_i,
                                                     std::span<const float> constellation_q) noexcept {
  float best = std::numeric_limits<float>::infinity();
  float second = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;
  const auto n = constellation_i.size();
  for (std::size_t i = 0; i < n; ++i) {
    const float di = sample_i - constellation_i[i];
    const float dq = sample_q - constellation_q[i];
    const float dist = di * di + dq * dq;
    if (dist < best) {
      second = best;
      best = dist;
      best_symbol = i;
    } else if (dist < second) {
      second = dist;
    }
  }
  return {.symbol = best_symbol, .nearest_distance = best, .next_distance = second};
}

} // namespace wbhf_modem::detail
