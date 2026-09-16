#include "goblin_cannon/modem.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <numbers>
#include <stdexcept>

namespace goblin_cannon {

namespace {

constexpr double min_sps = 2.0;

double rrc_impulse(double t, double beta) {
  constexpr double eps = 1.0e-8;
  const double pi = std::numbers::pi;

  if (std::abs(t) < eps) {
    return 1.0 + beta * (4.0 / pi - 1.0);
  }

  if (beta > eps) {
    const double singular = 1.0 / (4.0 * beta);
    if (std::abs(std::abs(t) - singular) < 1.0e-6) {
      const double a = (1.0 + 2.0 / pi) * std::sin(pi / (4.0 * beta));
      const double b = (1.0 - 2.0 / pi) * std::cos(pi / (4.0 * beta));
      return (beta / std::sqrt(2.0)) * (a + b);
    }
  }

  const double numerator = std::sin(pi * t * (1.0 - beta)) +
                           4.0 * beta * t * std::cos(pi * t * (1.0 + beta));
  const double denominator = pi * t * (1.0 - (4.0 * beta * t) * (4.0 * beta * t));
  return numerator / denominator;
}

float constellation_average_power(const Constellation& constellation) {
  double sum = 0.0;
  for (const auto point : constellation.points()) {
    sum += std::norm(point);
  }
  return static_cast<float>(sum / static_cast<double>(constellation.size()));
}

} // namespace

double derived_symbol_rate_hz(const ModemConfig& config) {
  if (config.symbol_rate_hz.has_value()) {
    return *config.symbol_rate_hz;
  }
  return config.bandwidth_hz * 0.8;
}

ModemInfo describe(const ModemConfig& config) {
  validate(config);
  ModemInfo info;
  info.sample_rate_hz = config.sample_rate_hz;
  info.bandwidth_hz = config.bandwidth_hz;
  info.symbol_rate_hz = derived_symbol_rate_hz(config);
  info.samples_per_symbol = info.sample_rate_hz / info.symbol_rate_hz;
  info.bits_per_symbol = bits_per_symbol(config.modulation);
  info.filter_span_symbols = config.filter_span_symbols;
  info.nominal_filter_latency_symbols = static_cast<double>(config.filter_span_symbols) / 2.0;
  info.receiver_oversampling = config.receiver_oversampling;
  return info;
}

void validate(const ModemConfig& config) {
  if (!std::isfinite(config.sample_rate_hz) || config.sample_rate_hz <= 0.0) {
    throw std::invalid_argument("sample_rate_hz must be positive");
  }
  if (!std::isfinite(config.bandwidth_hz) || config.bandwidth_hz <= 0.0) {
    throw std::invalid_argument("bandwidth_hz must be positive");
  }
  if (config.bandwidth_hz > config.sample_rate_hz) {
    throw std::invalid_argument("bandwidth_hz cannot exceed sample_rate_hz for complex baseband");
  }
  const double symbol_rate = derived_symbol_rate_hz(config);
  if (!std::isfinite(symbol_rate) || symbol_rate <= 0.0) {
    throw std::invalid_argument("symbol_rate_hz must be positive");
  }
  if (config.sample_rate_hz / symbol_rate < min_sps) {
    throw std::invalid_argument("sample_rate_hz / symbol_rate_hz must be at least 2");
  }
  if (!std::isfinite(config.rrc_rolloff) || config.rrc_rolloff < 0.0 || config.rrc_rolloff > 1.0) {
    throw std::invalid_argument("rrc_rolloff must be in [0, 1]");
  }
  if (config.filter_span_symbols < 2 || (config.filter_span_symbols % 2U) != 0U) {
    throw std::invalid_argument("filter_span_symbols must be an even value >= 2");
  }
  if (!std::isfinite(config.tx_gain) || config.tx_gain <= 0.0F) {
    throw std::invalid_argument("tx_gain must be positive");
  }
  if (config.receiver_oversampling != 1 && config.receiver_oversampling != 2 &&
      config.receiver_oversampling != 4 && config.receiver_oversampling != 8) {
    throw std::invalid_argument("receiver_oversampling must be one of 1, 2, 4, or 8");
  }
  if (!std::isfinite(config.symbol_confidence_threshold) ||
      config.symbol_confidence_threshold < 0.0F ||
      config.symbol_confidence_threshold > 1.0F) {
    throw std::invalid_argument("symbol_confidence_threshold must be in [0, 1]");
  }
}

namespace {

bool sps_is_integer(double sps) noexcept {
  if (!std::isfinite(sps) || sps < 1.5) {
    return false;
  }
  const auto rounded = std::round(sps);
  return std::abs(sps - rounded) < 1.0e-9;
}

} // namespace

Encoder::Encoder(ModemConfig config)
    : config_(std::move(config)),
      info_(describe(config_)),
      constellation_(config_.modulation, config_.constellation_profile) {
  if (sps_is_integer(info_.samples_per_symbol)) {
    synth_sps_int_ = static_cast<int>(std::lround(info_.samples_per_symbol));
    const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
    synth_taps_.assign(synth_sps_int_, {});
    synth_phase_d_min_.assign(synth_sps_int_, 0);
    synth_phase_d_max_.assign(synth_sps_int_, 0);
    for (int phase = 0; phase < synth_sps_int_; ++phase) {
      // For sample at index (sps*q + phase), t = q + phase/sps.
      // k iterates over integers in [t - half_span, t + half_span] = [q + phase/sps - h, q + phase/sps + h].
      // d = k - q is in [ceil(phase/sps - h), floor(phase/sps + h)].
      const double frac = static_cast<double>(phase) / static_cast<double>(synth_sps_int_);
      const int d_min = static_cast<int>(std::ceil(frac - half_span));
      const int d_max = static_cast<int>(std::floor(frac + half_span));
      synth_phase_d_min_[phase] = d_min;
      synth_phase_d_max_[phase] = d_max;
      const int n = d_max - d_min + 1;
      synth_taps_[phase].resize(static_cast<std::size_t>(n));
      for (int i = 0; i < n; ++i) {
        const int d = d_min + i;
        const double arg = frac - static_cast<double>(d);
        synth_taps_[phase][static_cast<std::size_t>(i)] =
            static_cast<float>(rrc_impulse(arg, config_.rrc_rolloff));
      }
    }
  }
}

StreamResult Encoder::push_bits(std::span<const std::uint8_t> bits, std::span<Complex> out) {
  for (const auto bit : bits) {
    append_bit(bit);
  }
  const auto produced = produce(out);
  return {.consumed = bits.size(), .produced = produced};
}

StreamResult Encoder::push_bytes(std::span<const std::uint8_t> bytes, std::span<Complex> out) {
  for (const auto byte : bytes) {
    for (int bit = 7; bit >= 0; --bit) {
      append_bit(static_cast<std::uint8_t>((byte >> bit) & 1U));
    }
  }
  const auto produced = produce(out);
  return {.consumed = bytes.size(), .produced = produced};
}

StreamResult Encoder::drain(std::span<Complex> out) {
  begin_flush();
  const auto produced = produce(out);
  return {.consumed = 0, .produced = produced};
}

void Encoder::reset() {
  bit_buffer_.clear();
  symbols_.clear();
  symbols_head_ = 0;
  first_symbol_index_ = 0;
  next_symbol_index_ = 0;
  next_sample_index_ = 0;
  flushing_ = false;
  flush_last_symbol_index_ = -1;
}

void Encoder::append_bit(std::uint8_t bit) {
  if (flushing_) {
    throw std::logic_error("cannot append bits after encoder drain has started");
  }
  bit_buffer_.push_back(bit & 1U);
  if (bit_buffer_.size() == info_.bits_per_symbol) {
    append_symbol(constellation_.map_bits(bit_buffer_));
    bit_buffer_.clear();
  }
}

void Encoder::append_symbol(Complex symbol) {
  symbols_.push_back(symbol);
  ++next_symbol_index_;
}

void Encoder::begin_flush() {
  if (flushing_) {
    return;
  }
  while (!bit_buffer_.empty() && bit_buffer_.size() < info_.bits_per_symbol) {
    bit_buffer_.push_back(0);
  }
  if (!bit_buffer_.empty()) {
    append_symbol(constellation_.map_bits(bit_buffer_));
    bit_buffer_.clear();
  }
  flushing_ = true;
  flush_last_symbol_index_ = next_symbol_index_ - 1;
}

std::size_t Encoder::produce(std::span<Complex> out) {
  std::size_t produced = 0;
  while (produced < out.size() && can_produce_next_sample()) {
    out[produced] = synthesize_sample(next_sample_index_) * config_.tx_gain;
    ++produced;
    ++next_sample_index_;
    prune_symbols(static_cast<double>(next_sample_index_) / info_.samples_per_symbol);
  }
  return produced;
}

bool Encoder::can_produce_next_sample() const {
  if (symbols_.empty()) {
    return false;
  }
  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const double t = static_cast<double>(next_sample_index_) / info_.samples_per_symbol;
  if (flushing_) {
    return t <= static_cast<double>(flush_last_symbol_index_) + half_span;
  }
  const auto needed = static_cast<std::int64_t>(std::floor(t + half_span));
  return needed < next_symbol_index_;
}

Complex Encoder::synthesize_sample(std::uint64_t sample_index) const {
  if (!synth_taps_.empty()) {
    // Fast path: integer SPS -> precomputed polyphase taps. No sin/cos/sqrt.
    const auto sps = static_cast<std::uint64_t>(synth_sps_int_);
    const auto phase = static_cast<std::size_t>(sample_index % sps);
    const auto q = static_cast<std::int64_t>(sample_index / sps);
    const auto& tap_row = synth_taps_[phase];
    const int d_min = synth_phase_d_min_[phase];
    const int d_max = synth_phase_d_max_[phase];
    const auto k_min = std::max<std::int64_t>(first_symbol_index_, q + d_min);
    const auto k_max = std::min<std::int64_t>(next_symbol_index_ - 1, q + d_max);
    Complex y{0.0F, 0.0F};
    for (auto k = k_min; k <= k_max; ++k) {
      const auto symbol = symbols_[symbols_head_ + static_cast<std::size_t>(k - first_symbol_index_)];
      const auto tap_idx = static_cast<std::size_t>((k - q) - d_min);
      y += symbol * tap_row[tap_idx];
    }
    return y;
  }

  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const double t = static_cast<double>(sample_index) / info_.samples_per_symbol;
  const auto k_min = static_cast<std::int64_t>(std::ceil(t - half_span));
  const auto k_max = static_cast<std::int64_t>(std::floor(t + half_span));
  Complex y{0.0F, 0.0F};

  for (auto k = k_min; k <= k_max; ++k) {
    if (k < first_symbol_index_ || k >= next_symbol_index_) {
      continue;
    }
    const auto symbol = symbols_[symbols_head_ + static_cast<std::size_t>(k - first_symbol_index_)];
    const auto h = static_cast<float>(rrc_impulse(t - static_cast<double>(k), config_.rrc_rolloff));
    y += symbol * h;
  }

  return y;
}

void Encoder::prune_symbols(double symbol_time) {
  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const auto keep_from = static_cast<std::int64_t>(std::floor(symbol_time - half_span)) - 1;
  if (keep_from <= first_symbol_index_) {
    return;
  }
  const auto live_size = symbols_.size() - symbols_head_;
  const auto remove_count = std::min<std::size_t>(
      static_cast<std::size_t>(keep_from - first_symbol_index_), live_size);
  symbols_head_ += remove_count;
  first_symbol_index_ += static_cast<std::int64_t>(remove_count);
  // Amortized compaction.
  if (symbols_head_ > 0U && symbols_head_ * 2U >= symbols_.size()) {
    symbols_.erase(symbols_.begin(),
                   symbols_.begin() + static_cast<std::ptrdiff_t>(symbols_head_));
    symbols_head_ = 0U;
  }
}

Decoder::Decoder(ModemConfig config, double timing_offset_symbols)
    : config_(std::move(config)),
      info_(describe(config_)),
      constellation_(config_.modulation, config_.constellation_profile),
      timing_offset_symbols_(timing_offset_symbols),
      target_symbol_power_(constellation_average_power(constellation_)) {
  if (!std::isfinite(timing_offset_symbols_) || timing_offset_symbols_ < 0.0 || timing_offset_symbols_ >= 1.0) {
    throw std::invalid_argument("timing_offset_symbols must be in [0, 1)");
  }
  if (sps_is_integer(info_.samples_per_symbol)) {
    sps_int_ = static_cast<int>(std::lround(info_.samples_per_symbol));
    sps_inv_ = 1.0F / static_cast<float>(sps_int_);
    const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
    // For symbol at integer index symbol_index, symbol_time = symbol_index + timing_offset.
    // Sample index sample_index has sample_time = sample_index / sps.
    // start_sample = ceil((symbol_time - half_span)*sps)
    //              = ceil(sps*symbol_index + sps*timing_offset - sps*half_span)
    //              = sps*symbol_index + ceil(sps*timing_offset - sps*half_span)
    // s = sample_index - sps*symbol_index; s_min = ceil(sps*(timing_offset - half_span)),
    // s_max = floor(sps*(timing_offset + half_span)).
    const double sps_times_offset = static_cast<double>(sps_int_) * timing_offset_symbols_;
    const double sps_times_half = static_cast<double>(sps_int_) * half_span;
    taps_s_min_ = static_cast<int>(std::ceil(sps_times_offset - sps_times_half));
    taps_s_max_ = static_cast<int>(std::floor(sps_times_offset + sps_times_half));
    const int n_taps = taps_s_max_ - taps_s_min_ + 1;
    taps_.assign(static_cast<std::size_t>(n_taps), 0.0F);
    for (int i = 0; i < n_taps; ++i) {
      const int s = taps_s_min_ + i;
      const double arg = static_cast<double>(s) / static_cast<double>(sps_int_) - timing_offset_symbols_;
      taps_[static_cast<std::size_t>(i)] = static_cast<float>(rrc_impulse(arg, config_.rrc_rolloff));
    }
  }
  reset();
}

DecodeResult Decoder::push_samples(std::span<const Complex> samples, std::span<std::uint8_t> out_bits) {
  for (const auto sample : samples) {
    append_sample(sample);
  }

  DecodeResult result{.consumed_samples = samples.size(), .produced_bits = 0};
  std::array<std::uint8_t, max_bits_per_symbol> bits{};
  while (result.produced_bits + info_.bits_per_symbol <= out_bits.size() && can_decode_next_symbol()) {
    Complex sample = matched_filter_symbol(next_symbol_index_);
    advance_symbol(sample);
    sample = apply_agc(sample, 0);
    const auto symbol = constellation_.nearest_symbol(sample);
    constellation_.symbol_to_bits(symbol, std::span<std::uint8_t>(bits).first(info_.bits_per_symbol));
    std::copy_n(bits.begin(),
                static_cast<std::ptrdiff_t>(info_.bits_per_symbol),
                out_bits.begin() + static_cast<std::ptrdiff_t>(result.produced_bits));
    result.produced_bits += info_.bits_per_symbol;
    prune_samples(next_symbol_index_);
  }
  return result;
}

DecodeResult Decoder::push_samples_soft(std::span<const Complex> samples, std::span<SoftBit> out_bits) {
  for (const auto sample : samples) {
    append_sample(sample);
  }

  DecodeResult result{.consumed_samples = samples.size(), .produced_bits = 0};
  std::array<std::uint8_t, max_bits_per_symbol> bits{};
  while (result.produced_bits + info_.bits_per_symbol <= out_bits.size() && can_decode_next_symbol()) {
    Complex sample = matched_filter_symbol(next_symbol_index_);
    advance_symbol(sample);
    sample = apply_agc(sample, 0);
    const auto decision = constellation_.decide(sample);
    constellation_.symbol_to_bits(decision.symbol, std::span<std::uint8_t>(bits).first(info_.bits_per_symbol));
    const bool certain = decision.confidence >= config_.symbol_confidence_threshold;
    for (std::size_t i = 0; i < info_.bits_per_symbol; ++i) {
      out_bits[result.produced_bits + i] = {.value = bits[i], .certain = certain, .confidence = decision.confidence};
    }
    result.produced_bits += info_.bits_per_symbol;
    prune_samples(next_symbol_index_);
  }
  return result;
}

DecodeSymbolsResult Decoder::push_samples_symbols(std::span<const Complex> samples,
                                                  std::span<SymbolDecision> out_symbols) {
  for (const auto sample : samples) {
    append_sample(sample);
  }

  DecodeSymbolsResult result{.consumed_samples = samples.size(), .produced_symbols = 0};
  while (result.produced_symbols < out_symbols.size() && can_decode_next_symbol()) {
    Complex sample = matched_filter_symbol(next_symbol_index_);
    advance_symbol(sample);
    sample = apply_agc(sample, 0);
    out_symbols[result.produced_symbols] = constellation_.decide(sample);
    ++result.produced_symbols;
    prune_samples(next_symbol_index_);
  }
  return result;
}

DecodeSymbolsResult Decoder::push_samples_matched(std::span<const Complex> samples,
                                                  std::span<Complex> out_symbols) {
  for (const auto sample : samples) {
    append_sample(sample);
  }
  DecodeSymbolsResult result{.consumed_samples = samples.size()};
  while (result.produced_symbols < out_symbols.size() && can_decode_next_symbol()) {
    const auto sample = matched_filter_symbol(next_symbol_index_);
    out_symbols[result.produced_symbols++] = sample;
    advance_symbol(sample);
    prune_samples(next_symbol_index_);
  }
  return result;
}

void Decoder::set_sample_clock_recovery(bool enabled) {
  if (next_sample_index_ != 0) {
    throw std::logic_error("configure sample clock recovery before feeding audio");
  }
  sample_clock_recovery_ = enabled;
  if (enabled && fractional_rrc_.empty()) {
    // Interpolate the pulse, not the received symbols. The table avoids
    // trigonometric work in both the symbol and midpoint matched filters.
    fractional_rrc_.resize(config_.filter_span_symbols * 1024U + 1U);
    const double half = config_.filter_span_symbols / 2.0;
    for (std::size_t i = 0; i < fractional_rrc_.size(); ++i) {
      fractional_rrc_[i] = static_cast<float>(rrc_impulse(i / 1024.0 - half, config_.rrc_rolloff));
    }
  }
}

Complex Decoder::matched_filter_at(double symbol_time) const {
  const double half = config_.filter_span_symbols / 2.0;
  const double sps = info_.samples_per_symbol;
  const auto start = std::max(first_sample_index_, static_cast<std::int64_t>(std::ceil((symbol_time - half) * sps)));
  const auto stop = std::min(static_cast<std::int64_t>(next_sample_index_) - 1,
                           static_cast<std::int64_t>(std::floor((symbol_time + half) * sps)));
  Complex value{};
  for (auto i = start; i <= stop; ++i) {
    const double position = std::clamp((i / sps - symbol_time + half) * 1024.0,
                                      0.0, static_cast<double>(fractional_rrc_.size() - 1));
    const auto index = std::min(static_cast<std::size_t>(position), fractional_rrc_.size() - 2);
    const auto fraction = static_cast<float>(position - index);
    const auto tap = fractional_rrc_[index] + fraction * (fractional_rrc_[index + 1] - fractional_rrc_[index]);
    value += samples_[samples_head_ + static_cast<std::size_t>(i - first_sample_index_)] * tap;
  }
  return value / static_cast<float>(sps);
}

void Decoder::advance_symbol(Complex matched) {
  if (sample_clock_recovery_) {
    timing_power_ += 0.01F * (std::norm(matched) - timing_power_);
    double error = 0.0;
    if (next_symbol_index_ >= 16 && timing_power_ > 1.0e-8F) {
      const auto midpoint = matched_filter_at((previous_symbol_time_ + next_symbol_time_) * 0.5);
      // Gardner timing error: invariant under a common phase rotation. A PI
      // loop adjusts sampling instants only; the rate bound is +/-1000 ppm.
      error = std::clamp(static_cast<double>(std::real((previous_matched_ - matched) * std::conj(midpoint))) /
                             timing_power_, -2.0, 2.0);
      clock_rate_ = std::clamp(clock_rate_ + 5.0e-7 * error, -0.001, 0.001);
    }
    previous_matched_ = matched;
    previous_symbol_time_ = next_symbol_time_;
    next_symbol_time_ += 1.0 + clock_rate_ + 0.001 * error;
  }
  ++next_symbol_index_;
}

void Decoder::reset() {
  samples_.clear();
  samples_head_ = 0;
  first_sample_index_ = 0;
  next_sample_index_ = 0;
  next_symbol_index_ = 0;
  next_symbol_time_ = timing_offset_symbols_;
  previous_symbol_time_ = timing_offset_symbols_;
  clock_rate_ = 0.0;
  timing_power_ = 1.0F;
  previous_matched_ = {};
  agc_power_ = target_symbol_power_ * config_.tx_gain * config_.tx_gain;
  agc_gain_ = std::sqrt(target_symbol_power_ / std::max(agc_power_, 1.0e-8F));
}

bool Decoder::can_decode_next_symbol() const {
  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const double symbol_time = sample_clock_recovery_ ? next_symbol_time_
      : static_cast<double>(next_symbol_index_) + timing_offset_symbols_;
  // Match the inclusive right edge used by matched_filter_symbol(). Rounding
  // up would wait for a sample outside the filter support at fractional symbol
  // times, withholding the last symbol of a finite training/header block.
  const auto latest = static_cast<std::int64_t>(
      std::floor((symbol_time + half_span) * info_.samples_per_symbol));
  return static_cast<std::int64_t>(next_sample_index_) > latest;
}

Complex Decoder::matched_filter_symbol(std::int64_t symbol_index) const {
  if (sample_clock_recovery_) return matched_filter_at(next_symbol_time_);
  if (!taps_.empty()) {
    // Fast path: integer SPS -> precomputed taps, straight FMA accumulation.
    const auto sps = static_cast<std::int64_t>(sps_int_);
    const auto center = sps * symbol_index;  // sample index aligned to this symbol
    const auto start = std::max<std::int64_t>(first_sample_index_, center + taps_s_min_);
    const auto stop = std::min<std::int64_t>(static_cast<std::int64_t>(next_sample_index_) - 1,
                                              center + taps_s_max_);
    Complex y{0.0F, 0.0F};
    for (auto sample_index = start; sample_index <= stop; ++sample_index) {
      const auto offset = samples_head_ + static_cast<std::size_t>(sample_index - first_sample_index_);
      const auto tap_idx = static_cast<std::size_t>((sample_index - center) - taps_s_min_);
      y += samples_[offset] * taps_[tap_idx];
    }
    return y * sps_inv_;
  }

  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const double symbol_time = static_cast<double>(symbol_index) + timing_offset_symbols_;
  const auto start = static_cast<std::int64_t>(
      std::ceil((symbol_time - half_span) * info_.samples_per_symbol));
  const auto stop = static_cast<std::int64_t>(
      std::floor((symbol_time + half_span) * info_.samples_per_symbol));

  Complex y{0.0F, 0.0F};
  for (auto sample_index = start; sample_index <= stop; ++sample_index) {
    if (sample_index < first_sample_index_ || sample_index >= static_cast<std::int64_t>(next_sample_index_)) {
      continue;
    }
    const auto offset = samples_head_ + static_cast<std::size_t>(sample_index - first_sample_index_);
    const double sample_time = static_cast<double>(sample_index) / info_.samples_per_symbol;
    const auto h = static_cast<float>(rrc_impulse(sample_time - symbol_time, config_.rrc_rolloff));
    y += samples_[offset] * h;
  }

  return y / static_cast<float>(info_.samples_per_symbol);
}

void Decoder::append_sample(Complex sample) {
  samples_.push_back(sample);
  ++next_sample_index_;
}

void Decoder::prune_samples(std::int64_t decoded_symbol) {
  const double half_span = static_cast<double>(config_.filter_span_symbols) / 2.0;
  const double symbol_time = sample_clock_recovery_ ? next_symbol_time_ - 1.0
      : static_cast<double>(decoded_symbol) + timing_offset_symbols_;
  const auto keep_from = static_cast<std::int64_t>(
      std::floor((symbol_time - half_span) * info_.samples_per_symbol)) - 1;
  if (keep_from <= first_sample_index_) {
    return;
  }
  const auto live_size = samples_.size() - samples_head_;
  const auto remove_count = std::min<std::size_t>(
      static_cast<std::size_t>(keep_from - first_sample_index_), live_size);
  samples_head_ += remove_count;
  first_sample_index_ += static_cast<std::int64_t>(remove_count);
  // Amortized compaction: only memmove when the dead-head fraction is large.
  if (samples_head_ > 0U && samples_head_ * 2U >= samples_.size()) {
    samples_.erase(samples_.begin(),
                   samples_.begin() + static_cast<std::ptrdiff_t>(samples_head_));
    samples_head_ = 0U;
  }
}

Complex Decoder::apply_agc(Complex sample, std::uint32_t) {
  if (!config_.decoder_agc) {
    return sample;
  }
  const float power = std::max(std::norm(sample), 1.0e-8F);
  agc_power_ = 0.98F * agc_power_ + 0.02F * power;
  agc_gain_ = std::sqrt(target_symbol_power_ / std::max(agc_power_, 1.0e-8F));
  return sample * agc_gain_;
}

std::size_t BytePacker::push_bits(std::span<const std::uint8_t> bits, std::span<std::uint8_t> out) {
  std::size_t produced = 0;
  if (has_pending_) {
    if (out.empty()) {
      return 0;
    }
    out[produced++] = pending_;
    has_pending_ = false;
  }
  for (const auto bit : bits) {
    current_ = static_cast<std::uint8_t>((current_ << 1U) | (bit & 1U));
    ++filled_;
    if (filled_ == 8U) {
      if (produced == out.size()) {
        pending_ = current_;
        has_pending_ = true;
        current_ = 0;
        filled_ = 0;
        return produced;
      }
      out[produced++] = current_;
      current_ = 0;
      filled_ = 0;
    }
  }
  return produced;
}

void BytePacker::reset() noexcept {
  current_ = 0;
  filled_ = 0;
  pending_ = 0;
  has_pending_ = false;
}

} // namespace goblin_cannon
