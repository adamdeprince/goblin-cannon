#pragma once

#include "goblin_cannon/rf_stream.hpp"

#include <algorithm>
#include <cmath>
#include <numbers>
#include <vector>

namespace goblin_cannon::detail {

// Symbol-spaced decision-feedback equalizer. Zero decision delay needs no
// lookahead; a configured delay admits precursor cancellation on multipath
// channels. NLMS trains the span, optionally followed by sparse RLS tracking.
class RfEqualizer {
public:
  explicit RfEqualizer(const RfStreamConfig& config)
      : carrier_enabled_(config.carrier_correction),
        adaptive_(config.adaptive_equalization),
        spacing_(config.fractionally_spaced_equalization ? 2U : 1U),
        delay_(config.equalizer_delay_symbols * spacing_),
        reselect_interval_(config.equalizer_reselect_interval),
        forward_(validated_forward_taps(config)),
        feedback_(config.equalizer_feedback_taps),
        samples_(forward_.size()), decisions_(feedback_.size()) {
    reset();
  }

  void reset() {
    recursive_ = false;
    selection_updates_ = 0;
    std::fill(forward_.begin(), forward_.end(), Complex{});
    std::fill(feedback_.begin(), feedback_.end(), Complex{});
    forward_[delay_] = {1.0F, 0.0F};
    input_gain_ = 1.0F;
    gain_tracking_ = false;
    fast_power_ = slow_power_ = 1.0F;
    restart_training_pass();
  }

  void clear_history() {
    std::fill(samples_.begin(), samples_.end(), Complex{});
    std::fill(decisions_.begin(), decisions_.end(), Complex{});
    history_symbols_ = 0;
    if (recursive_) reset_covariance();
  }

  void restart_training_pass() {
    clear_history();
    phase_ = 0.0;
    frequency_ = 0.0;
    output_phase_ = {1.0F, 0.0F};
  }

  [[nodiscard]] std::size_t memory_symbols() const {
    return std::max((samples_.size() - 1U) / spacing_, decisions_.size());
  }

  // Training identifies the echo delays. Track only their strongest taps with
  // recursive least squares, avoiding a full 512-by-512 matrix per symbol.
  // Retain near-cursor taps for pulse-shaping and fractional-delay ISI.
  void start_recursive_tracking() {
    if (!adaptive_) return;
    active_.clear();
    const auto select = [&](const auto& weights, std::size_t base, std::size_t center, std::size_t near, std::size_t limit) {
      std::vector<std::size_t> indices;
      for (std::size_t i = 0; i < weights.size(); ++i) indices.push_back(i);
      std::stable_sort(indices.begin(), indices.end(), [&](auto a, auto b) {
        const auto close = [&](auto i) { return (i > center ? i-center : center-i) < near; };
        if (close(a) != close(b)) return close(a);
        return std::norm(weights[a]) > std::norm(weights[b]);
      });
      indices.resize(std::min(limit, indices.size()));
      for (const auto index : indices) active_.push_back(base + index);
    };
    select(forward_, 0, delay_, 2 * spacing_, 12);
    select(feedback_, forward_.size(), 0, 2, 12);
    for (std::size_t i = 0; i < forward_.size() + feedback_.size(); ++i) {
      if (std::find(active_.begin(), active_.end(), i) == active_.end()) {
        (i < forward_.size() ? forward_[i] : feedback_[i-forward_.size()]) = {};
      }
    }
    const auto n = active_.size();
    shadow_forward_ = forward_;
    shadow_feedback_ = feedback_;
    covariance_.resize(n*n);
    reset_covariance();
    feature_.resize(n); gain_numerator_.resize(n);
    recursive_ = true;
  }

  void advance_phase(double symbols) {
    phase_ = std::remainder(phase_ + frequency_ * symbols, 2.0 * std::numbers::pi);
  }

  Complex filter(Complex sample, Complex half_sample = {}) {
    const float power = std::norm(sample);
    fast_power_ += 0.125F * (power-fast_power_);
    slow_power_ += 0.002F * (power-slow_power_);
    const auto ratio = fast_power_/std::max(slow_power_,1.0e-8F);
    power_excursion_ = ratio < 0.3F || ratio > 3.0F;
    sample *= input_gain_;
    half_sample *= input_gain_;
    advance_phase(1.0);
    if (carrier_enabled_) {
      sample *= std::polar(1.0F, static_cast<float>(-phase_));
      half_sample *= std::polar(1.0F, static_cast<float>(-phase_ + frequency_ * 0.5));
    }
    if (spacing_ == 2 && samples_.size() > 1) {
      std::move_backward(samples_.begin(), samples_.end() - 1, samples_.end());
      samples_.front() = half_sample;
    }
    std::move_backward(samples_.begin(), samples_.end() - 1, samples_.end());
    samples_.front() = sample;
    Complex output{};
    for (std::size_t i = 0; i < forward_.size(); ++i) {
      output += forward_[i] * samples_[i];
    }
    last_forward_ = output * output_phase_;
    output = last_forward_;
    for (std::size_t i = 0; i < feedback_.size(); ++i) {
      output += feedback_[i] * decisions_[i];
    }
    return output;
  }

  // Known pilots resolve QAM's amplitude ambiguity after a radio AGC step.
  // Only correct a positive real gain: a phase mismatch still fails the pilot
  // check. Feedback coefficients describe ISI relative to the main cursor and
  // must not be scaled with the incoming signal.
  Complex track_pilot_gain(Complex desired, Complex observed) {
    if (!adaptive_ || std::norm(last_forward_) < 1.0e-8F) return observed;
    const auto power_ratio = fast_power_/std::max(slow_power_,1.0e-8F);
    if (power_ratio > 0.3F && power_ratio < 3.0F && !(recursive_ && gain_tracking_)) return observed;
    const auto wanted = desired - (observed - last_forward_);
    const auto ratio = wanted / last_forward_;
    if (std::abs(std::arg(ratio)) > (recursive_ ? 0.5F : 0.2F)) return observed;
    // Least-squares positive real scale; magnitude would overcorrect when a
    // pilot also carries residual phase/ISI error.
    const float gain = std::clamp(ratio.real(), 0.0625F, 16.0F);
    if (recursive_ ? (gain >= 0.95F && gain <= 1.05F) : (gain >= 0.8F && gain <= 1.25F)) return observed;
    input_gain_ *= gain;
    gain_tracking_ = input_gain_ < 0.95F || input_gain_ > 1.05F;
    if (recursive_) reset_covariance();
    for (auto& value : samples_) value *= gain;
    observed += last_forward_ * (gain - 1.0F);
    last_forward_ *= gain;
    return observed;
  }

  // Always record a decision for causal feedback. Low confidence freezes both
  // loops rather than teaching the equalizer errors during a fade.
  void update(Complex desired, Complex observed, float step, bool reliable, bool known = false) {
    bool phase_reliable = reliable;
    if (recursive_ && !known) {
      // A nearest-point confidence can be high even when an AGC step puts the
      // entire constellation near zero. Such decisions must not retrain the
      // feedback filter. Pilots supply supervised updates through that interval.
      const auto power_ratio = fast_power_/std::max(slow_power_,1.0e-8F);
      if (gain_tracking_ || power_ratio < 0.7F || power_ratio > 1.5F) {
        reliable = reliable && std::norm(desired-observed) <= 0.01F*std::norm(desired);
      }
      // Phase can still be learned from a reliable decision outside that tight
      // amplitude/ISI gate. Freeze it during a level excursion, where a sliced
      // QAM point can have the wrong angle as well as the wrong amplitude.
      phase_reliable = phase_reliable && power_ratio >= 0.7F && power_ratio <= 1.5F;
    }
    // During an abrupt gain excursion, sliced QAM amplitudes are ambiguous.
    // Learn from known pilots until level tracking restores the signal.
    if (recursive_ && power_excursion_) reliable = known;
    const bool usable = history_symbols_ >= memory_symbols() &&
        std::isfinite(observed.real()) && std::isfinite(observed.imag());
    if (reliable && usable) {
      const auto error = desired - observed;
      if (carrier_enabled_ && !recursive_ && std::norm(desired) > 1.0e-6F && std::norm(observed) > 1.0e-6F) {
        const auto phase_error = std::clamp(static_cast<double>(std::arg(observed * std::conj(desired))), -0.5, 0.5);
        frequency_ = std::clamp(frequency_ + 0.0005 * phase_error, -0.05, 0.05);
        phase_ = std::remainder(phase_ + 0.08 * phase_error, 2.0 * std::numbers::pi);
      }
      if (adaptive_) {
        if (recursive_) {
          update_recursive(error);
          if (reselect_interval_ != 0) {
            // Candidate taps see the same residual and history as the active
            // filter. This lets a newly important echo enter the next support.
            float energy = 1.0e-4F;
            for (const auto v : samples_) energy += std::norm(v);
            for (const auto v : decisions_) energy += std::norm(v);
            const auto correction = error * (step / energy);
            for (std::size_t i = 0; i < forward_.size(); ++i)
              shadow_forward_[i] += correction * std::conj(samples_[i] * output_phase_);
            for (std::size_t i = 0; i < feedback_.size(); ++i)
              shadow_feedback_[i] += correction * std::conj(decisions_[i]);
            if (++selection_updates_ >= reselect_interval_) {
              for (const auto i : active_)
                (i < forward_.size() ? shadow_forward_[i] : shadow_feedback_[i-forward_.size()]) =
                    i < forward_.size() ? forward_[i] : feedback_[i-forward_.size()];
              forward_ = shadow_forward_;
              feedback_ = shadow_feedback_;
              start_recursive_tracking();
              selection_updates_ = 0;
            }
          }
        } else {
          float energy = 1.0e-4F;
          for (const auto value : samples_) {
            energy += std::norm(value);
          }
          for (const auto value : decisions_) {
            energy += std::norm(value);
          }
          const auto correction = error * (step / energy);
          for (std::size_t i = 0; i < forward_.size(); ++i) {
            forward_[i] += correction * std::conj(samples_[i] * output_phase_);
          }
          for (std::size_t i = 0; i < feedback_.size(); ++i) {
            feedback_[i] += correction * std::conj(decisions_[i]);
          }
        }
      }
    }
    // First-order phase coefficient, with no frequency estimate or phase-rate
    // accumulator. Feedback decisions already use the corrected constellation;
    // rotating them again would force the ISI filter to chase common phase.
    if (adaptive_ && recursive_ && phase_reliable && usable &&
        std::norm(desired) > 1.0e-6F && std::norm(observed) > 1.0e-6F) {
      // Weight phase evidence by symbol energy. Inner QAM points have much
      // noisier angles than the outer points; treating every angle equally
      // injects their timing/ISI error into the entire constellation.
      const auto wanted_forward = desired - (observed - last_forward_);
      const auto phase_error = std::clamp(std::imag(last_forward_*std::conj(wanted_forward)) /
          std::max(std::norm(wanted_forward), 0.25F), -0.5F, 0.5F);
      output_phase_ *= std::polar(1.0F, -0.3F*phase_error);
      output_phase_ /= std::abs(output_phase_);
    }
    if (!decisions_.empty()) {
      std::move_backward(decisions_.begin(), decisions_.end() - 1, decisions_.end());
      decisions_.front() = desired;
    }
    ++history_symbols_;
  }

private:
  void reset_covariance() {
    std::fill(covariance_.begin(), covariance_.end(), std::complex<double>{});
    for (std::size_t i = 0; i < active_.size(); ++i) covariance_[i*active_.size()+i] = 0.1;
  }

  void update_recursive(Complex error) {
    constexpr double forgetting = 0.985;
    const auto n = active_.size();
    for (std::size_t i = 0; i < n; ++i) {
      const auto index = active_[i];
      feature_[i] = index < forward_.size() ? samples_[index]*output_phase_ : decisions_[index-forward_.size()];
    }
    double denominator = forgetting;
    for (std::size_t i = 0; i < n; ++i) {
      auto& value = gain_numerator_[i]; value = {};
      for (std::size_t j = 0; j < n; ++j) value += covariance_[i*n+j] * std::conj(feature_[j]);
      denominator += std::real(feature_[i] * value);
    }
    if (!std::isfinite(denominator) || denominator <= 0.0) {
      start_recursive_tracking();
      return;
    }
    for (std::size_t i = 0; i < n; ++i) {
      auto& weight = active_[i] < forward_.size() ? forward_[active_[i]] : feedback_[active_[i]-forward_.size()];
      weight += static_cast<Complex>(gain_numerator_[i] * std::complex<double>(error) / denominator);
      for (std::size_t j = 0; j <= i; ++j) {
        auto value = (covariance_[i*n+j] - gain_numerator_[i]*std::conj(gain_numerator_[j])/denominator) / forgetting;
        if (i == j) value = {value.real(), 0};
        covariance_[i*n+j] = value;
        covariance_[j*n+i] = std::conj(value);
      }
    }
    double largest = 0;
    for (std::size_t i = 0; i < n; ++i) largest = std::max(largest, covariance_[i*n+i].real());
    if (largest > 1.0) {
      // Bound uncertainty in unexcited directions without destroying positive
      // definiteness by clipping individual covariance entries.
      for (auto& value : covariance_) value *= 1.0/largest;
    }
  }

  static std::size_t validated_forward_taps(const RfStreamConfig& config) {
    validate(config);
    return config.fractionally_spaced_equalization ? 2U * config.equalizer_feedforward_taps - 1U
                                                 : config.equalizer_feedforward_taps;
  }

  bool carrier_enabled_;
  float input_gain_ = 1.0F;
  float fast_power_ = 1.0F, slow_power_ = 1.0F;
  bool power_excursion_ = false;
  bool gain_tracking_ = false;
  Complex last_forward_{};
  Complex output_phase_ = {1.0F, 0.0F};
  bool adaptive_;
  std::size_t spacing_ = 1;
  std::size_t delay_ = 0;
  std::size_t reselect_interval_ = 0, selection_updates_ = 0;
  std::vector<Complex> shadow_forward_, shadow_feedback_;
  bool recursive_ = false;
  std::vector<std::size_t> active_;
  std::vector<std::complex<double>> covariance_, feature_, gain_numerator_;
  std::vector<Complex> forward_;
  std::vector<Complex> feedback_;
  std::vector<Complex> samples_;
  std::vector<Complex> decisions_;
  std::size_t history_symbols_ = 0;
  double phase_ = 0.0;
  double frequency_ = 0.0;
};

} // namespace goblin_cannon::detail
