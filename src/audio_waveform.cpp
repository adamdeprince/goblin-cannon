#include "audio_waveform.hpp"
#include "goblin_cannon/convolutional.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <deque>
#include <map>
#include <numbers>
#include <stdexcept>

namespace goblin_cannon::detail {
namespace {
constexpr double tau = 2 * std::numbers::pi;
constexpr std::array<unsigned, 16> sync_tones{0, 3, 1, 2, 3, 0, 2, 1, 0, 2, 3, 1, 3, 2, 0, 1};
RfStreamHeader header_for(const RfStreamConfig& c, std::uint64_t frame) {
  RfStreamHeader h;
  h.schedule_epoch_low = static_cast<std::uint32_t>(c.expected_schedule_epoch);
  h.frame_counter_start = frame;
  h.symbols_per_frame = c.symbols_per_frame;
  h.pilot_interval_symbols = c.pilot_interval_symbols;
  h.modulation = c.modem.modulation;
  h.header_modulation = c.header_modulation;
  h.crc32 = stream_header_crc32(h);
  return h;
}
struct FskParameters {
  unsigned tones, bits;
  std::size_t useful, guard, symbol, tick, header_symbols;
  std::array<double, 8> frequencies{};
  explicit FskParameters(const RfStreamConfig& c) {
    tones = c.waveform == AudioWaveform::fsk4 ? 4 : 8;
    bits = tones == 4 ? 2 : 3;
    const double fs = c.modem.sample_rate_hz;
    if (bits_per_symbol(c.modem.modulation) != bits || c.differential_mapping != DifferentialMapping::none ||
        c.carrier_correction)
      throw std::invalid_argument("FSK requires matching 2/3-bit payload labeling, no differential mapping "
                                  "and carrier correction off");
    if (!std::isfinite(c.fsk_useful_ms) || !std::isfinite(c.fsk_guard_ms) || c.fsk_useful_ms < 1 ||
        c.fsk_useful_ms > 20 || c.fsk_guard_ms < 0 || c.fsk_guard_ms > 50)
      throw std::invalid_argument("FSK useful time must be [1,20] ms and guard [0,50] ms");
    useful = std::llround(fs * c.fsk_useful_ms / 1000);
    guard = std::llround(fs * c.fsk_guard_ms / 1000);
    tick = std::llround(fs / 1000);
    symbol = useful + guard;
    if (!tick || std::abs(fs / 1000 - tick) > 1e-9 || useful % tick || guard % tick)
      throw std::invalid_argument("FSK timing requires integer millisecond durations and integer samples/ms");
    const auto bins = std::floor(c.modem.bandwidth_hz / (tones + 2) / (fs / useful));
    if (bins < 1)
      throw std::invalid_argument("FSK tones do not fit the configured bandwidth");
    for (unsigned i = 0; i < tones; ++i)
      frequencies[i] = (i - (tones - 1) / 2.0) * bins * fs / useful;
    header_symbols = (2 * (128 + 6) + bits - 1) / bits;
  }
};
std::uint32_t fsk_crc(const RfStreamConfig& c, std::uint64_t frame) {
  auto crc = header_for(c, frame).crc32;
  // Fixed framing parameters are bound to the checksum, configured over fiber.
  for (auto v : {static_cast<unsigned>(c.waveform), static_cast<unsigned>(std::llround(c.fsk_useful_ms)),
                 static_cast<unsigned>(std::llround(c.fsk_guard_ms))})
    crc = (crc ^ v) * 16777619U;
  return crc;
}
std::vector<std::uint32_t> fsk_prefix(const RfStreamConfig& c, const FskParameters& p, std::uint64_t frame) {
  std::vector<std::uint32_t> out;
  for (auto tone : sync_tones)
    out.push_back(p.tones == 8 ? tone * 2 : tone);
  std::array<std::uint8_t, 16> bytes{};
  for (unsigned i = 0; i < 4; ++i)
    bytes[i] = c.expected_schedule_epoch >> (8 * (3 - i));
  for (unsigned i = 0; i < 8; ++i)
    bytes[4 + i] = frame >> (8 * (7 - i));
  const auto crc = fsk_crc(c, frame);
  for (unsigned i = 0; i < 4; ++i)
    bytes[12 + i] = crc >> (8 * (3 - i));
  PuncturedConvolutionalEncoder encoder;
  auto coded = encoder.push_bytes(bytes);
  for (unsigned i = 0; i < 6; ++i)
    encoder.push_bit_append(0, coded);
  while (coded.size() % p.bits)
    coded.push_back(0);
  for (std::size_t i = 0; i < coded.size(); i += p.bits) {
    unsigned symbol = 0;
    for (unsigned j = 0; j < p.bits; ++j)
      symbol = (symbol << 1) | coded[i + j];
    out.push_back(symbol);
  }
  return out;
}

class FskEncoder final : public AudioWaveformEncoder {
public:
  explicit FskEncoder(RfStreamConfig c) : c_(std::move(c)), p_(c_) { validate(c_); }
  const RfStreamConfig& config() const noexcept override { return c_; }
  bool active() const noexcept override { return active_; }
  RfStreamState state() const noexcept override {
    return active_ ? (prefix_at_ < prefix_.size() ? RfStreamState::header : RfStreamState::locked)
                   : RfStreamState::search;
  }
  RfStreamHeader current_header() const noexcept override { return header_for(c_, frame_); }
  void start_epoch(std::uint64_t frame) override {
    reset();
    frame_ = frame;
    active_ = true;
    prefix_ = fsk_prefix(c_, p_, frame_);
  }
  void reset() override {
    active_ = false;
    draining_ = false;
    frame_ = 0;
    payload_ = 0;
    prefix_at_ = 0;
    remaining_ = 0;
    phase_ = {1, 0};
    prefix_.clear();
  }
  RfStreamEncodeResult push_symbols(std::span<const std::uint32_t> symbols, std::span<Complex> out) override {
    RfStreamEncodeResult result;
    // Equal nominal total mean power to the original full-band RRC waveform.
    const double amplitude =
        c_.modem.tx_gain;
    while (active_ && result.produced_samples < out.size()) {
      if (!remaining_) {
        if (payload_ == c_.symbols_per_frame) {
          if (draining_) {
            active_ = false;
            break;
          }
          ++frame_;
          payload_ = 0;
          prefix_ = fsk_prefix(c_, p_, frame_);
          prefix_at_ = 0;
        }
        unsigned tone = 0;
        if (prefix_at_ < prefix_.size())
          tone = prefix_[prefix_at_++];
        else {
          if (result.consumed_symbols == symbols.size()) {
            if (!draining_)
              break;
          } else
            tone = symbols[result.consumed_symbols++];
          if (tone >= p_.tones)
            throw std::invalid_argument("FSK symbol exceeds tone alphabet");
          ++payload_;
        }
        rotation_ = std::polar(1.0, tau * p_.frequencies[tone] / c_.modem.sample_rate_hz);
        remaining_ = p_.symbol;
      }
      out[result.produced_samples++] = Complex(phase_ * amplitude);
      phase_ *= rotation_;
      --remaining_;
      if (!remaining_)
        phase_ /= std::abs(phase_);
    }
    result.state = state();
    return result;
  }
  RfStreamEncodeResult drain(std::span<Complex> out) override {
    draining_ = true;
    return push_symbols({}, out);
  }

private:
  RfStreamConfig c_;
  FskParameters p_;
  bool active_ = false, draining_ = false;
  std::uint64_t frame_ = 0;
  std::size_t payload_ = 0, prefix_at_ = 0, remaining_ = 0;
  std::vector<std::uint32_t> prefix_;
  std::complex<double> phase_{1, 0}, rotation_{1, 0};
};

class FskReceiver final : public AudioWaveformReceiver {
public:
  explicit FskReceiver(RfStreamConfig c)
      : c_(std::move(c)), p_(c_), history_(p_.useful),
        energy_history_((sync_tones.size() + 2) * p_.symbol / p_.tick) {
    validate(c_);
    for (unsigned i = 0; i < p_.tones; ++i) {
      rotations_[i] = std::polar(1.0, -tau * p_.frequencies[i] / c_.modem.sample_rate_hz);
      old_rotations_[i] = std::polar(1.0, tau * p_.frequencies[i] * p_.useful / c_.modem.sample_rate_hz);
    }
    reset();
  }
  const RfStreamConfig& config() const noexcept override { return c_; }
  RfStreamState state() const noexcept override { return state_; }
  std::optional<RfStreamHeader> header() const noexcept override { return header_; }
  RfSyncEstimate sync_estimate() const noexcept override { return {}; }
  void reset() override {
    state_ = RfStreamState::search;
    header_.reset();
    samples_ = 0;
    ticks_ = 0;
    next_decision_ = 0;
    payload_ = 0;
    std::fill(history_.begin(), history_.end(), Complex{});
    for (auto& e : energy_history_)
      e = {};
    phases_.fill({1, 0});
    sums_.fill({0, 0});
    header_bits_.clear();
  }
  RfStreamReceiveResult push_samples(std::span<const Complex> samples,
                                     std::span<RfStreamSymbol> out) override {
    RfStreamReceiveResult result;
    for (auto sample : samples) {
      // Never consume a symbol's last sample if the caller cannot receive it.
      if (state_ == RfStreamState::locked && samples_ + 1 == next_decision_ &&
          result.produced_symbols == out.size())
        break;
      const auto old = history_[samples_ % p_.useful];
      history_[samples_ % p_.useful] = sample;
      for (unsigned i = 0; i < p_.tones; ++i) {
        sums_[i] += std::complex<double>(sample) * phases_[i] -
                    std::complex<double>(old) * phases_[i] * old_rotations_[i];
        phases_[i] *= rotations_[i];
      }
      ++samples_;
      ++result.consumed_samples;
      if (samples_ % 4096 == 0)
        for (unsigned i = 0; i < p_.tones; ++i)
          phases_[i] /= std::abs(phases_[i]);
      if (samples_ % p_.tick)
        continue;
      std::array<float, 8> energy{};
      for (unsigned i = 0; i < p_.tones; ++i)
        energy[i] = std::norm(sums_[i] / static_cast<double>(p_.useful));
      energy_history_[ticks_ % energy_history_.size()] = energy;
      ++ticks_;
      if (state_ == RfStreamState::search) {
        const auto stride = p_.symbol / p_.tick;
        if (ticks_ < (sync_tones.size() - 1) * stride + 1)
          continue;
        float score = 0;
        unsigned matched = 0;
        for (unsigned i = 0; i < sync_tones.size(); ++i) {
          const auto& e =
              energy_history_[(ticks_ - 1 - (sync_tones.size() - 1 - i) * stride) % energy_history_.size()];
          const auto expected = p_.tones == 8 ? sync_tones[i] * 2 : sync_tones[i];
          const auto best = std::max_element(e.begin(), e.begin() + p_.tones);
          float total = 0;
          for (unsigned j = 0; j < p_.tones; ++j)
            total += e[j];
          score += total > 0 ? e[expected] / total : 0;
          matched += static_cast<unsigned>(best - e.begin()) == expected;
        }
        if (matched >= 14 && score / sync_tones.size() >= 0.65F) {
          state_ = RfStreamState::header;
          header_bits_.clear();
          next_decision_ = samples_ + p_.guard + p_.symbol;
          result.acquisition_found = true;
          result.acquisition.found = true;
          result.acquisition.confidence = score / sync_tones.size();
        }
        continue;
      }
      if (samples_ != next_decision_)
        continue;
      next_decision_ += p_.symbol;
      auto symbol = decision(energy);
      if (state_ == RfStreamState::header) {
        for (unsigned i = 0; i < p_.bits; ++i)
          header_bits_.push_back(symbol.soft_bits[i]);
        if (header_bits_.size() < p_.header_symbols * p_.bits)
          continue;
        const auto decoded = SoftViterbiDecoder().decode(header_bits_, 134);
        std::uint32_t epoch = 0, crc = 0;
        std::uint64_t frame = 0;
        for (unsigned i = 0; i < 4; ++i)
          epoch = (epoch << 8) | decoded.bytes[i].value;
        for (unsigned i = 4; i < 12; ++i)
          frame = (frame << 8) | decoded.bytes[i].value;
        for (unsigned i = 12; i < 16; ++i)
          crc = (crc << 8) | decoded.bytes[i].value;
        if (epoch != static_cast<std::uint32_t>(c_.expected_schedule_epoch) || crc != fsk_crc(c_, frame)) {
          state_ = RfStreamState::search;
          result.lock_lost = true;
          continue;
        }
        header_ = header_for(c_, frame);
        state_ = RfStreamState::locked;
        payload_ = 0;
        result.header_valid = true;
      } else {
        symbol.frame_counter = header_->frame_counter_start;
        symbol.frame_symbol_offset = payload_++;
        out[result.produced_symbols++] = symbol;
        if (payload_ == c_.symbols_per_frame)
          state_ = RfStreamState::search;
      }
    }
    result.state = state_;
    result.header = header_;
    return result;
  }

private:
  RfStreamSymbol decision(const std::array<float, 8>& energy) const {
    float variance = 0, peak = 0;
    for (unsigned i = 0; i < p_.tones; ++i) {
      variance += energy[i];
      peak = std::max(peak, energy[i]);
    }
    variance -= peak;
    variance = std::max(1e-10F, variance / (p_.tones - 1));
    RfStreamSymbol out;
    out.bits_per_symbol = p_.bits;
    out.has_soft_bits = true;
    out.confidence = 1;
    // Conventional noncoherent energy-bank max-log scores. They use the other
    // tone bins to estimate residual noise, not simulated channel state.
    for (unsigned bit = 0; bit < p_.bits; ++bit) {
      float best[2] = {0, 0};
      for (unsigned tone = 0; tone < p_.tones; ++tone) {
        const auto b = (tone >> (p_.bits - bit - 1)) & 1;
        best[b] = std::max(best[b], energy[tone]);
      }
      const auto llr = std::clamp((best[0] - best[1]) / variance, -64.0F, 64.0F);
      const auto confidence = std::tanh(std::abs(llr) * .5F);
      out.soft_bits[bit] = {static_cast<std::uint8_t>(llr < 0), llr != 0, confidence, llr};
      out.value = (out.value << 1) | (llr < 0);
      out.confidence = std::min(out.confidence, confidence);
    }
    out.certain = out.confidence >= c_.symbol_confidence_threshold;
    return out;
  }
  RfStreamConfig c_;
  FskParameters p_;
  std::vector<Complex> history_;
  std::vector<std::array<float, 8>> energy_history_;
  std::array<std::complex<double>, 8> rotations_{}, old_rotations_{}, phases_{}, sums_{};
  std::uint64_t samples_ = 0, ticks_ = 0, next_decision_ = 0;
  unsigned payload_ = 0;
  std::vector<SoftBit> header_bits_;
  std::optional<RfStreamHeader> header_;
  RfStreamState state_ = RfStreamState::search;
};

double diversity_separation(const RfStreamConfig& c) {
  return c.diversity_separation_hz == 0 ? c.modem.bandwidth_hz / 2 : c.diversity_separation_hz;
}
RfStreamConfig diversity_branch(const RfStreamConfig& c) {
  if (c.modem.modulation != Modulation::bpsk || c.differential_mapping != DifferentialMapping::none ||
      !c.recovery_interval_frames)
    throw std::invalid_argument("frequency diversity requires coherent BPSK and absolute recovery markers");
  auto b = c;
  b.waveform = AudioWaveform::single_carrier;
  b.modem.bandwidth_hz = c.diversity_branch_bandwidth_hz == 0 ? c.modem.bandwidth_hz / 2
                                                           : c.diversity_branch_bandwidth_hz;
  const auto separation = diversity_separation(c);
  if (!std::isfinite(b.modem.bandwidth_hz) || b.modem.bandwidth_hz <= 0 ||
      !std::isfinite(separation) || separation < b.modem.bandwidth_hz ||
      separation + b.modem.bandwidth_hz > c.modem.bandwidth_hz ||
      c.diversity_branch_mask < 1 || c.diversity_branch_mask > 3)
    throw std::invalid_argument("diversity copies must be nonoverlapping, fit the audio bandwidth, and select mask 1, 2 or 3");
  b.modem.symbol_rate_hz = b.modem.bandwidth_hz / 1.25;
  // RRC amplitudes use symbol-time normalization: mean sample power is gain^2,
  // independent of symbol rate. The mixer splits that power across two copies.
  b.modem.tx_gain = c.modem.tx_gain;
  b.soft_demapping = true;
  return b;
}
class DiversityEncoder final : public AudioWaveformEncoder {
public:
  explicit DiversityEncoder(RfStreamConfig c) : c_(std::move(c)), tx_(diversity_branch(c_)) {}
  const RfStreamConfig& config() const noexcept override { return c_; }
  bool active() const noexcept override { return tx_.active(); }
  RfStreamState state() const noexcept override { return tx_.state(); }
  RfStreamHeader current_header() const noexcept override { return tx_.current_header(); }
  void start_epoch(std::uint64_t frame) override {
    sample_ = 0;
    tx_.start_epoch(frame);
  }
  void reset() override {
    sample_ = 0;
    tx_.reset();
  }
  RfStreamEncodeResult push_symbols(std::span<const std::uint32_t> symbols, std::span<Complex> out) override {
    auto r = tx_.push_symbols(symbols, out);
    mix(out.first(r.produced_samples));
    return r;
  }
  RfStreamEncodeResult drain(std::span<Complex> out) override {
    auto r = tx_.drain(out);
    mix(out.first(r.produced_samples));
    return r;
  }

private:
  void mix(std::span<Complex> out) {
    for (auto& s : out) {
      const auto phase = tau * (diversity_separation(c_) / 2) / c_.modem.sample_rate_hz * (sample_++);
      if (c_.diversity_branch_mask == 3)
        s *= static_cast<float>(std::sqrt(2.0) * std::cos(phase));
      else
        s *= Complex(std::polar(1.0, c_.diversity_branch_mask == 1 ? -phase : phase));
    }
  }
  RfStreamConfig c_;
  RfStreamEncoder tx_;
  std::uint64_t sample_ = 0;
};
class DiversityReceiver final : public AudioWaveformReceiver {
public:
  explicit DiversityReceiver(RfStreamConfig c)
      : c_(std::move(c)),
        rx_{RfStreamReceiver(diversity_branch(c_)), RfStreamReceiver(diversity_branch(c_))} {}
  const RfStreamConfig& config() const noexcept override { return c_; }
  RfStreamState state() const noexcept override {
    return ((c_.diversity_branch_mask & 1) && rx_[0].state() == RfStreamState::locked) ||
                   ((c_.diversity_branch_mask & 2) && rx_[1].state() == RfStreamState::locked)
               ? RfStreamState::locked
               : RfStreamState::search;
  }
  std::optional<RfStreamHeader> header() const noexcept override {
    return (c_.diversity_branch_mask & 1) && rx_[0].header() ? rx_[0].header() : rx_[1].header();
  }
  RfSyncEstimate sync_estimate() const noexcept override {
    return rx_[c_.diversity_branch_mask == 2 ? 1 : 0].sync_estimate();
  }
  void reset() override {
    for (auto& r : rx_)
      r.reset();
    sample_ = 0;
    pending_.clear();
    last_.reset();
    was_locked_ = false;
  }
  RfStreamReceiveResult push_samples(std::span<const Complex> samples,
                                     std::span<RfStreamSymbol> out) override {
    RfStreamReceiveResult result;
    // Wait expires even when one copy fades; quantized to this bounded audio block.
    while (result.consumed_samples < samples.size()) {
      if (result.produced_symbols == out.size())
        break;
      const auto count = std::min<std::size_t>(48, samples.size() - result.consumed_samples);
      std::array<Complex, 48> base{};
      std::array<RfStreamSymbol, 128> decoded{};
      bool actual_loss = false;
      for (unsigned branch = 0; branch < 2; ++branch) {
        if (!(c_.diversity_branch_mask & (1U << branch))) continue;
        for (unsigned i = 0; i < count; ++i) {
          const auto phase =
              (branch ? 1 : -1) * tau * (diversity_separation(c_) / 2) / c_.modem.sample_rate_hz * (sample_ + i);
          base[i] = samples[result.consumed_samples + i] * Complex(std::polar(1.0, -phase));
        }
        const auto r = rx_[branch].push_samples(std::span(base).first(count), decoded);
        if (r.consumed_samples != count)
          throw std::logic_error("diversity branch failed to consume bounded audio");
        result.acquisition_found |= r.acquisition_found;
        result.header_valid |= r.header_valid;
        actual_loss |= r.lock_lost;
        for (unsigned i = 0; i < r.produced_symbols; ++i) {
          const auto& s = decoded[i];
          const auto key = std::pair{s.frame_counter, s.frame_symbol_offset};
          if (last_ && key <= *last_)
            continue;
          auto [it, inserted] = pending_.try_emplace(key);
          if (inserted)
            it->second.arrival = sample_ + count;
          it->second.symbol[branch] = s;
        }
      }
      sample_ += count;
      result.consumed_samples += count;
      while (!pending_.empty() && result.produced_symbols < out.size()) {
        auto it = pending_.begin();
        auto& p = it->second;
        if (c_.diversity_branch_mask == 3 && (!p.symbol[0] || !p.symbol[1]) &&
            sample_ - p.arrival <
                static_cast<std::uint64_t>(std::ceil(c_.diversity_wait_ms * c_.modem.sample_rate_hz / 1000)))
          break;
        auto s = p.symbol[0] ? *p.symbol[0] : *p.symbol[1];
        if (p.symbol[0] && p.symbol[1]) {
          const auto llr = std::clamp(p.symbol[0]->soft_bits[0].log_likelihood_ratio +
                                          p.symbol[1]->soft_bits[0].log_likelihood_ratio,
                                      -64.0F, 64.0F);
          s.value = llr < 0;
          s.confidence = std::tanh(std::abs(llr) * .5F);
          s.certain = s.confidence >= c_.symbol_confidence_threshold;
          s.has_soft_bits = true;
          s.soft_bits[0] = {static_cast<std::uint8_t>(s.value), llr != 0, s.confidence, llr};
        }
        out[result.produced_symbols++] = s;
        last_ = it->first;
        pending_.erase(it);
      }
      const bool locked = state() == RfStreamState::locked;
      result.lock_lost |= actual_loss && !locked;
      was_locked_ = locked;
    }
    result.state = state();
    result.header = header();
    result.sync = sync_estimate();
    return result;
  }

private:
  struct Pending {
    std::optional<RfStreamSymbol> symbol[2];
    std::uint64_t arrival = 0;
  };
  RfStreamConfig c_;
  std::array<RfStreamReceiver, 2> rx_;
  std::uint64_t sample_ = 0;
  bool was_locked_ = false;
  std::map<std::pair<std::uint64_t, std::uint32_t>, Pending> pending_;
  std::optional<std::pair<std::uint64_t, std::uint32_t>> last_;
};
} // namespace
void validate_audio_waveform(const RfStreamConfig& c) {
  if (c.waveform == AudioWaveform::single_carrier)
    return;
  if (c.waveform == AudioWaveform::bpsk_frequency_diversity) {
    (void)diversity_branch(c);
    if (!std::isfinite(c.diversity_wait_ms) || c.diversity_wait_ms < 0 || c.diversity_wait_ms > 10)
      throw std::invalid_argument("diversity combining wait must be [0,10] ms");
  } else if (c.waveform == AudioWaveform::fsk4 || c.waveform == AudioWaveform::fsk8)
    (void)FskParameters(c);
  else
    throw std::invalid_argument("unknown audio waveform");
}
std::unique_ptr<AudioWaveformEncoder> make_audio_encoder(RfStreamConfig c) {
  validate(c);
  if (c.waveform == AudioWaveform::bpsk_frequency_diversity)
    return std::make_unique<DiversityEncoder>(std::move(c));
  if (c.waveform == AudioWaveform::fsk4 || c.waveform == AudioWaveform::fsk8)
    return std::make_unique<FskEncoder>(std::move(c));
  throw std::invalid_argument("unknown audio waveform");
}
std::unique_ptr<AudioWaveformReceiver> make_audio_receiver(RfStreamConfig c) {
  validate(c);
  if (c.waveform == AudioWaveform::bpsk_frequency_diversity)
    return std::make_unique<DiversityReceiver>(std::move(c));
  if (c.waveform == AudioWaveform::fsk4 || c.waveform == AudioWaveform::fsk8)
    return std::make_unique<FskReceiver>(std::move(c));
  throw std::invalid_argument("unknown audio waveform");
}
} // namespace goblin_cannon::detail
