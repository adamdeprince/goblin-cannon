#include "wbhf_modem/modem.hpp"

#include "demapper.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <numbers>
#include <stdexcept>

namespace wbhf_modem {

namespace {

constexpr float inv_sqrt_2 = 0.7071067811865475F;

std::vector<Complex> make_wbhf_points(Modulation modulation) {
  switch (modulation) {
  case Modulation::qpsk:
    return {
      {1.0F, 0.0F},
      {0.0F, 1.0F},
      {-1.0F, 0.0F},
      {0.0F, -1.0F},
    };
  case Modulation::psk8:
    return {
      {1.0F, 0.0F},
      {inv_sqrt_2, inv_sqrt_2},
      {0.0F, 1.0F},
      {-inv_sqrt_2, inv_sqrt_2},
      {-1.0F, 0.0F},
      {-inv_sqrt_2, -inv_sqrt_2},
      {0.0F, -1.0F},
      {inv_sqrt_2, -inv_sqrt_2},
    };
  case Modulation::qam16:
    return {
      {0.866025F, 0.500000F},  {0.500000F, 0.866025F},
      {1.000000F, 0.000000F},  {0.258819F, 0.258819F},
      {-0.500000F, 0.866025F}, {0.000000F, 1.000000F},
      {-0.866025F, 0.500000F}, {-0.258819F, 0.258819F},
      {0.500000F, -0.866025F}, {0.000000F, -1.000000F},
      {0.866025F, -0.500000F}, {0.258819F, -0.258819F},
      {-0.866025F, -0.500000F}, {-0.500000F, -0.866025F},
      {-1.000000F, 0.000000F}, {-0.258819F, -0.258819F},
    };
  case Modulation::qam64:
    return {
      {1.000000F, 0.000000F}, {0.822878F, 0.568218F}, {0.821137F, 0.152996F}, {0.932897F, 0.360142F},
      {0.000000F, -1.000000F}, {0.822878F, -0.568218F}, {0.821137F, -0.152996F}, {0.932897F, -0.360142F},
      {0.568218F, 0.822878F}, {0.588429F, 0.588429F}, {0.588429F, 0.117686F}, {0.588429F, 0.353057F},
      {0.568218F, -0.822878F}, {0.588429F, -0.588429F}, {0.588429F, -0.117686F}, {0.588429F, -0.353057F},
      {0.152996F, 0.821137F}, {0.117686F, 0.588429F}, {0.117686F, 0.117686F}, {0.117686F, 0.353057F},
      {0.152996F, -0.821137F}, {0.117686F, -0.588429F}, {0.117686F, -0.117686F}, {0.117686F, -0.353057F},
      {0.360142F, 0.932897F}, {0.353057F, 0.588429F}, {0.353057F, 0.117686F}, {0.353057F, 0.353057F},
      {0.360142F, -0.932897F}, {0.353057F, -0.588429F}, {0.353057F, -0.117686F}, {0.353057F, -0.353057F},
      {0.000000F, 1.000000F}, {-0.822878F, 0.568218F}, {-0.821137F, 0.152996F}, {-0.932897F, 0.360142F},
      {-1.000000F, 0.000000F}, {-0.822878F, -0.568218F}, {-0.821137F, -0.152996F}, {-0.932897F, -0.360142F},
      {-0.568218F, 0.822878F}, {-0.588429F, 0.588429F}, {-0.588429F, 0.117686F}, {-0.588429F, 0.353057F},
      {-0.568218F, -0.822878F}, {-0.588429F, -0.588429F}, {-0.588429F, -0.117686F}, {-0.588429F, -0.353057F},
      {-0.152996F, 0.821137F}, {-0.117686F, 0.588429F}, {-0.117686F, 0.117686F}, {-0.117686F, 0.353057F},
      {-0.152996F, -0.821137F}, {-0.117686F, -0.588429F}, {-0.117686F, -0.117686F}, {-0.117686F, -0.353057F},
      {-0.360142F, 0.932897F}, {-0.353057F, 0.588429F}, {-0.353057F, 0.117686F}, {-0.353057F, 0.353057F},
      {-0.360142F, -0.932897F}, {-0.353057F, -0.588429F}, {-0.353057F, -0.117686F}, {-0.353057F, -0.353057F},
    };
  case Modulation::qam256:
    break;
  case Modulation::qam1024:
    throw std::invalid_argument("WBHF profile does not define 1024QAM points; use square_gray");
  }

  const std::array<float, 16> x0 = {
    0.959366F, 0.959366F, 0.846499F, 0.959366F,
    0.846499F, 0.846499F, 0.846499F, 0.846499F,
    0.959366F, 0.959366F, 0.846499F, 0.959366F,
    0.846499F, 0.846499F, 0.846499F, 0.846499F,
  };
  const std::array<float, 16> y0 = {
    0.056433F, 0.169300F, 0.507899F, 0.282166F,
    0.056433F, 0.169300F, 0.395033F, 0.282166F,
    -0.056433F, -0.169300F, -0.507899F, -0.282166F,
    -0.056433F, -0.169300F, -0.395033F, -0.282166F,
  };
  const std::array<float, 16> x1 = {
    0.169300F, 0.056433F, 0.733632F, 0.733632F,
    0.733632F, 0.733632F, 0.733632F, 0.733632F,
    0.169300F, 0.056433F, 0.733632F, 0.733632F,
    0.733632F, 0.733632F, 0.733632F, 0.733632F,
  };
  const std::array<float, 16> y1 = {
    0.959366F, 0.998304F, 0.507899F, 0.620766F,
    0.056433F, 0.169300F, 0.395033F, 0.282166F,
    -0.959366F, -0.998304F, -0.507899F, -0.620766F,
    -0.056433F, -0.169300F, -0.395033F, -0.282166F,
  };
  const std::array<float, 16> y_inner = {
    0.846499F, 0.733632F, 0.507899F, 0.620766F,
    0.056433F, 0.169300F, 0.395033F, 0.282166F,
    -0.846499F, -0.733632F, -0.507899F, -0.620766F,
    -0.056433F, -0.169300F, -0.395033F, -0.282166F,
  };
  const std::array<float, 16> y_edge = {
    0.959366F, 0.733632F, 0.507899F, 0.620766F,
    0.056433F, 0.169300F, 0.395033F, 0.282166F,
    -0.959366F, -0.733632F, -0.507899F, -0.620766F,
    -0.056433F, -0.169300F, -0.395033F, -0.282166F,
  };

  std::vector<Complex> points;
  points.reserve(256);
  auto append_block = [&points](const std::array<float, 16>& xs, const std::array<float, 16>& ys) {
    for (std::size_t i = 0; i < 16; ++i) {
      points.emplace_back(xs[i], ys[i]);
    }
  };
  auto append_negated_x_block = [&points](const std::array<float, 16>& xs, const std::array<float, 16>& ys) {
    for (std::size_t i = 0; i < 16; ++i) {
      points.emplace_back(-xs[i], ys[i]);
    }
  };
  auto append_constant_x_block = [&points, &y_inner](float x) {
    for (const float y : y_inner) {
      points.emplace_back(x, y);
    }
  };
  auto append_edge_x_block = [&points, &y_edge](float edge_x, float body_x) {
    for (std::size_t i = 0; i < y_edge.size(); ++i) {
      points.emplace_back((i == 0 || i == 8) ? edge_x : body_x, y_edge[i]);
    }
  };

  append_block(x0, y0);
  append_block(x1, y1);
  append_constant_x_block(0.507899F);
  append_edge_x_block(0.282166F, 0.620766F);
  append_constant_x_block(0.056433F);
  append_constant_x_block(0.169300F);
  append_constant_x_block(0.395033F);
  append_constant_x_block(0.282166F);

  append_negated_x_block(x0, y0);
  append_negated_x_block(x1, y1);
  append_constant_x_block(-0.507899F);
  append_edge_x_block(-0.282166F, -0.620766F);
  append_constant_x_block(-0.056433F);
  append_constant_x_block(-0.169300F);
  append_constant_x_block(-0.395033F);
  append_constant_x_block(-0.282166F);
  return points;
}

std::uint32_t gray_to_binary(std::uint32_t gray) {
  for (auto shift = gray >> 1U; shift != 0U; shift >>= 1U) {
    gray ^= shift;
  }
  return gray;
}

std::vector<Complex> make_square_gray_points(Modulation modulation) {
  if (modulation == Modulation::qpsk || modulation == Modulation::psk8) {
    return make_wbhf_points(modulation);
  }

  const std::size_t bits = bits_per_symbol(modulation);
  const std::size_t side_bits = bits / 2U;
  const std::size_t side = 1U << side_bits;
  std::vector<Complex> points(1U << bits);
  const float scale = std::sqrt((2.0F / 3.0F) * (static_cast<float>(side * side) - 1.0F));
  for (std::uint32_t sym = 0; sym < points.size(); ++sym) {
    const std::uint32_t i_gray = sym >> side_bits;
    const std::uint32_t q_gray = sym & ((1U << side_bits) - 1U);
    const auto i = static_cast<float>(2U * gray_to_binary(i_gray) + 1U) - static_cast<float>(side);
    const auto q = static_cast<float>(2U * gray_to_binary(q_gray) + 1U) - static_cast<float>(side);
    points[sym] = {i / scale, q / scale};
  }
  return points;
}

} // namespace

std::string to_string(Modulation modulation) {
  switch (modulation) {
  case Modulation::qpsk:
    return "QPSK";
  case Modulation::psk8:
    return "8PSK";
  case Modulation::qam16:
    return "16QAM";
  case Modulation::qam64:
    return "64QAM";
  case Modulation::qam256:
    return "256QAM";
  case Modulation::qam1024:
    return "1024QAM";
  }
  return "unknown";
}

std::size_t bits_per_symbol(Modulation modulation) {
  switch (modulation) {
  case Modulation::qpsk:
    return 2;
  case Modulation::psk8:
    return 3;
  case Modulation::qam16:
    return 4;
  case Modulation::qam64:
    return 6;
  case Modulation::qam256:
    return 8;
  case Modulation::qam1024:
    return 10;
  }
  throw std::invalid_argument("unknown modulation");
}

Constellation::Constellation(Modulation modulation, ConstellationProfile profile)
    : modulation_(modulation),
      bits_per_symbol_(wbhf_modem::bits_per_symbol(modulation)),
      points_((profile == ConstellationProfile::square_gray || modulation == Modulation::qam1024)
                  ? make_square_gray_points(modulation)
                  : make_wbhf_points(modulation)) {
  if (points_.size() != (1ULL << bits_per_symbol_)) {
    throw std::logic_error("constellation point count does not match modulation order");
  }
  i_.reserve(points_.size());
  q_.reserve(points_.size());
  for (const auto point : points_) {
    i_.push_back(point.real());
    q_.push_back(point.imag());
  }
}

Complex Constellation::map_bits(std::span<const std::uint8_t> bits) const {
  return map_symbol(bits_to_symbol(bits));
}

Complex Constellation::map_symbol(std::uint32_t symbol) const {
  if (symbol >= points_.size()) {
    throw std::out_of_range("symbol outside constellation");
  }
  if (modulation_ == Modulation::qpsk) {
    static constexpr std::array<std::uint8_t, 4> map = {0, 2, 3, 1};
    return points_[map[symbol]];
  }
  if (modulation_ == Modulation::psk8) {
    static constexpr std::array<std::uint8_t, 8> map = {1, 0, 2, 3, 6, 7, 5, 4};
    return points_[map[symbol]];
  }
  return points_[symbol];
}

std::uint32_t Constellation::bits_to_symbol(std::span<const std::uint8_t> bits) const {
  if (bits.size() < bits_per_symbol_) {
    throw std::invalid_argument("not enough bits for modulation symbol");
  }
  std::uint32_t symbol = 0;
  for (std::size_t i = 0; i < bits_per_symbol_; ++i) {
    symbol = (symbol << 1U) | (bits[i] & 1U);
  }
  return symbol;
}

std::uint32_t Constellation::nearest_symbol(Complex sample) const {
  const auto point = detail::nearest_symbol_avx512(sample.real(), sample.imag(), i_, q_);
  if (modulation_ == Modulation::qpsk) {
    static constexpr std::array<std::uint8_t, 8> reverse = {0, 3, 1, 2, 2, 2, 2, 2};
    return reverse[point];
  }
  if (modulation_ == Modulation::psk8) {
    static constexpr std::array<std::uint8_t, 8> reverse = {1, 0, 2, 3, 7, 6, 4, 5};
    return reverse[point];
  }
  return static_cast<std::uint32_t>(point);
}

SymbolDecision Constellation::decide(Complex sample) const {
  const auto decision = detail::nearest_symbol_decision_avx512(sample.real(), sample.imag(), i_, q_);
  auto symbol = static_cast<std::uint32_t>(decision.symbol);
  if (modulation_ == Modulation::qpsk) {
    static constexpr std::array<std::uint8_t, 8> reverse = {0, 3, 1, 2, 2, 2, 2, 2};
    symbol = reverse[decision.symbol];
  } else if (modulation_ == Modulation::psk8) {
    static constexpr std::array<std::uint8_t, 8> reverse = {1, 0, 2, 3, 7, 6, 4, 5};
    symbol = reverse[decision.symbol];
  }

  float confidence = 1.0F;
  if (std::isfinite(decision.next_distance)) {
    const float denominator = std::max(decision.next_distance, 1.0e-8F);
    confidence = std::clamp((decision.next_distance - decision.nearest_distance) / denominator, 0.0F, 1.0F);
  }

  return {.symbol = symbol,
          .nearest_distance = decision.nearest_distance,
          .next_distance = decision.next_distance,
          .confidence = confidence};
}

void Constellation::symbol_to_bits(std::uint32_t symbol, std::span<std::uint8_t> out) const {
  if (out.size() < bits_per_symbol_) {
    throw std::invalid_argument("output span too small for symbol bits");
  }
  for (std::size_t i = 0; i < bits_per_symbol_; ++i) {
    const auto shift = bits_per_symbol_ - i - 1U;
    out[i] = static_cast<std::uint8_t>((symbol >> shift) & 1U);
  }
}

} // namespace wbhf_modem
