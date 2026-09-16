#pragma once

// Shared simulated channel used by regression and characterization tests.
#include "goblin_cannon/modem.hpp"
#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <limits>
#include <numbers>
#include <random>
#include <span>
#include <stdexcept>
#include <vector>

namespace goblin_cannon::test {
inline constexpr double tau = 2.0 * std::numbers::pi;
// Explicit Box-Muller transform: mt19937 is specified, whereas the sequence
// produced by std::normal_distribution can differ between standard libraries.
class GaussianNoise {
public:
  explicit GaussianNoise(std::uint32_t seed) : engine_(seed) {}

  Complex next() {
    const double u = (static_cast<double>(engine_()) + 0.5) / 4294967296.0;
    const double v = (static_cast<double>(engine_()) + 0.5) / 4294967296.0;
    const double radius = std::sqrt(-2.0 * std::log(u));
    return {static_cast<float>(radius * std::cos(tau * v)),
            static_cast<float>(radius * std::sin(tau * v))};
  }

private:
  std::mt19937 engine_;
};

inline double mean_power(std::span<const Complex> samples) {
  if (samples.empty()) throw std::invalid_argument("cannot measure empty waveform");
  double power = 0.0;
  for (const auto sample : samples) {
    power += std::norm(sample);
  }
  return power / static_cast<double>(samples.size());
}

struct Channel {
  double gain = 1.0;
  double phase_rad = 0.0;
  double frequency_offset_hz = 0.0;
  double frequency_rate_hz_per_second = 0.0;
  double fade_depth_db = 0.0;
  double fade_rate_hz = 0.0;
  double snr_db = std::numeric_limits<double>::infinity();
  double echo_delay_ms = 0.0;
  double echo_gain = 0.0;
  double echo_frequency_offset_hz = 0.0;
};

// F.1487's spread is 2*sigma of the Gaussian POWER spectrum, not a carrier
// shift. Independent complex white sequences pass through a Gaussian FIR at
// 32*spread Hz, then are interpolated to the audio clock. Filling the history
// before the first output avoids a non-stationary startup fade.
class RayleighPath {
public:
  RayleighPath(double spread, double sample_rate, std::uint32_t seed)
      : noise_(seed), step_(32.0 * spread / sample_rate) {
    if (spread <= 0.0) throw std::invalid_argument("Watterson spread must be positive");
    double energy = 0;
    for (int i = -64; i <= 64; ++i) {
      const double value = std::exp(-std::pow(std::numbers::pi * i / 32.0, 2));
      weights_[i + 64] = static_cast<float>(value);
      energy += value * value;
      history_[i + 64] = noise_.next() / std::numbers::sqrt2_v<float>;
    }
    for (auto& w : weights_) w /= static_cast<float>(std::sqrt(energy));
    previous_ = next_control();
    next_ = next_control();
  }

  Complex next() {
    while (position_ >= 1.0) {
      position_ -= 1.0;
      previous_ = next_;
      next_ = next_control();
    }
    const auto value = previous_ + static_cast<float>(position_) * (next_ - previous_);
    position_ += step_;
    return value;
  }

private:
  Complex next_control() {
    head_ = (head_ + 1) % history_.size();
    history_[head_] = noise_.next() / std::numbers::sqrt2_v<float>;
    Complex sum{};
    for (std::size_t i = 0; i < weights_.size(); ++i) {
      sum += weights_[i] * history_[(head_ + i) % history_.size()];
    }
    return sum;
  }
  GaussianNoise noise_;
  std::array<float, 129> weights_{};
  std::array<Complex, 129> history_{};
  std::size_t head_ = 0;
  double step_, position_ = 0;
  Complex previous_{}, next_{};
};

struct Impairments {
  Channel legacy;
  bool watterson = false;
  double delay_spread_ms = 0;
  double doppler_spread_hz = 1;
  std::array<double, 2> path_gains_db{0, 0};
  bool normalize_path_power = true;
  bool pure_noise = false;
  double cw_hz = 0, cw_sir_db = std::numeric_limits<double>::infinity();
  double data_sir_db = std::numeric_limits<double>::infinity();
  double interferer_start_s = 0;
  double impulse_ms = 0, impulses_per_second = 0, impulse_above_noise_db = 0;
  double dropout_start_s = 0, dropout_duration_s = 0;
  double agc_step_db = 0, agc_start_s = 0.1, agc_attack_ms = 1, agc_decay_ms = 100;
  double clip_amplitude = std::numeric_limits<double>::infinity();
  bool soft_clip = false;
  double filter_bandwidth_hz = 0, group_delay_ripple_ms = 0;
  double notch_center_hz = 0, notch_width_hz = 0, notch_depth_db = 0;
  double clock_ppm = 0;
  std::int64_t sample_slip_index = -1;
  int sample_slip = 0;
  std::vector<Complex> noise_bed;
};

class AudioFilter {
public:
  AudioFilter(double fs, const Impairments& c) {
    if (c.filter_bandwidth_hz > 0 || c.notch_width_hz > 0) {
      taps_.resize(129);
      history_.resize(taps_.size());
      for (int j = -64; j <= 64; ++j) {
        const auto sinc = [](double x) { return x == 0 ? 1.0 : std::sin(std::numbers::pi*x)/(std::numbers::pi*x); };
        const double window = 0.54 + 0.46 * std::cos(std::numbers::pi * j / 64.0);
        Complex h = j == 0 ? Complex{1, 0} : Complex{};
        if (c.filter_bandwidth_hz > 0) {
          const double width = c.filter_bandwidth_hz / fs;
          h = {static_cast<float>(width * sinc(width*j) * window), 0};
        }
        if (c.notch_width_hz > 0) {
          const double width = c.notch_width_hz / fs;
          h -= static_cast<float>((1-std::pow(10.0,-c.notch_depth_db/20.0))*width*sinc(width*j)*window) *
               std::polar(1.0F, static_cast<float>(tau*c.notch_center_hz*j/fs));
        }
        taps_[j+64] = h;
      }
    }
    if (c.group_delay_ripple_ms > 0 && c.filter_bandwidth_hz > 0) {
      const double delay = c.group_delay_ripple_ms * fs / 1000.0;
      const float r = static_cast<float>((delay-1)/(delay+1));
      allpass_[0] = std::polar(r, static_cast<float>(std::numbers::pi*c.filter_bandwidth_hz/fs));
      allpass_[1] = std::conj(allpass_[0]);
      ripple_ = true;
    }
  }
  Complex push(Complex x) {
    if (!taps_.empty()) {
      history_[head_] = x;
      x = {};
      for (std::size_t k=0;k<taps_.size();++k) x += taps_[k]*history_[(head_+history_.size()-k)%history_.size()];
      head_ = (head_+1)%history_.size();
    }
    if (ripple_) {
      for (int k=0;k<2;++k) {
        const auto y = allpass_[k]*last_y_[k]+last_x_[k]-std::conj(allpass_[k])*x;
        last_x_[k]=x; last_y_[k]=y; x=y;
      }
    }
    return x;
  }
private:
  std::vector<Complex> taps_, history_;
  std::size_t head_ = 0;
  bool ripple_ = false;
  std::array<Complex, 2> allpass_{}, last_x_{}, last_y_{};
};

// One streaming implementation for both the original deterministic channel and
// the extended simulated channel. State and PRNG draws do not depend on chunks.
// Order: channel/noise, interferers, impulse, dropout, AGC, clipping, filtering,
// sample clock, residual carrier, then audio delivery (owned by the runner).
class SimulatedChannel {
public:
  SimulatedChannel(double fs, double signal_power, Impairments config, std::uint32_t seed)
      : fs_(fs), power_(signal_power), config_(config), noise_(seed), impulses_(seed ^ 0x192734AFU),
        path0_(config.doppler_spread_hz, fs, seed ^ 0x638AD923U),
        path1_(config.doppler_spread_hz, fs, seed ^ 0xC94F216BU), filter_(fs, config),
        delay_(static_cast<std::size_t>(std::llround((config.watterson ? config.delay_spread_ms :
                                                   config.legacy.echo_delay_ms)*fs/1000.0))),
        delayed_(delay_+1), sigma_(static_cast<float>(std::sqrt(signal_power*
            std::pow(10.0,-config.legacy.snr_db/10.0)/2.0))) {
    for (int k=0;k<2;++k) gains_[k]=static_cast<float>(std::pow(10.0, config.path_gains_db[k]/20.0));
    if (config.normalize_path_power) {
      const auto total = std::hypot(gains_[0],gains_[1]);
      for (auto& g:gains_) g/=total;
    }
    if(!config_.noise_bed.empty()) {
      const auto bed_power=mean_power(config_.noise_bed);
      if(!(bed_power>0) || !std::isfinite(bed_power))throw std::invalid_argument("recorded noise must have finite positive power");
      const auto scale=static_cast<float>(std::sqrt(signal_power*std::pow(10.0,-config.legacy.snr_db/10.0)/bed_power));
      for(auto& sample:config_.noise_bed)sample*=scale;
    }
    if (1.0+config.clock_ppm*1e-6 <= 0) throw std::invalid_argument("invalid sample clock ratio");
  }

  void process(std::span<const Complex> input, std::vector<Complex>& output,
               std::span<const Complex> interferer = {}) {
    output.clear();
    for (std::size_t j=0;j<input.size();++j,++index_) {
      const double t = static_cast<double>(index_)/fs_;
      const auto& c=config_;
      const auto& old=c.legacy;
      delayed_[index_%delayed_.size()] = input[j];
      const auto echo = index_ >= delay_ ? delayed_[(index_-delay_)%delayed_.size()] : Complex{};
      Complex value{};
      if (c.watterson) {
        value = gains_[0]*path0_.next()*input[j]+gains_[1]*path1_.next()*echo;
      } else {
        const double fade = old.fade_depth_db!=0 ? old.fade_depth_db*(1-std::cos(tau*old.fade_rate_hz*t))/2 : 0;
        value = input[j]*static_cast<float>(old.gain*(fade!=0?std::pow(10.0,-fade/20.0):1.0));
        if(old.echo_gain!=0)value += echo*std::polar(static_cast<float>(old.echo_gain),static_cast<float>(tau*old.echo_frequency_offset_hz*t));
      }
      if (c.pure_noise) value={};
      // Preserve the original regression channel's noise draw/order. Legacy
      // phase is applied before AWGN; new residual offset is set separately.
      if(old.phase_rad!=0 || old.frequency_offset_hz!=0 || old.frequency_rate_hz_per_second!=0)
        value *= std::polar(1.0F, static_cast<float>(old.phase_rad + tau*(old.frequency_offset_hz*t +
                                         0.5*old.frequency_rate_hz_per_second*t*t)));
      const auto receiver_noise=[&]() {
        if(c.noise_bed.empty())return sigma_!=0 ? sigma_*noise_.next() : Complex{};
        if(index_>=c.noise_bed.size())throw std::runtime_error("recorded noise exhausted; duration cannot be silently looped or truncated");
        return c.noise_bed[index_];
      };
      value += receiver_noise();
      if (t>=c.interferer_start_s) {
        if(std::isfinite(c.cw_sir_db))value += std::polar(static_cast<float>(std::sqrt(power_)*std::pow(10.0,-c.cw_sir_db/20.0)),
                                                       static_cast<float>(std::remainder(tau*c.cw_hz*t,tau)));
        if (!interferer.empty()) value += interferer[j]*static_cast<float>(std::pow(10.0,-c.data_sir_db/20.0));
      }
      if (c.impulses_per_second>0 && std::fmod(t,1.0/c.impulses_per_second)<c.impulse_ms/1000.0)
        value += sigma_*static_cast<float>(std::pow(10.0,c.impulse_above_noise_db/20.0))*impulses_.next();
      if (t>=c.dropout_start_s && t<c.dropout_start_s+c.dropout_duration_s) value=receiver_noise();
      if (c.agc_step_db!=0 && t>=c.agc_start_s) {
        const double elapsed=t-c.agc_start_s;
        const double attack=c.agc_attack_ms/1000.0,hold=0.05,decay=c.agc_decay_ms/1000.0;
        const double envelope=elapsed<attack ? elapsed/attack :
                              elapsed<attack+hold ? 1.0 : std::max(0.0,1-(elapsed-attack-hold)/decay);
        value *= static_cast<float>(std::pow(10.0,c.agc_step_db*envelope/20.0));
      }
      const float amplitude=std::abs(value);
      if (std::isfinite(c.clip_amplitude) && amplitude>0) {
        const double clipped=c.soft_clip ? c.clip_amplitude*std::tanh(amplitude/c.clip_amplitude) :
                                          std::min<double>(amplitude,c.clip_amplitude);
        value *= static_cast<float>(clipped/amplitude);
      }
      value=filter_.push(value);
      // Linear fractional resampler; this interpolation and its response are
      // declared in every result. A zero-ppm stage is an exact identity.
      if (c.clock_ppm==0) emit(value,output);
      else {
        while (next_output_<=static_cast<double>(index_)) {
          const auto fraction=static_cast<float>(next_output_-static_cast<double>(index_)+1);
          emit(previous_+fraction*(value-previous_),output);
          next_output_+=1.0+c.clock_ppm*1e-6;
        }
      }
      previous_=value;
    }
  }

  double residual_offset_hz=0, residual_drift_hz_per_second=0;
private:
  void emit(Complex value,std::vector<Complex>& output) {
    const double t=static_cast<double>(output_index_)/fs_;
    if(residual_offset_hz!=0 || residual_drift_hz_per_second!=0)
      value*=std::polar(1.0F,static_cast<float>(std::remainder(tau*(residual_offset_hz*t+
                                              0.5*residual_drift_hz_per_second*t*t),tau)));
    if (static_cast<std::int64_t>(output_index_)!=config_.sample_slip_index || config_.sample_slip>=0) output.push_back(value);
    if (static_cast<std::int64_t>(output_index_)==config_.sample_slip_index && config_.sample_slip>0) output.push_back(value);
    ++output_index_;
  }
  double fs_,power_;
  Impairments config_;
  GaussianNoise noise_,impulses_;
  RayleighPath path0_,path1_;
  AudioFilter filter_;
  std::size_t delay_;
  std::vector<Complex> delayed_;
  float sigma_;
  std::array<float,2> gains_{};
  std::uint64_t index_=0,output_index_=0;
  double next_output_=0;
  Complex previous_{};
};

inline std::vector<Complex> through_channel(std::span<const Complex> input, double sample_rate_hz,
                                            double signal_power,const Channel& channel,std::uint32_t seed) {
  Impairments config;
  config.legacy=channel;
  SimulatedChannel simulator(sample_rate_hz,signal_power,config,seed);
  std::vector<Complex> output;
  simulator.process(input,output);
  return output;
}


} // namespace goblin_cannon::test
