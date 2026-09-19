#pragma once

#include "goblin_cannon/modem.hpp"

#include <complex>
#include <array>
#include <cstddef>
#include <cstdint>
#include <memory>
#include <optional>
#include <span>
#include <vector>

namespace goblin_cannon {

namespace detail { class AudioWaveformEncoder; class AudioWaveformReceiver; }

enum class DifferentialMapping : std::uint8_t { none, dbpsk, dqpsk, pi4_dqpsk };
enum class AudioWaveform : std::uint8_t { single_carrier, fsk4, fsk8, bpsk_frequency_diversity };

enum class RfStreamState {
  search,
  acquired,
  training,
  header,
  locked,
  lock_lost,
  protocol_error,
  recovering,
};

struct AcquisitionResult {
  bool found = false;
  std::size_t sample_index = 0;
  float peak_metric = 0.0F;
  float sidelobe_metric = 0.0F;
  float confidence = 0.0F;
};

struct RfSyncEstimate {
  double symbol_timing_offset_samples = 0.0;
  double carrier_frequency_offset_hz = 0.0; // Mean carrier offset, not Doppler spread.
  float carrier_phase_rad = 0.0F;
  // Forward complex channel gain at the start of the acquisition preamble.
  Complex channel = {1.0F, 0.0F};
  float training_evm = 0.0F;
  double sample_clock_error_ppm = 0.0;
};

struct RfStreamHeader {
  std::uint32_t schedule_epoch_low = 0;
  std::uint64_t frame_counter_start = 0;
  std::uint32_t symbols_per_frame = 0;
  std::uint32_t pilot_interval_symbols = 0;
  Modulation modulation = Modulation::qam64;
  Modulation header_modulation = Modulation::qpsk;
  DifferentialMapping differential_mapping = DifferentialMapping::none;
  std::uint32_t crc32 = 0;
};

struct RfStreamConfig {
  ModemConfig modem = {};
  std::uint64_t expected_schedule_epoch = 0;
  std::vector<std::uint32_t> acquisition_sequence;
  std::vector<std::uint32_t> equalizer_training_sequence;
  std::vector<std::uint32_t> pilot_sequence;
  std::uint32_t symbols_per_frame = 1024;
  std::uint32_t pilot_interval_symbols = 128;
  std::uint8_t header_repetition = 3;
  // Configured over fiber at both ends. Compact headers carry only epoch,
  // absolute frame counter and CRC, with rate-1/2 FEC and embedded training.
  bool compact_header = false;
  // Fiber configured; acquisition, equalizer training and embedded header
  // probes stay QPSK. Only header data symbols switch to BPSK.
  Modulation header_modulation = Modulation::qpsk;
  // Payload differential mapping; pilots remain absolute phase references.
  // DBPSK requires BPSK; DQPSK and pi/4-DQPSK require QPSK payload bits.
  DifferentialMapping differential_mapping = DifferentialMapping::none;
  // Zero retains continuous legacy framing. Nonzero inserts a fresh preamble
  // and training block after this many payload frames, without restarting FEC
  // or the encryption keystream.
  std::uint32_t recovery_interval_frames = 0;
  // Minimum normalized correlation and relative peak prominence for acquisition.
  float acquisition_confidence_threshold = 0.35F;
  float pilot_confidence_threshold = 0.20F;
  float symbol_confidence_threshold = 0.18F;
  std::size_t acquisition_sidelobe_guard_samples = 32;
  // Legacy library option. The recorded acceptance profile sets this false:
  // the radio owns carrier frequency offset correction; the equalizer tracks
  // delay spread, Doppler spread, fading, phase rotation and multipath.
  bool carrier_correction = true;
  bool adaptive_equalization = true;
  // Alternative to NLMS. Configure over the control path; keep NLMS as the
  // legacy carrier-loop companion and enable sparse RLS for audio-only links.
  bool recursive_equalization = false;
  bool sample_clock_recovery = true;
  // Symbol-spaced equalizer: [1,512] feedforward and [0,512] feedback.
  // Supply matching counts over the control link: startup pilots span the
  // greater of filter_span_symbols and the sum of these two tap counts.
  std::uint32_t equalizer_feedforward_taps = 3;
  std::uint32_t equalizer_feedback_taps = 4;
  // Lookahead expressed as a decision delay in the causal FIR. It allows a
  // stronger delayed path without forcing an unstable minimum-phase inverse.
  // Adds this many symbols of modem delay; must match at both ends.
  std::uint32_t equalizer_delay_symbols = 0;
  // Preserve the configured feedforward span, sampling it at T/2 (2*N-1 taps).
  bool fractionally_spaced_equalization = false;
  // Revisit sparse RLS support after this many reliable updates; zero freezes
  // the initial selection. Inactive taps receive shadow NLMS updates.
  std::uint32_t equalizer_reselect_interval = 0;
  // Fiber-selected recovery experiment: reuse learned echo support, assess
  // recent training residuals, and use varied known payload startup symbols.
  bool warm_recovery = false;
  // Age RLS uncertainty in symbol time, including unreliable observations.
  bool elapsed_time_tracking = false;
  // Conventional per-bit Euclidean metrics; receiver-only, no wire change.
  bool soft_demapping = false;
  AudioWaveform waveform = AudioWaveform::single_carrier;
  // Noncoherent orthogonal tones; repeat the tone during a multipath guard,
  // then integrate for fsk_useful_ms. Acquisition and headers also use FSK.
  double fsk_useful_ms = 4.0;
  double fsk_guard_ms = 8.0;
  double diversity_wait_ms = 1.0; // Receiver combining wait; charged as buffering.
  // Fiber-configured occupied RRC bandwidth per copy and center separation.
  // Zero retains the original half-band width / half-band separation.
  double diversity_branch_bandwidth_hz = 0.0;
  double diversity_separation_hz = 0.0;
  // 1 = lower copy, 2 = upper copy, 3 = both. Single-copy controls retain
  // the same symbol rate and use the entire configured transmit power.
  std::uint32_t diversity_branch_mask = 3;
};

struct RfStreamEncodeResult {
  std::size_t consumed_symbols = 0;
  std::size_t produced_samples = 0;
  RfStreamState state = RfStreamState::search;
};

struct RfStreamSymbol {
  std::uint32_t value = 0;
  std::uint8_t bits_per_symbol = 0;
  std::uint64_t frame_counter = 0;
  std::uint32_t frame_symbol_offset = 0;
  bool certain = true;
  float confidence = 1.0F;
  bool has_soft_bits = false;
  std::array<SoftBit, max_bits_per_symbol> soft_bits{};
};

struct RfStreamReceiveResult {
  std::size_t consumed_samples = 0;
  std::size_t produced_symbols = 0;
  RfStreamState state = RfStreamState::search;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  AcquisitionResult acquisition = {};
  RfSyncEstimate sync = {};
  std::optional<RfStreamHeader> header = std::nullopt;
};

std::vector<std::uint32_t> make_default_qpsk_sequence(std::size_t symbols, std::uint32_t seed = 0x13579BDFU);

void validate(const RfStreamConfig& config);
[[nodiscard]] double rf_symbol_rate_hz(const RfStreamConfig& config);
std::uint32_t stream_header_crc32(const RfStreamHeader& header);

class AcquisitionCorrelator {
public:
  explicit AcquisitionCorrelator(RfStreamConfig config);
  ~AcquisitionCorrelator();

  AcquisitionCorrelator(const AcquisitionCorrelator&) = delete;
  AcquisitionCorrelator& operator=(const AcquisitionCorrelator&) = delete;
  AcquisitionCorrelator(AcquisitionCorrelator&&) noexcept;
  AcquisitionCorrelator& operator=(AcquisitionCorrelator&&) noexcept;

  [[nodiscard]] AcquisitionResult scan(std::span<const Complex> samples) const;
  [[nodiscard]] std::span<const Complex> reference_samples() const noexcept;

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

class RfStreamEncoder {
public:
  explicit RfStreamEncoder(RfStreamConfig config);
  ~RfStreamEncoder();

  RfStreamEncoder(const RfStreamEncoder&) = delete;
  RfStreamEncoder& operator=(const RfStreamEncoder&) = delete;
  RfStreamEncoder(RfStreamEncoder&&) noexcept;
  RfStreamEncoder& operator=(RfStreamEncoder&&) noexcept;

  [[nodiscard]] const RfStreamConfig& config() const noexcept;
  [[nodiscard]] bool active() const noexcept;
  [[nodiscard]] RfStreamState state() const noexcept;
  [[nodiscard]] RfStreamHeader current_header() const noexcept;

  void start_epoch(std::uint64_t frame_counter_start);
  RfStreamEncodeResult push_symbols(std::span<const std::uint32_t> symbols, std::span<Complex> out);
  RfStreamEncodeResult drain(std::span<Complex> out);
  void reset();

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<detail::AudioWaveformEncoder> audio_;
};

class RfStreamReceiver {
public:
  explicit RfStreamReceiver(RfStreamConfig config);
  ~RfStreamReceiver();

  RfStreamReceiver(const RfStreamReceiver&) = delete;
  RfStreamReceiver& operator=(const RfStreamReceiver&) = delete;
  RfStreamReceiver(RfStreamReceiver&&) noexcept;
  RfStreamReceiver& operator=(RfStreamReceiver&&) noexcept;

  [[nodiscard]] const RfStreamConfig& config() const noexcept;
  [[nodiscard]] RfStreamState state() const noexcept;
  [[nodiscard]] std::optional<RfStreamHeader> header() const noexcept;
  [[nodiscard]] RfSyncEstimate sync_estimate() const noexcept;

  RfStreamReceiveResult push_samples(std::span<const Complex> samples, std::span<RfStreamSymbol> out);
  void reset();

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
  std::unique_ptr<detail::AudioWaveformReceiver> audio_;
};

} // namespace goblin_cannon
