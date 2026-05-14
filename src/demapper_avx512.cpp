#include "demapper.hpp"

#include <immintrin.h>

#include <algorithm>
#include <cstdint>
#include <limits>

namespace wbhf_modem::detail {

std::size_t nearest_symbol_avx512(float sample_i,
                                  float sample_q,
                                  std::span<const float> constellation_i,
                                  std::span<const float> constellation_q) noexcept {
  const auto n = constellation_i.size();
  const __m512 si = _mm512_set1_ps(sample_i);
  const __m512 sq = _mm512_set1_ps(sample_q);
  __m512 best_dist = _mm512_set1_ps(std::numeric_limits<float>::infinity());
  __m512i best_idx = _mm512_setzero_si512();
  const __m512i stride = _mm512_set1_epi32(16);
  __m512i idx = _mm512_set_epi32(15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0);

  std::size_t i = 0;
  for (; i + 16 <= n; i += 16) {
    const __m512 ci = _mm512_loadu_ps(constellation_i.data() + i);
    const __m512 cq = _mm512_loadu_ps(constellation_q.data() + i);
    const __m512 di = _mm512_sub_ps(si, ci);
    const __m512 dq = _mm512_sub_ps(sq, cq);
    const __m512 dist = _mm512_fmadd_ps(dq, dq, _mm512_mul_ps(di, di));
    const __mmask16 better = _mm512_cmp_ps_mask(dist, best_dist, _CMP_LT_OQ);
    best_dist = _mm512_mask_blend_ps(better, best_dist, dist);
    best_idx = _mm512_mask_blend_epi32(better, best_idx, idx);
    idx = _mm512_add_epi32(idx, stride);
  }

  alignas(64) float dist_lanes[16];
  alignas(64) std::uint32_t idx_lanes[16];
  _mm512_store_ps(dist_lanes, best_dist);
  _mm512_store_si512(reinterpret_cast<__m512i*>(idx_lanes), best_idx);

  float best = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;
  for (std::size_t lane = 0; lane < 16; ++lane) {
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

NearestSymbolDecision nearest_symbol_decision_avx512(float sample_i,
                                                     float sample_q,
                                                     std::span<const float> constellation_i,
                                                     std::span<const float> constellation_q) noexcept {
  const auto n = constellation_i.size();
  const __m512 si = _mm512_set1_ps(sample_i);
  const __m512 sq = _mm512_set1_ps(sample_q);

  float best = std::numeric_limits<float>::infinity();
  float second = std::numeric_limits<float>::infinity();
  std::size_t best_symbol = 0;

  std::size_t i = 0;
  alignas(64) float dist_lanes[16];
  for (; i + 16 <= n; i += 16) {
    const __m512 ci = _mm512_loadu_ps(constellation_i.data() + i);
    const __m512 cq = _mm512_loadu_ps(constellation_q.data() + i);
    const __m512 di = _mm512_sub_ps(si, ci);
    const __m512 dq = _mm512_sub_ps(sq, cq);
    const __m512 dist = _mm512_fmadd_ps(dq, dq, _mm512_mul_ps(di, di));
    _mm512_store_ps(dist_lanes, dist);

    for (std::size_t lane = 0; lane < 16; ++lane) {
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

float dot_product_avx512(std::span<const Complex> samples,
                         std::span<const float> taps,
                         std::size_t sample_offset) noexcept {
  const auto n = taps.size();
  __m512 acc_i = _mm512_setzero_ps();
  __m512 acc_q = _mm512_setzero_ps();

  std::size_t i = 0;
  for (; i + 16 <= n; i += 16) {
    alignas(64) float tmp_i[16];
    alignas(64) float tmp_q[16];
    for (std::size_t lane = 0; lane < 16; ++lane) {
      const auto v = samples[sample_offset + i + lane];
      tmp_i[lane] = v.real();
      tmp_q[lane] = v.imag();
    }
    const __m512 vi = _mm512_load_ps(tmp_i);
    const __m512 vq = _mm512_load_ps(tmp_q);
    const __m512 h = _mm512_loadu_ps(taps.data() + i);
    acc_i = _mm512_fmadd_ps(vi, h, acc_i);
    acc_q = _mm512_fmadd_ps(vq, h, acc_q);
  }

  float out_i = _mm512_reduce_add_ps(acc_i);
  float out_q = _mm512_reduce_add_ps(acc_q);
  for (; i < n; ++i) {
    const auto v = samples[sample_offset + i];
    const float h = taps[i];
    out_i += v.real() * h;
    out_q += v.imag() * h;
  }

  return out_i + out_q;
}

} // namespace wbhf_modem::detail
