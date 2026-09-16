#include "demapper.hpp"

#include <immintrin.h>

#include <cstdint>
#include <limits>

namespace goblin_cannon::detail {

std::size_t nearest_symbol_avx2(float sample_i,
                                float sample_q,
                                std::span<const float> constellation_i,
                                std::span<const float> constellation_q) noexcept {
  const auto n = constellation_i.size();
  const __m256 si = _mm256_set1_ps(sample_i);
  const __m256 sq = _mm256_set1_ps(sample_q);
  __m256 best_dist = _mm256_set1_ps(std::numeric_limits<float>::infinity());
  __m256i best_idx = _mm256_setzero_si256();
  const __m256i stride = _mm256_set1_epi32(8);
  __m256i idx = _mm256_setr_epi32(0, 1, 2, 3, 4, 5, 6, 7);

  std::size_t i = 0;
  for (; i + 8 <= n; i += 8) {
    const __m256 ci = _mm256_loadu_ps(constellation_i.data() + i);
    const __m256 cq = _mm256_loadu_ps(constellation_q.data() + i);
    const __m256 di = _mm256_sub_ps(si, ci);
    const __m256 dq = _mm256_sub_ps(sq, cq);
    const __m256 dist = _mm256_fmadd_ps(dq, dq, _mm256_mul_ps(di, di));
    const __m256 better = _mm256_cmp_ps(dist, best_dist, _CMP_LT_OQ);
    best_dist = _mm256_blendv_ps(best_dist, dist, better);
    best_idx = _mm256_castps_si256(
        _mm256_blendv_ps(_mm256_castsi256_ps(best_idx),
                         _mm256_castsi256_ps(idx),
                         better));
    idx = _mm256_add_epi32(idx, stride);
  }

  alignas(32) float dist_lanes[8];
  alignas(32) std::uint32_t idx_lanes[8];
  _mm256_store_ps(dist_lanes, best_dist);
  _mm256_store_si256(reinterpret_cast<__m256i*>(idx_lanes), best_idx);

  float best = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;
  for (std::size_t lane = 0; lane < 8; ++lane) {
    if (dist_lanes[lane] < best) {
      best = dist_lanes[lane];
      best_symbol = idx_lanes[lane];
    }
  }

  for (; i < n; ++i) {
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

NearestSymbolDecision nearest_symbol_decision_avx2(float sample_i,
                                                   float sample_q,
                                                   std::span<const float> constellation_i,
                                                   std::span<const float> constellation_q) noexcept {
  const auto n = constellation_i.size();
  const __m256 si = _mm256_set1_ps(sample_i);
  const __m256 sq = _mm256_set1_ps(sample_q);

  float best = std::numeric_limits<float>::infinity();
  float second = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;

  std::size_t i = 0;
  alignas(32) float dist_lanes[8];
  for (; i + 8 <= n; i += 8) {
    const __m256 ci = _mm256_loadu_ps(constellation_i.data() + i);
    const __m256 cq = _mm256_loadu_ps(constellation_q.data() + i);
    const __m256 di = _mm256_sub_ps(si, ci);
    const __m256 dq = _mm256_sub_ps(sq, cq);
    const __m256 dist = _mm256_fmadd_ps(dq, dq, _mm256_mul_ps(di, di));
    _mm256_store_ps(dist_lanes, dist);

    for (std::size_t lane = 0; lane < 8; ++lane) {
      const float d = dist_lanes[lane];
      const std::size_t symbol = i + lane;
      if (d < best) {
        second = best;
        best = d;
        best_symbol = symbol;
      } else if (d < second) {
        second = d;
      }
    }
  }

  for (; i < n; ++i) {
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

} // namespace goblin_cannon::detail
