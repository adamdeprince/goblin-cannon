#pragma once

#include <complex>
#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace goblin_cannon {

using Complex = std::complex<float>;

enum class Modulation {
  qpsk,
  psk8,
  qam16,
  qam64,
  qam256,
  qam1024,
  qci16,
  qci64,
  qci256,
  qci1024,
  bpsk,
};

inline constexpr std::size_t max_bits_per_symbol = 10;

enum class ConstellationProfile {
  mil_std_188_110c_wbhf,
  square_gray,
};

struct ModemConfig {
  double sample_rate_hz = 48000.0;
  double bandwidth_hz = 24000.0;
  std::optional<double> symbol_rate_hz = std::nullopt;
  double rrc_rolloff = 0.25;
  std::size_t filter_span_symbols = 8;
  Modulation modulation = Modulation::qam64;
  ConstellationProfile constellation_profile = ConstellationProfile::mil_std_188_110c_wbhf;
  float tx_gain = 0.65F;
  bool decoder_agc = true;
  std::uint8_t receiver_oversampling = 1;
  float symbol_confidence_threshold = 0.18F;
};

struct ModemInfo {
  double sample_rate_hz = 0.0;
  double bandwidth_hz = 0.0;
  double symbol_rate_hz = 0.0;
  double samples_per_symbol = 0.0;
  std::size_t bits_per_symbol = 0;
  std::size_t filter_span_symbols = 0;
  double nominal_filter_latency_symbols = 0.0;
  std::uint8_t receiver_oversampling = 1;
};

struct StreamResult {
  std::size_t consumed = 0;
  std::size_t produced = 0;
};

struct DecodeResult {
  std::size_t consumed_samples = 0;
  std::size_t produced_bits = 0;
};

struct DecodeSymbolsResult {
  std::size_t consumed_samples = 0;
  std::size_t produced_symbols = 0;
};

struct SoftBit {
  std::uint8_t value = 0;
  bool certain = true;
  float confidence = 1.0F;
};

struct Token {
  std::uint8_t value = 0;
  bool certain = true;
  float confidence = 1.0F;
};

struct SymbolDecision {
  std::uint32_t symbol = 0;
  float nearest_distance = 0.0F;
  float next_distance = 0.0F;
  float confidence = 1.0F;
};

std::string to_string(Modulation modulation);
std::size_t bits_per_symbol(Modulation modulation);
double derived_symbol_rate_hz(const ModemConfig& config);
ModemInfo describe(const ModemConfig& config);
void validate(const ModemConfig& config);

class Constellation {
public:
  explicit Constellation(Modulation modulation,
                         ConstellationProfile profile = ConstellationProfile::mil_std_188_110c_wbhf);

  [[nodiscard]] Modulation modulation() const noexcept { return modulation_; }
  [[nodiscard]] std::size_t bits_per_symbol() const noexcept { return bits_per_symbol_; }
  [[nodiscard]] std::size_t size() const noexcept { return points_.size(); }
  [[nodiscard]] std::span<const Complex> points() const noexcept { return points_; }

  [[nodiscard]] Complex map_bits(std::span<const std::uint8_t> bits) const;
  [[nodiscard]] Complex map_symbol(std::uint32_t symbol) const;
  [[nodiscard]] std::uint32_t bits_to_symbol(std::span<const std::uint8_t> bits) const;
  [[nodiscard]] std::uint32_t nearest_symbol(Complex sample) const;
  [[nodiscard]] SymbolDecision decide(Complex sample) const;
  void symbol_to_bits(std::uint32_t symbol, std::span<std::uint8_t> out) const;

private:
  Modulation modulation_;
  std::size_t bits_per_symbol_;
  std::vector<Complex> points_;
  std::vector<float> i_;
  std::vector<float> q_;
};

class Encoder {
public:
  explicit Encoder(ModemConfig config = {});

  [[nodiscard]] const ModemConfig& config() const noexcept { return config_; }
  [[nodiscard]] const ModemInfo& info() const noexcept { return info_; }
  [[nodiscard]] std::size_t pending_bits() const noexcept { return bit_buffer_.size(); }
  [[nodiscard]] bool flushing() const noexcept { return flushing_; }

  StreamResult push_bits(std::span<const std::uint8_t> bits, std::span<Complex> out);
  StreamResult push_bytes(std::span<const std::uint8_t> bytes, std::span<Complex> out);
  StreamResult drain(std::span<Complex> out);
  void reset();

private:
  void append_bit(std::uint8_t bit);
  void append_symbol(Complex symbol);
  void begin_flush();
  std::size_t produce(std::span<Complex> out);
  [[nodiscard]] bool can_produce_next_sample() const;
  [[nodiscard]] Complex synthesize_sample(std::uint64_t sample_index) const;
  void prune_symbols(double symbol_time);

  ModemConfig config_;
  ModemInfo info_;
  Constellation constellation_;
  std::vector<std::uint8_t> bit_buffer_;
  std::vector<Complex> symbols_;
  // Amortized-compaction head: symbols_[i] holds the symbol at index
  // first_symbol_index_ + i - symbols_head_.
  std::size_t symbols_head_ = 0;
  std::int64_t first_symbol_index_ = 0;
  std::int64_t next_symbol_index_ = 0;
  std::uint64_t next_sample_index_ = 0;
  bool flushing_ = false;
  std::int64_t flush_last_symbol_index_ = -1;
  // Precomputed pulse-shape taps for integer samples_per_symbol. For each
  // phase (= sample_index % sps), synth_taps_[phase] holds taps for symbol
  // offsets d in [synth_phase_d_min_[phase], synth_phase_d_max_[phase]] where
  // d = k - q (q = sample_index / sps). Tap value = rrc((phase/sps - d), rolloff).
  std::vector<std::vector<float>> synth_taps_;
  std::vector<int> synth_phase_d_min_;
  std::vector<int> synth_phase_d_max_;
  int synth_sps_int_ = 0;
};

class Decoder {
public:
  explicit Decoder(ModemConfig config = {}, double timing_offset_symbols = 0.0);

  [[nodiscard]] const ModemConfig& config() const noexcept { return config_; }
  [[nodiscard]] const ModemInfo& info() const noexcept { return info_; }
  [[nodiscard]] float current_agc_gain() const noexcept { return agc_gain_; }
  [[nodiscard]] double timing_offset_symbols() const noexcept { return timing_offset_symbols_; }
  // Recover the audio sample clock. This does not rotate phase or track carrier
  // frequency. Enable before feeding samples; reset retains this setting.
  void set_sample_clock_recovery(bool enabled);
  [[nodiscard]] double recovered_clock_ppm() const noexcept { return clock_rate_ * 1.0e6; }

  DecodeResult push_samples(std::span<const Complex> samples, std::span<std::uint8_t> out_bits);
  DecodeResult push_samples_soft(std::span<const Complex> samples, std::span<SoftBit> out_bits);
  // Symbol-direct soft decode: emits SymbolDecision per symbol, skipping the
  // symbol→bits→symbol round-trip the streaming RF receiver used to do.
  DecodeSymbolsResult push_samples_symbols(std::span<const Complex> samples,
                                            std::span<SymbolDecision> out_symbols);
  // Matched-filter output before AGC or decisions, for RF carrier recovery and
  // equalization. Shares streaming state with the other decode entry points.
  DecodeSymbolsResult push_samples_matched(std::span<const Complex> samples,
                                          std::span<Complex> out_symbols,
                                          std::span<Complex> half_symbols = {});
  void reset();

private:
  [[nodiscard]] bool can_decode_next_symbol() const;
  [[nodiscard]] Complex matched_filter_symbol(std::int64_t symbol_index) const;
  [[nodiscard]] Complex matched_filter_at(double symbol_time) const;
  void advance_symbol(Complex matched);
  void prepare_fractional_filter();
  void append_sample(Complex sample);
  void prune_samples(std::int64_t decoded_symbol);
  Complex apply_agc(Complex sample, std::uint32_t decided_symbol);

  ModemConfig config_;
  ModemInfo info_;
  Constellation constellation_;
  double timing_offset_symbols_ = 0.0;
  bool sample_clock_recovery_ = false;
  double next_symbol_time_ = 0.0;
  double previous_symbol_time_ = 0.0;
  double clock_rate_ = 0.0;
  float timing_power_ = 1.0F;
  Complex previous_matched_{};
  std::vector<float> fractional_rrc_;
  std::vector<Complex> samples_;
  // Amortized-compaction head: samples_[i] holds the sample at index
  // first_sample_index_ + i - samples_head_. prune_samples advances both
  // first_sample_index_ and samples_head_; compaction memmove only fires
  // when samples_head_ exceeds half of samples_.size().
  std::size_t samples_head_ = 0;
  std::int64_t first_sample_index_ = 0;
  std::uint64_t next_sample_index_ = 0;
  std::int64_t next_symbol_index_ = 0;
  float agc_gain_ = 1.0F;
  float agc_power_ = 1.0F;
  float target_symbol_power_ = 1.0F;
  // Precomputed RRC matched-filter taps for integer samples_per_symbol.
  // taps_[i] applies to the sample at offset (taps_s_min_ + i) from
  // sps_int_*symbol_index. Empty if the integer-SPS fast path is unavailable.
  std::vector<float> taps_;
  int sps_int_ = 0;
  int taps_s_min_ = 0;
  int taps_s_max_ = 0;
  float sps_inv_ = 0.0F;
};

class BytePacker {
public:
  [[nodiscard]] std::size_t push_bits(std::span<const std::uint8_t> bits, std::span<std::uint8_t> out);
  void reset() noexcept;

private:
  std::uint8_t current_ = 0;
  std::uint8_t filled_ = 0;
  std::uint8_t pending_ = 0;
  bool has_pending_ = false;
};

struct CarrierDetectorConfig {
  float open_threshold = 0.002F;
  float close_threshold = 0.0005F;
  std::size_t attack_samples = 4;
  std::size_t release_samples = 384;
  std::size_t preroll_samples = 128;
};

struct FrameConfig {
  ModemConfig modem = {};
  CarrierDetectorConfig carrier = {};
  std::size_t preamble_bytes = 32;
  std::uint8_t sync_max_bit_errors = 1;
  std::uint32_t max_payload_bytes = 1U << 20U;
  bool continuous_stream = false;
};

enum class FrameStatus {
  idle,
  transmitting,
  complete,
  carrier_detected,
  receiving,
  frame_complete,
  protocol_error,
};

struct FrameEncodeResult {
  std::size_t consumed_payload_bytes = 0;
  std::size_t produced_samples = 0;
  FrameStatus status = FrameStatus::idle;
};

struct FrameDecodeResult {
  std::size_t consumed_samples = 0;
  std::size_t produced_payload_bytes = 0;
  FrameStatus status = FrameStatus::idle;
  bool carrier_present = false;
  bool locked = false;
};

class FrameEncoder {
public:
  explicit FrameEncoder(FrameConfig config = {});

  [[nodiscard]] const FrameConfig& config() const noexcept { return config_; }
  [[nodiscard]] bool active() const noexcept;
  [[nodiscard]] std::uint32_t remaining_payload_bytes() const noexcept;

  void start_frame(std::uint32_t payload_bytes);
  void start_stream();
  FrameEncodeResult push_payload(std::span<const std::uint8_t> payload, std::span<Complex> out);
  FrameEncodeResult push_tokens(std::span<const std::uint8_t> tokens, std::span<Complex> out);
  FrameEncodeResult drain(std::span<Complex> out);
  void reset();

private:
  enum class TxState {
    idle,
    control,
    payload,
    draining,
    complete,
  };

  FrameEncodeResult pump(std::span<const std::uint8_t> payload, std::span<Complex> out);
  void queue_header(std::optional<std::uint32_t> payload_bytes);

  FrameConfig config_;
  Encoder encoder_;
  TxState state_ = TxState::idle;
  bool continuous_stream_ = false;
  bool closing_stream_ = false;
  std::vector<std::uint8_t> control_;
  std::size_t control_offset_ = 0;
  std::uint32_t payload_expected_ = 0;
  std::uint32_t payload_consumed_ = 0;
};

class FrameDecoder {
public:
  explicit FrameDecoder(FrameConfig config = {});

  [[nodiscard]] const FrameConfig& config() const noexcept { return config_; }
  [[nodiscard]] bool carrier_present() const noexcept { return carrier_present_; }

  FrameDecodeResult push_samples(std::span<const Complex> samples, std::span<std::uint8_t> out_payload);
  FrameDecodeResult push_samples(std::span<const Complex> samples, std::span<Token> out_tokens);
  void reset();

private:
  enum class RxState {
    searching_sync,
    length,
    payload,
  };

  void reset_frame_parser();
  void reset_branch_parser(std::size_t branch);
  bool push_sample_to_branches(Complex sample,
                               std::span<Token> out_payload,
                               FrameDecodeResult& result,
                               std::span<SoftBit> bit_buffer);
  bool push_branch_bit(std::size_t branch,
                       SoftBit bit,
                       std::span<Token> out_payload,
                       FrameDecodeResult& result);
  bool push_branch_byte(std::size_t branch,
                        std::uint8_t byte,
                        bool certain,
                        float confidence,
                        std::span<Token> out_payload,
                        FrameDecodeResult& result);
  bool emit_payload_byte(std::size_t branch,
                         std::uint8_t byte,
                         bool certain,
                         float confidence,
                         std::span<Token> out_payload,
                         FrameDecodeResult& result);
  bool flush_pending_payload(std::size_t branch, std::span<Token> out_payload, FrameDecodeResult& result);
  void update_carrier(Complex sample);

  struct TimingBranch {
    TimingBranch(ModemConfig modem, double timing_offset_symbols);

    Decoder decoder;
    RxState state = RxState::searching_sync;
    std::uint32_t sync_shift = 0;
    std::uint8_t sync_bits = 0;
    std::uint8_t current_byte = 0;
    std::uint8_t current_byte_bits = 0;
    bool current_byte_certain = true;
    float current_byte_confidence = 1.0F;
    std::uint32_t length = 0;
    std::uint32_t length_shift = 0;
    std::uint32_t payload_received = 0;
    std::uint8_t pending_payload = 0;
    bool pending_payload_certain = true;
    float pending_payload_confidence = 1.0F;
    bool has_pending_payload = false;
  };

  FrameConfig config_;
  std::vector<TimingBranch> branches_;
  std::size_t locked_branch_ = static_cast<std::size_t>(-1);
  bool carrier_present_ = false;
  std::size_t attack_count_ = 0;
  std::size_t release_count_ = 0;
  float energy_ = 0.0F;
  std::vector<Complex> preroll_;
  std::size_t preroll_write_ = 0;
  bool preroll_full_ = false;
};

} // namespace goblin_cannon
