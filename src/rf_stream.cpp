#include "goblin_cannon/rf_stream.hpp"
#include "audio_waveform.hpp"

#include "rf_equalizer.hpp"
#include "differential_psk.hpp"
#include "goblin_cannon/convolutional.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstring>
#include <limits>
#include <numbers>
#include <stdexcept>

namespace goblin_cannon {

namespace {

constexpr std::uint32_t header_magic = 0x57424846U; // WBHF
constexpr std::size_t serialized_header_bytes = 32;
constexpr float equalizer_step = 0.4F;
constexpr float tracking_confidence = 0.4F;
std::uint32_t startup_pilot_symbols(const RfStreamConfig& config) {
  return static_cast<std::uint32_t>(std::max<std::size_t>(config.modem.filter_span_symbols,
      config.equalizer_feedforward_taps + config.equalizer_feedback_taps));
}

std::uint32_t modulation_id(Modulation modulation) {
  switch (modulation) {
  case Modulation::qpsk:
    return 0;
  case Modulation::psk8:
    return 1;
  case Modulation::qam16:
    return 2;
  case Modulation::qam64:
    return 3;
  case Modulation::qam256:
    return 4;
  case Modulation::qam1024:
    return 5;
  case Modulation::qci16:
    return 6;
  case Modulation::qci64:
    return 7;
  case Modulation::qci256:
    return 8;
  case Modulation::qci1024:
    return 9;
  case Modulation::bpsk:
    return 10;
  }
  return 0;
}

Modulation modulation_from_id(std::uint32_t id) {
  switch (id) {
  case 0:
    return Modulation::qpsk;
  case 1:
    return Modulation::psk8;
  case 2:
    return Modulation::qam16;
  case 3:
    return Modulation::qam64;
  case 4:
    return Modulation::qam256;
  case 5:
    return Modulation::qam1024;
  case 6:
    return Modulation::qci16;
  case 7:
    return Modulation::qci64;
  case 8:
    return Modulation::qci256;
  case 9:
    return Modulation::qci1024;
  case 10:
    return Modulation::bpsk;
  default:
    throw std::invalid_argument("unknown modulation id in RF stream header");
  }
}

void append_u32_be(std::array<std::uint8_t, serialized_header_bytes>& out, std::size_t& offset, std::uint32_t value) {
  out[offset++] = static_cast<std::uint8_t>((value >> 24U) & 0xFFU);
  out[offset++] = static_cast<std::uint8_t>((value >> 16U) & 0xFFU);
  out[offset++] = static_cast<std::uint8_t>((value >> 8U) & 0xFFU);
  out[offset++] = static_cast<std::uint8_t>(value & 0xFFU);
}

void append_u64_be(std::array<std::uint8_t, serialized_header_bytes>& out, std::size_t& offset, std::uint64_t value) {
  for (int shift = 56; shift >= 0; shift -= 8) {
    out[offset++] = static_cast<std::uint8_t>((value >> static_cast<unsigned>(shift)) & 0xFFU);
  }
}

std::uint32_t read_u32_be(std::span<const std::uint8_t> bytes, std::size_t offset) {
  return (static_cast<std::uint32_t>(bytes[offset]) << 24U) |
         (static_cast<std::uint32_t>(bytes[offset + 1U]) << 16U) |
         (static_cast<std::uint32_t>(bytes[offset + 2U]) << 8U) |
         static_cast<std::uint32_t>(bytes[offset + 3U]);
}

std::uint64_t read_u64_be(std::span<const std::uint8_t> bytes, std::size_t offset) {
  std::uint64_t value = 0;
  for (std::size_t i = 0; i < 8; ++i) {
    value = (value << 8U) | bytes[offset + i];
  }
  return value;
}

std::uint32_t crc32_update(std::uint32_t crc, std::span<const std::uint8_t> bytes) {
  crc = ~crc;
  for (const auto byte : bytes) {
    crc ^= byte;
    for (int bit = 0; bit < 8; ++bit) {
      const std::uint32_t mask = 0U - (crc & 1U);
      crc = (crc >> 1U) ^ (0xEDB88320U & mask);
    }
  }
  return ~crc;
}

std::array<std::uint8_t, serialized_header_bytes> serialize_header_without_crc(RfStreamHeader header) {
  std::array<std::uint8_t, serialized_header_bytes> bytes{};
  std::size_t offset = 0;
  append_u32_be(bytes, offset, header_magic);
  append_u32_be(bytes, offset, header.schedule_epoch_low);
  append_u64_be(bytes, offset, header.frame_counter_start);
  append_u32_be(bytes, offset, header.symbols_per_frame);
  append_u32_be(bytes, offset, header.pilot_interval_symbols);
  bytes[offset++] = static_cast<std::uint8_t>(modulation_id(header.modulation));
  bytes[offset++] = static_cast<std::uint8_t>(modulation_id(header.header_modulation));
  bytes[offset++] = static_cast<std::uint8_t>(header.differential_mapping);
  bytes[offset++] = 0;
  return bytes;
}

std::array<std::uint8_t, serialized_header_bytes> serialize_header(RfStreamHeader header) {
  auto bytes = serialize_header_without_crc(header);
  const auto crc = crc32_update(0, std::span<const std::uint8_t>(bytes.data(), serialized_header_bytes - 4U));
  std::size_t offset = serialized_header_bytes - 4U;
  append_u32_be(bytes, offset, crc);
  return bytes;
}

std::optional<RfStreamHeader> parse_header(std::span<const std::uint8_t> bytes) {
  if (bytes.size() != serialized_header_bytes || read_u32_be(bytes, 0) != header_magic) {
    return std::nullopt;
  }
  const auto expected_crc = crc32_update(0, bytes.first(serialized_header_bytes - 4U));
  const auto observed_crc = read_u32_be(bytes, serialized_header_bytes - 4U);
  if (expected_crc != observed_crc) {
    return std::nullopt;
  }

  RfStreamHeader header;
  header.schedule_epoch_low = read_u32_be(bytes, 4);
  header.frame_counter_start = read_u64_be(bytes, 8);
  header.symbols_per_frame = read_u32_be(bytes, 16);
  header.pilot_interval_symbols = read_u32_be(bytes, 20);
  header.modulation = modulation_from_id(bytes[24]);
  // The two formerly reserved zero bytes retain legacy QPSK/coherent defaults.
  if (bytes[25] != 0 && bytes[25] != 10) return std::nullopt;
  if (bytes[26] > static_cast<std::uint8_t>(DifferentialMapping::pi4_dqpsk)) return std::nullopt;
  header.header_modulation = modulation_from_id(bytes[25]);
  header.differential_mapping = static_cast<DifferentialMapping>(bytes[26]);
  header.crc32 = observed_crc;
  return header;
}

std::vector<std::uint8_t> bytes_to_repeated_bits(std::span<const std::uint8_t> bytes, std::uint8_t repetition) {
  std::vector<std::uint8_t> bits;
  bits.reserve(bytes.size() * 8U * repetition);
  for (const auto byte : bytes) {
    for (int bit = 7; bit >= 0; --bit) {
      const auto value = static_cast<std::uint8_t>((byte >> bit) & 1U);
      for (std::uint8_t r = 0; r < repetition; ++r) {
        bits.push_back(value);
      }
    }
  }
  return bits;
}

std::vector<std::uint8_t> qpsk_symbols_to_bits(std::span<const std::uint32_t> symbols) {
  Constellation qpsk(Modulation::qpsk);
  std::array<std::uint8_t, 2> symbol_bits{};
  std::vector<std::uint8_t> bits;
  bits.reserve(symbols.size() * 2U);
  for (const auto symbol : symbols) {
    qpsk.symbol_to_bits(symbol, symbol_bits);
    bits.insert(bits.end(), symbol_bits.begin(), symbol_bits.end());
  }
  return bits;
}

std::vector<Complex> encode_bits(ModemConfig config, Modulation modulation, std::span<const std::uint8_t> bits) {
  config.modulation = modulation;
  config.receiver_oversampling = 1;
  Encoder encoder(config);
  std::vector<Complex> samples;
  std::array<Complex, 512> chunk{};
  const auto pushed = encoder.push_bits(bits, chunk);
  if (pushed.consumed != bits.size()) {
    throw std::logic_error("encoder did not consume all RF stream control bits");
  }
  samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(pushed.produced));
  for (;;) {
    const auto drained = encoder.drain(chunk);
    samples.insert(samples.end(), chunk.begin(), chunk.begin() + static_cast<std::ptrdiff_t>(drained.produced));
    if (drained.produced == 0) {
      break;
    }
  }
  return samples;
}

std::vector<Complex> encode_qpsk_symbols(ModemConfig config, std::span<const std::uint32_t> symbols) {
  const auto bits = qpsk_symbols_to_bits(symbols);
  return encode_bits(std::move(config), Modulation::qpsk, bits);
}

std::vector<Complex> build_reference_preamble(const RfStreamConfig& config) {
  return encode_qpsk_symbols(config.modem, config.acquisition_sequence);
}

constexpr std::size_t compact_header_bytes = 16;
constexpr std::size_t compact_input_bits = compact_header_bytes * 8U + 6U;
constexpr std::size_t header_probe_interval = 16;
constexpr std::size_t header_probe_length = 4;

std::vector<std::uint8_t> header_wire_bits(const RfStreamConfig& config, const RfStreamHeader& header) {
  const auto width = bits_per_symbol(config.header_modulation);
  std::vector<std::uint8_t> coded;
  if (!config.compact_header) coded = bytes_to_repeated_bits(serialize_header(header), config.header_repetition);
  // Mode, pilot cadence and frame size already come from the control link.
  // The CRC binds them too, so mismatched configuration cannot validate.
  std::array<std::uint8_t, serialized_header_bytes> storage{};
  std::size_t offset = 0;
  append_u32_be(storage, offset, header.schedule_epoch_low);
  append_u64_be(storage, offset, header.frame_counter_start);
  append_u32_be(storage, offset, stream_header_crc32(header));
  if (config.compact_header) {
    PuncturedConvolutionalEncoder encoder;
    coded = encoder.push_bytes(std::span(storage).first(compact_header_bytes));
    for (std::size_t i = 0; i < 6; ++i) encoder.push_bit_append(0, coded);
  }
  std::vector<std::uint8_t> bits;
  Constellation qpsk(Modulation::qpsk);
  std::array<std::uint8_t, 2> probe{};
  for (std::size_t i = 0; i < coded.size()/width; ++i) {
    if (config.compact_header && i != 0 && i % header_probe_interval == 0) {
      for (std::size_t j = 0; j < header_probe_length; ++j) {
        qpsk.symbol_to_bits(config.equalizer_training_sequence[(i+j) % config.equalizer_training_sequence.size()], probe);
        bits.insert(bits.end(), probe.begin(), probe.end());
      }
    }
    if (width == 1) {
      // Use QPSK's +1/-1 points in the same pulse-shaping stream as training.
      bits.push_back(0); bits.push_back(coded[i]);
    } else {
      bits.insert(bits.end(), coded.begin()+static_cast<std::ptrdiff_t>(2*i), coded.begin()+static_cast<std::ptrdiff_t>(2*i+2));
    }
  }
  return bits;
}

std::vector<Complex> build_training_header_samples(const RfStreamConfig& config, const RfStreamHeader& header) {
  auto bits = qpsk_symbols_to_bits(config.equalizer_training_sequence);
  auto repeated = header_wire_bits(config, header);
  bits.insert(bits.end(), repeated.begin(), repeated.end());
  return encode_bits(config.modem, Modulation::qpsk, bits);
}

std::size_t expected_training_header_bits(const RfStreamConfig& config) {
  const auto data_symbols = (config.compact_header ? 2U*compact_input_bits
      : serialized_header_bytes*8U*config.header_repetition) / bits_per_symbol(config.header_modulation);
  const auto probes = config.compact_header ? (data_symbols-1U)/header_probe_interval*header_probe_length : 0U;
  return 2U * (config.equalizer_training_sequence.size() + data_symbols + probes);
}

std::vector<std::uint8_t> majority_header_bytes(std::span<const std::uint8_t> repeated_bits,
                                                std::uint8_t repetition) {
  std::vector<std::uint8_t> header_bits;
  header_bits.reserve(serialized_header_bytes * 8U);
  for (std::size_t bit = 0; bit < serialized_header_bytes * 8U; ++bit) {
    std::size_t ones = 0;
    for (std::uint8_t r = 0; r < repetition; ++r) {
      ones += repeated_bits[bit * repetition + r] & 1U;
    }
    header_bits.push_back(static_cast<std::uint8_t>(ones > repetition / 2U));
  }

  std::vector<std::uint8_t> bytes(serialized_header_bytes);
  for (std::size_t i = 0; i < serialized_header_bytes; ++i) {
    std::uint8_t byte = 0;
    for (std::size_t bit = 0; bit < 8; ++bit) {
      byte = static_cast<std::uint8_t>((byte << 1U) | header_bits[i * 8U + bit]);
    }
    bytes[i] = byte;
  }
  return bytes;
}

float normalized_metric(Complex corr, float signal_energy, float reference_energy) {
  const float denom = std::max(signal_energy * reference_energy, 1.0e-12F);
  return std::norm(corr) / denom;
}

Complex correlation_at(std::span<const Complex> samples, std::span<const Complex> reference, std::size_t offset) {
  Complex corr{0.0F, 0.0F};
  for (std::size_t i = 0; i < reference.size(); ++i) {
    corr += samples[offset + i] * std::conj(reference[i]);
  }
  return corr;
}

float window_energy(std::span<const Complex> samples, std::size_t offset, std::size_t length) {
  float energy = 0.0F;
  for (std::size_t i = 0; i < length; ++i) {
    energy += std::norm(samples[offset + i]);
  }
  return energy;
}

void erase_prefix(std::vector<Complex>& buffer, std::size_t count, std::uint64_t& first_sample_index) {
  count = std::min(count, buffer.size());
  buffer.erase(buffer.begin(), buffer.begin() + static_cast<std::ptrdiff_t>(count));
  first_sample_index += count;
}

bool symbol_vector_valid(std::span<const std::uint32_t> symbols, std::size_t order) {
  return std::all_of(symbols.begin(), symbols.end(), [order](std::uint32_t symbol) { return symbol < order; });
}

} // namespace

std::vector<std::uint32_t> make_default_qpsk_sequence(std::size_t symbols, std::uint32_t seed) {
  std::vector<std::uint32_t> sequence;
  sequence.reserve(symbols);
  std::uint32_t state = seed == 0 ? 0x13579BDFU : seed;
  for (std::size_t i = 0; i < symbols; ++i) {
    state ^= state << 13U;
    state ^= state >> 17U;
    state ^= state << 5U;
    sequence.push_back(state & 0x3U);
  }
  return sequence;
}

double rf_symbol_rate_hz(const RfStreamConfig& config) {
  if (config.waveform == AudioWaveform::fsk4 || config.waveform == AudioWaveform::fsk8)
    return 1000.0 / (config.fsk_useful_ms + config.fsk_guard_ms);
  if (config.waveform == AudioWaveform::bpsk_frequency_diversity)
    return config.modem.bandwidth_hz / 2.0 / 1.25;
  return derived_symbol_rate_hz(config.modem);
}

void validate(const RfStreamConfig& config) {
  validate(config.modem);
  detail::validate_audio_waveform(config);
  if (config.waveform != AudioWaveform::single_carrier && config.modem.symbol_rate_hz &&
      std::abs(*config.modem.symbol_rate_hz - rf_symbol_rate_hz(config)) > 1.0e-6)
    throw std::invalid_argument("alternative waveform symbol rate must match its configured audio timing");
  if (config.header_modulation != Modulation::bpsk && config.header_modulation != Modulation::qpsk)
    throw std::invalid_argument("header modulation must be BPSK or QPSK");
  (void)detail::DifferentialPsk(config);
  if (config.soft_demapping && config.differential_mapping != DifferentialMapping::none)
    throw std::invalid_argument("Euclidean soft demapping requires coherent payload mapping");
  if (config.acquisition_sequence.empty()) {
    throw std::invalid_argument("acquisition_sequence must not be empty");
  }
  if (config.equalizer_training_sequence.empty()) {
    throw std::invalid_argument("equalizer_training_sequence must not be empty");
  }
  if (config.equalizer_feedforward_taps == 0 || config.equalizer_feedforward_taps > 512 ||
      config.equalizer_feedback_taps > 512) {
    throw std::invalid_argument("equalizer tap counts must be feedforward [1,512], feedback [0,512]");
  }
  if (config.equalizer_delay_symbols >= config.equalizer_feedforward_taps) {
    throw std::invalid_argument("equalizer decision delay must be less than feedforward span");
  }
  if (config.adaptive_equalization && config.equalizer_training_sequence.size() <=
      std::max(config.equalizer_feedforward_taps, config.equalizer_feedback_taps)) {
    throw std::invalid_argument("equalizer training sequence must exceed equalizer memory");
  }
  if (!symbol_vector_valid(config.acquisition_sequence, 4)) {
    throw std::invalid_argument("acquisition_sequence must contain QPSK symbols");
  }
  if (!symbol_vector_valid(config.equalizer_training_sequence, 4)) {
    throw std::invalid_argument("equalizer_training_sequence must contain QPSK symbols");
  }
  if (config.pilot_sequence.empty()) {
    throw std::invalid_argument("pilot_sequence must not be empty");
  }
  if (!symbol_vector_valid(config.pilot_sequence, 1ULL << bits_per_symbol(config.modem.modulation))) {
    throw std::invalid_argument("pilot_sequence contains symbols outside configured modulation");
  }
  if (config.symbols_per_frame == 0) {
    throw std::invalid_argument("symbols_per_frame must be positive");
  }
  if (config.pilot_interval_symbols == 0) {
    throw std::invalid_argument("pilot_interval_symbols must be positive");
  }
  if (config.header_repetition == 0 || (config.header_repetition % 2U) == 0U) {
    throw std::invalid_argument("header_repetition must be an odd positive value");
  }
  if (!std::isfinite(config.acquisition_confidence_threshold) ||
      config.acquisition_confidence_threshold < 0.0F ||
      config.acquisition_confidence_threshold > 1.0F) {
    throw std::invalid_argument("acquisition_confidence_threshold must be in [0, 1]");
  }
  if (!std::isfinite(config.pilot_confidence_threshold) ||
      config.pilot_confidence_threshold < 0.0F ||
      config.pilot_confidence_threshold > 1.0F) {
    throw std::invalid_argument("pilot_confidence_threshold must be in [0, 1]");
  }
  if (!std::isfinite(config.symbol_confidence_threshold) ||
      config.symbol_confidence_threshold < 0.0F ||
      config.symbol_confidence_threshold > 1.0F) {
    throw std::invalid_argument("symbol_confidence_threshold must be in [0, 1]");
  }
}

std::uint32_t stream_header_crc32(const RfStreamHeader& header) {
  const auto bytes = serialize_header_without_crc(header);
  return crc32_update(0, std::span<const std::uint8_t>(bytes.data(), serialized_header_bytes - 4U));
}

class AcquisitionCorrelator::Impl {
public:
  explicit Impl(RfStreamConfig config)
      : config_(std::move(config)),
        reference_(build_reference_preamble(config_)) {
    validate(config_);
    reference_energy_ = 0.0F;
    for (const auto sample : reference_) {
      reference_energy_ += std::norm(sample);
    }
  }

  [[nodiscard]] AcquisitionResult scan(std::span<const Complex> samples) const {
    AcquisitionResult result;
    if (samples.size() < reference_.size() || reference_energy_ <= 0.0F) {
      return result;
    }

    float best_metric = -1.0F;
    std::size_t best_index = 0;
    std::vector<float> metrics(samples.size() - reference_.size() + 1U);
    for (std::size_t offset = 0; offset < metrics.size(); ++offset) {
      const auto corr = correlation_at(samples, reference_, offset);
      const float energy = window_energy(samples, offset, reference_.size());
      const float metric = normalized_metric(corr, energy, reference_energy_);
      metrics[offset] = metric;
      if (metric > best_metric) {
        best_metric = metric;
        best_index = offset;
      }
    }

    float sidelobe = 0.0F;
    const auto guard = config_.acquisition_sidelobe_guard_samples;
    for (std::size_t i = 0; i < metrics.size(); ++i) {
      const auto distance = i > best_index ? i - best_index : best_index - i;
      if (distance <= guard) {
        continue;
      }
      sidelobe = std::max(sidelobe, metrics[i]);
    }

    result.sample_index = best_index;
    result.peak_metric = std::max(best_metric, 0.0F);
    result.sidelobe_metric = sidelobe;
    result.confidence = std::clamp((result.peak_metric - sidelobe) / std::max(result.peak_metric, 1.0e-8F),
                                   0.0F,
                                   1.0F);
    // A short scan can put every candidate inside the sidelobe guard, making
    // even noise have confidence == 1. Require actual preamble correlation as
    // well as peak prominence before committing to training/header decoding.
    result.found = result.peak_metric > 0.0F &&
                   result.peak_metric >= config_.acquisition_confidence_threshold &&
                   result.confidence >= config_.acquisition_confidence_threshold;
    return result;
  }

  [[nodiscard]] std::span<const Complex> reference_samples() const noexcept { return reference_; }

private:
  RfStreamConfig config_;
  std::vector<Complex> reference_;
  float reference_energy_ = 0.0F;
};

AcquisitionCorrelator::AcquisitionCorrelator(RfStreamConfig config) : impl_(std::make_unique<Impl>(std::move(config))) {}
AcquisitionCorrelator::~AcquisitionCorrelator() = default;
AcquisitionCorrelator::AcquisitionCorrelator(AcquisitionCorrelator&&) noexcept = default;
AcquisitionCorrelator& AcquisitionCorrelator::operator=(AcquisitionCorrelator&&) noexcept = default;
AcquisitionResult AcquisitionCorrelator::scan(std::span<const Complex> samples) const { return impl_->scan(samples); }
std::span<const Complex> AcquisitionCorrelator::reference_samples() const noexcept { return impl_->reference_samples(); }

class RfStreamEncoder::Impl {
public:
  explicit Impl(RfStreamConfig config)
      : config_(std::move(config)),
        data_encoder_(detail::differential_wire_config(config_)),
        data_constellation_(config_.modem.modulation, config_.modem.constellation_profile),
        wire_constellation_(data_encoder_.config().modulation, config_.modem.constellation_profile),
        differential_(config_) {
    validate(config_);
  }

  [[nodiscard]] const RfStreamConfig& config() const noexcept { return config_; }
  [[nodiscard]] bool active() const noexcept { return state_ != RfStreamState::search; }
  [[nodiscard]] RfStreamState state() const noexcept { return state_; }
  [[nodiscard]] RfStreamHeader current_header() const noexcept { return header_; }

  void start_epoch(std::uint64_t frame_counter_start) {
    reset();
    header_.schedule_epoch_low = static_cast<std::uint32_t>(config_.expected_schedule_epoch & 0xFFFFFFFFULL);
    header_.frame_counter_start = frame_counter_start;
    header_.symbols_per_frame = config_.symbols_per_frame;
    header_.pilot_interval_symbols = config_.pilot_interval_symbols;
    header_.modulation = config_.modem.modulation;
    header_.header_modulation = config_.header_modulation;
    header_.differential_mapping = config_.differential_mapping;
    header_.crc32 = stream_header_crc32(header_);

    auto preamble = build_reference_preamble(config_);
    auto training_header = build_training_header_samples(config_, header_);
    control_samples_ = std::move(preamble);
    control_samples_.insert(control_samples_.end(), training_header.begin(), training_header.end());
    state_ = RfStreamState::acquired;
  }

  RfStreamEncodeResult push_symbols(std::span<const std::uint32_t> symbols, std::span<Complex> out) {
    RfStreamEncodeResult result{.state = state_};
    std::size_t input_offset = 0;

    while (result.produced_samples < out.size()) {
      if (control_offset_ < control_samples_.size()) {
        const auto n = std::min(out.size() - result.produced_samples, control_samples_.size() - control_offset_);
        std::copy_n(control_samples_.begin() + static_cast<std::ptrdiff_t>(control_offset_),
                    static_cast<std::ptrdiff_t>(n),
                    out.begin() + static_cast<std::ptrdiff_t>(result.produced_samples));
        control_offset_ += n;
        result.produced_samples += n;
        state_ = control_offset_ == control_samples_.size() ? RfStreamState::locked : RfStreamState::acquired;
        continue;
      }

      if (closing_) {
        const auto drained = data_encoder_.drain(out.subspan(result.produced_samples));
        result.produced_samples += drained.produced;
        if (drained.produced == 0) {
          state_ = RfStreamState::search;
        }
        break;
      }

      // Drain already synthesized symbol support before accepting another
      // symbol. Otherwise one-sample output buffers enqueue symbols faster
      // than the sample clock can transmit them, creating unbounded latency.
      const auto ready = data_encoder_.push_bits({}, out.subspan(result.produced_samples));
      result.produced_samples += ready.produced;
      if (result.produced_samples == out.size()) break;

      if (startup_pilots_remaining_ != 0) {
        const auto idx = (startup_pilot_symbols(config_) - startup_pilots_remaining_) % config_.pilot_sequence.size();
        push_modulation_symbol(config_.pilot_sequence[idx], out.subspan(result.produced_samples), result);
        --startup_pilots_remaining_;
        if (result.produced_samples == out.size()) {
          break;
        }
        continue;
      }

      if (symbols_until_pilot_ == 0) {
        push_modulation_symbol(config_.pilot_sequence[pilot_index_], out.subspan(result.produced_samples), result);
        pilot_index_ = (pilot_index_ + 1U) % config_.pilot_sequence.size();
        if (pilot_index_ == 0) {
          symbols_until_pilot_ = config_.pilot_interval_symbols;
        }
        if (result.produced_samples == out.size()) {
          break;
        }
        continue;
      }

      if (!finalizing_ && config_.recovery_interval_frames && segment_payload_symbols_ ==
          static_cast<std::uint64_t>(config_.recovery_interval_frames) * config_.symbols_per_frame) {
        if (segment_padding_ < config_.equalizer_delay_symbols) {
          push_modulation_symbol(config_.pilot_sequence[segment_padding_ % config_.pilot_sequence.size()],
                                 out.subspan(result.produced_samples), result);
          ++segment_padding_;
          continue;
        }
        const auto tail = data_encoder_.drain(out.subspan(result.produced_samples));
        result.produced_samples += tail.produced;
        if (tail.produced != 0) continue;
        const auto next_frame = header_.frame_counter_start + config_.recovery_interval_frames;
        start_epoch(next_frame);
        periodic_transition_ = true;
        continue;
      }

      periodic_transition_ = false;

      if (input_offset >= symbols.size()) {
        break;
      }
      const auto symbol = symbols[input_offset++];
      if (symbol >= data_constellation_.size()) {
        throw std::invalid_argument("payload symbol outside configured constellation");
      }
      push_modulation_symbol(symbol, out.subspan(result.produced_samples), result, true);
      --symbols_until_pilot_;
      ++result.consumed_symbols;
      ++segment_payload_symbols_;
    }

    result.state = state_;
    return result;
  }

  RfStreamEncodeResult drain(std::span<Complex> out) {
    if (!finalizing_ && config_.recovery_interval_frames && (periodic_transition_ || segment_payload_symbols_ ==
        static_cast<std::uint64_t>(config_.recovery_interval_frames) * config_.symbols_per_frame)) {
      auto result = push_symbols({}, out);
      if (result.produced_samples != 0) return result;
    }
    finalizing_ = true;
    if (!closing_ && drain_padding_remaining_ != 0) {
      std::array<std::uint32_t, 512> padding{};
      auto result = push_symbols(std::span(padding).first(drain_padding_remaining_), out);
      drain_padding_remaining_ -= result.consumed_symbols;
      result.consumed_symbols = 0;
      if (result.produced_samples != 0 || drain_padding_remaining_ != 0) return result;
    }
    if (!closing_ && symbols_until_pilot_ == 0) {
      // A payload ending exactly at a pilot boundary must finish the same
      // pilot group whether its last sample filled the caller's buffer or not.
      auto result = push_symbols({}, out);
      if (result.produced_samples != 0 || symbols_until_pilot_ == 0) return result;
    }
    closing_ = true;
    return push_symbols({}, out);
  }

  void reset() {
    data_encoder_.reset();
    differential_.reset();
    state_ = RfStreamState::search;
    control_samples_.clear();
    control_offset_ = 0;
    symbols_until_pilot_ = config_.pilot_interval_symbols;
    startup_pilots_remaining_ = startup_pilot_symbols(config_);
    drain_padding_remaining_ = config_.equalizer_delay_symbols;
    pilot_index_ = 0;
    closing_ = false;
    finalizing_ = false;
    periodic_transition_ = false;
    segment_payload_symbols_ = 0;
    segment_padding_ = 0;
    header_ = {};
  }

private:
  void push_modulation_symbol(std::uint32_t symbol, std::span<Complex> out, RfStreamEncodeResult& result, bool payload = false) {
    std::array<std::uint8_t, max_bits_per_symbol> bits{};
    symbol = payload ? differential_.encode(symbol) : differential_.encode_pilot(symbol);
    const auto width = wire_constellation_.bits_per_symbol();
    wire_constellation_.symbol_to_bits(symbol, std::span<std::uint8_t>(bits).first(width));
    const auto pushed = data_encoder_.push_bits(std::span<const std::uint8_t>(bits).first(width), out);
    result.produced_samples += pushed.produced;
    state_ = RfStreamState::locked;
  }

  RfStreamConfig config_;
  Encoder data_encoder_;
  Constellation data_constellation_;
  Constellation wire_constellation_;
  detail::DifferentialPsk differential_;
  RfStreamState state_ = RfStreamState::search;
  RfStreamHeader header_ = {};
  std::vector<Complex> control_samples_;
  std::size_t control_offset_ = 0;
  std::uint32_t symbols_until_pilot_ = 0;
  std::uint32_t startup_pilots_remaining_ = 0;
  std::size_t pilot_index_ = 0;
  bool closing_ = false;
  bool finalizing_ = false;
  bool periodic_transition_ = false;
  std::uint64_t segment_payload_symbols_ = 0;
  std::size_t segment_padding_ = 0;
  std::size_t drain_padding_remaining_ = 0;
};

RfStreamEncoder::RfStreamEncoder(RfStreamConfig config) {
  if (config.waveform == AudioWaveform::single_carrier) impl_ = std::make_unique<Impl>(std::move(config));
  else audio_ = detail::make_audio_encoder(std::move(config));
}
RfStreamEncoder::~RfStreamEncoder() = default;
RfStreamEncoder::RfStreamEncoder(RfStreamEncoder&&) noexcept = default;
RfStreamEncoder& RfStreamEncoder::operator=(RfStreamEncoder&&) noexcept = default;
const RfStreamConfig& RfStreamEncoder::config() const noexcept { return audio_ ? audio_->config() : impl_->config(); }
bool RfStreamEncoder::active() const noexcept { return audio_ ? audio_->active() : impl_->active(); }
RfStreamState RfStreamEncoder::state() const noexcept { return audio_ ? audio_->state() : impl_->state(); }
RfStreamHeader RfStreamEncoder::current_header() const noexcept { return audio_ ? audio_->current_header() : impl_->current_header(); }
void RfStreamEncoder::start_epoch(std::uint64_t frame_counter_start) { if (audio_) audio_->start_epoch(frame_counter_start); else impl_->start_epoch(frame_counter_start); }
RfStreamEncodeResult RfStreamEncoder::push_symbols(std::span<const std::uint32_t> symbols, std::span<Complex> out) {
  return audio_ ? audio_->push_symbols(symbols, out) : impl_->push_symbols(symbols, out);
}
RfStreamEncodeResult RfStreamEncoder::drain(std::span<Complex> out) { return audio_ ? audio_->drain(out) : impl_->drain(out); }
void RfStreamEncoder::reset() { if (audio_) audio_->reset(); else impl_->reset(); }

class RfStreamReceiver::Impl {
public:
  explicit Impl(RfStreamConfig config)
      : config_(std::move(config)),
        correlator_(config_),
        qpsk_decoder_(qpsk_config()),
        data_decoder_(config_.modem),
        data_constellation_(config_.modem.modulation, config_.modem.constellation_profile),
        differential_(config_),
        equalizer_(config_),
        reference_(build_reference_preamble(config_)),
        training_header_samples_(build_training_header_samples(config_, placeholder_header())) {
    validate(config_);
    data_decoder_.set_sample_clock_recovery(config_.sample_clock_recovery);
  }

  [[nodiscard]] const RfStreamConfig& config() const noexcept { return config_; }
  [[nodiscard]] RfStreamState state() const noexcept { return state_; }
  [[nodiscard]] std::optional<RfStreamHeader> header() const noexcept { return header_; }
  [[nodiscard]] RfSyncEstimate sync_estimate() const noexcept { return sync_; }

  RfStreamReceiveResult push_samples(std::span<const Complex> samples, std::span<RfStreamSymbol> out) {
    buffer_.insert(buffer_.end(), samples.begin(), samples.end());
    RfStreamReceiveResult result{.consumed_samples = samples.size(), .state = state_, .sync = sync_, .header = header_};

    bool progressed = true;
    while (progressed) {
      progressed = false;
      if ((state_ == RfStreamState::search || state_ == RfStreamState::recovering) && buffer_.size() >= reference_.size()) {
        progressed = try_acquire(result);
        continue;
      }
      if ((state_ == RfStreamState::training || state_ == RfStreamState::header) &&
          buffer_.size() >= training_header_input_size()) {
        progressed = try_decode_training_header(result);
        continue;
      }
      if (state_ == RfStreamState::locked && result.produced_symbols < out.size()) {
        progressed = decode_payload_symbols(out, result);
        // Return the old segment's symbols before publishing a later header.
        if (state_ == RfStreamState::recovering) break;
      }
    }

    result.state = state_;
    result.sync = sync_;
    result.header = header_;
    return result;
  }

  void reset() {
    state_ = RfStreamState::search;
    buffer_.clear();
    recent_audio_.clear();
    first_sample_index_ = 0;
    qpsk_decoder_.reset();
    data_decoder_.reset();
    differential_.reset();
    bad_pilots_ = 0;
    noise_variance_ = 1.0F;
    pilot_group_bad_ = false;
    equalizer_.reset();
    header_ = std::nullopt;
    sync_ = {};
    carrier_origin_sample_ = 0;
    pending_symbols_.clear();
    pending_symbol_offset_ = 0;
    frame_counter_ = 0;
    frame_symbol_offset_ = 0;
    symbols_until_pilot_ = config_.pilot_interval_symbols;
    startup_pilots_remaining_ = 0;
    pilot_index_ = 0;
  }

private:
  std::size_t training_header_input_size() const {
    return training_header_samples_.size() + static_cast<std::size_t>(std::ceil(
        config_.equalizer_delay_symbols * describe(config_.modem).samples_per_symbol));
  }

  ModemConfig qpsk_config() const {
    auto cfg = config_.modem;
    cfg.modulation = Modulation::qpsk;
    cfg.receiver_oversampling = 1;
    cfg.symbol_confidence_threshold = config_.symbol_confidence_threshold;
    return cfg;
  }

  RfStreamHeader placeholder_header() const {
    RfStreamHeader header;
    header.schedule_epoch_low = static_cast<std::uint32_t>(config_.expected_schedule_epoch & 0xFFFFFFFFULL);
    header.frame_counter_start = 0;
    header.symbols_per_frame = config_.symbols_per_frame;
    header.pilot_interval_symbols = config_.pilot_interval_symbols;
    header.modulation = config_.modem.modulation;
    header.header_modulation = config_.header_modulation;
    header.differential_mapping = config_.differential_mapping;
    header.crc32 = stream_header_crc32(header);
    return header;
  }

  bool try_acquire(RfStreamReceiveResult& result) {
    const auto scan = correlator_.scan(buffer_);
    if (!scan.found) {
      const auto keep = reference_.size() - 1U;
      if (buffer_.size() > keep) {
        erase_prefix(buffer_, buffer_.size() - keep, first_sample_index_);
      }
      return false;
    }

    // A partially observed preamble can have a local maximum before its true
    // correlation peak. This matters when joining a running stream: preceding
    // payload supplies candidates that do not exist at sample zero. Observe
    // one full symbol beyond the candidate before committing its timing.
    const auto confirmation = static_cast<std::size_t>(std::ceil(describe(config_.modem).samples_per_symbol));
    if (scan.sample_index + reference_.size() + confirmation > buffer_.size()) {
      return false;
    }

    result.acquisition = scan;
    result.acquisition.sample_index = static_cast<std::size_t>(first_sample_index_ + scan.sample_index);
    result.acquisition_found = true;
    sync_.training_evm = 0.0F;
    const auto half = reference_.size() / 2U;
    if (half > 0) {
      const auto early = correlation_at(std::span<const Complex>(buffer_.data() + scan.sample_index, half),
                                        std::span<const Complex>(reference_.data(), half),
                                        0);
      const auto late_count = reference_.size() - half;
      const auto late = correlation_at(std::span<const Complex>(buffer_.data() + scan.sample_index + half, late_count),
                                       std::span<const Complex>(reference_.data() + half, late_count),
                                       0);
      const auto phase_delta = std::atan2((late * std::conj(early)).imag(), (late * std::conj(early)).real());
      double early_energy = 0.0, late_energy = 0.0;
      double early_time = 0.0, late_time = 0.0;
      for (std::size_t i = 0; i < reference_.size(); ++i) {
        const double energy = std::norm(reference_[i]);
        if (i < half) {
          early_energy += energy;
          early_time += energy * static_cast<double>(i);
        } else {
          late_energy += energy;
          late_time += energy * static_cast<double>(i);
        }
      }
      // Pulse shaping makes the two halves' energy centroids differ from their
      // geometric centers. Using those centroids removes the coarse CFO bias.
      const double time_delta = (late_time / std::max(late_energy, 1.0e-12) -
                                 early_time / std::max(early_energy, 1.0e-12)) / config_.modem.sample_rate_hz;
      sync_.carrier_frequency_offset_hz = time_delta > 0.0
          ? static_cast<double>(phase_delta) / (2.0 * std::numbers::pi * time_delta)
          : 0.0;
    }
    Complex channel_sum{};
    float reference_energy = 0.0F;
    for (std::size_t i = 0; i < reference_.size(); ++i) {
      const auto phase = -2.0 * std::numbers::pi * sync_.carrier_frequency_offset_hz *
                         static_cast<double>(i) / config_.modem.sample_rate_hz;
      channel_sum += buffer_[scan.sample_index + i] * std::conj(reference_[i]) *
                     std::polar(1.0F, static_cast<float>(phase));
      reference_energy += std::norm(reference_[i]);
    }
    sync_.channel = channel_sum / std::max(reference_energy, 1.0e-8F);
    sync_.carrier_phase_rad = std::arg(sync_.channel);
    carrier_origin_sample_ = result.acquisition.sample_index;
    sync_.symbol_timing_offset_samples = std::fmod(static_cast<double>(result.acquisition.sample_index),
                                                   describe(config_.modem).samples_per_symbol);

    erase_prefix(buffer_, scan.sample_index + reference_.size(), first_sample_index_);
    qpsk_decoder_.reset();
    state_ = RfStreamState::training;
    result.state = state_;
    return true;
  }

  std::span<const Complex> correct_samples(std::span<const Complex> samples) {
    corrected_samples_.resize(samples.size());
    const float scale = 1.0F / (std::max(std::abs(sync_.channel), 1.0e-6F) * config_.modem.tx_gain);
    const double omega = 2.0 * std::numbers::pi * sync_.carrier_frequency_offset_hz / config_.modem.sample_rate_hz;
    for (std::size_t i = 0; i < samples.size(); ++i) {
      const auto phase = config_.carrier_correction
          ? -sync_.carrier_phase_rad - omega * static_cast<double>(first_sample_index_ + i - carrier_origin_sample_)
          : 0.0;
      corrected_samples_[i] = samples[i] * std::polar(scale, static_cast<float>(std::remainder(phase, 2.0 * std::numbers::pi)));
    }
    return corrected_samples_;
  }

  bool try_decode_training_header(RfStreamReceiveResult& result) {
    const auto delay = config_.equalizer_delay_symbols;
    const auto expected_symbols = expected_training_header_bits(config_) / 2U + delay;
    std::vector<Complex> symbols(expected_symbols + 8U);
    std::vector<Complex> halves(config_.fractionally_spaced_equalization ? symbols.size() : 0);
    qpsk_decoder_.reset();
    const auto decoded = qpsk_decoder_.push_samples_matched(
        correct_samples(std::span<const Complex>(buffer_).first(training_header_input_size())), symbols, halves);
    if (decoded.produced_symbols < expected_symbols) {
      return false;
    }
    Constellation qpsk(Modulation::qpsk);
    Constellation header_constellation(config_.header_modulation);
    const auto training_count = config_.equalizer_training_sequence.size();
    equalizer_.reset();
    const auto guard = std::max(equalizer_.memory_symbols(), config_.modem.filter_span_symbols / 2U);
    double error_power = 0.0;
    std::size_t error_count = 0;
    const std::size_t passes = config_.adaptive_equalization ? (config_.recursive_equalization ? 13 : 12) : 1;
    for (std::size_t pass = 0; pass < passes; ++pass) {
      // Reuse the already received training block; no extra RF symbols or
      // steady-state buffering are introduced by these convergence passes.
      equalizer_.restart_training_pass();
      if (pass == 12 && config_.recursive_equalization) equalizer_.start_recursive_tracking();
      for (std::size_t i = 0; i < training_count + delay; ++i) {
        const auto observed = equalizer_.filter(symbols[i], halves.empty() ? Complex{} : halves[i]);
        const auto desired = i >= delay ? qpsk.map_symbol(config_.equalizer_training_sequence[i-delay]) : Complex{};
        if (pass + 1 == passes && i >= guard) {
          error_power += std::norm(desired - observed);
          ++error_count;
        }
        equalizer_.update(desired, observed, equalizer_step, i >= guard, true);
      }
    }
    sync_.training_evm = static_cast<float>(std::sqrt(error_power / std::max<std::size_t>(error_count, 1U)));
    noise_variance_ = std::max(1.0e-4F, sync_.training_evm * sync_.training_evm);
    if (!std::isfinite(sync_.training_evm) || sync_.training_evm > 0.45F) {
      lose_lock(result);
      return true;
    }

    std::vector<std::uint8_t> repeated_bits;
    std::vector<SoftBit> coded_header;
    repeated_bits.reserve(serialized_header_bytes * 8U * config_.header_repetition);
    std::size_t header_data_index = 0, header_probe_index = 0;
    for (std::size_t i = training_count + delay; i < expected_symbols; ++i) {
      auto observed = equalizer_.filter(symbols[i], halves.empty() ? Complex{} : halves[i]);
      if (config_.compact_header && header_data_index != 0 && header_data_index % header_probe_interval == 0 &&
          header_probe_index < header_probe_length) {
        const auto known = config_.equalizer_training_sequence[(header_data_index+header_probe_index) %
            config_.equalizer_training_sequence.size()];
        observed = equalizer_.track_pilot_gain(qpsk.map_symbol(known), observed);
        equalizer_.update(qpsk.map_symbol(known), observed, equalizer_step, true, true);
        ++header_probe_index;
        continue;
      }
      const auto decision = header_constellation.decide(observed);
      std::array<std::uint8_t, 2> bits{};
      const auto decoded_bits = std::span(bits).first(header_constellation.bits_per_symbol());
      header_constellation.symbol_to_bits(decision.symbol, decoded_bits);
      repeated_bits.insert(repeated_bits.end(), decoded_bits.begin(), decoded_bits.end());
      if (config_.soft_demapping) {
        std::array<SoftBit, 2> soft{};
        header_constellation.soft_bits(observed, noise_variance_, soft);
        coded_header.insert(coded_header.end(), soft.begin(), soft.begin() + decoded_bits.size());
      } else {
        for (const auto bit : decoded_bits) coded_header.push_back({bit, decision.confidence >= tracking_confidence, decision.confidence});
      }
      equalizer_.update(header_constellation.map_symbol(decision.symbol), observed, equalizer_step,
                        decision.confidence >= tracking_confidence);
      ++header_data_index;
      header_probe_index = 0;
    }
    std::optional<RfStreamHeader> parsed;
    if (config_.compact_header) {
      const auto decoded_header = SoftViterbiDecoder().decode(coded_header, compact_input_bits);
      std::array<std::uint8_t, compact_header_bytes> bytes{};
      for (std::size_t i = 0; i < bytes.size(); ++i) bytes[i] = decoded_header.bytes[i].value;
      auto candidate = placeholder_header();
      candidate.schedule_epoch_low = read_u32_be(bytes, 0);
      candidate.frame_counter_start = read_u64_be(bytes, 4);
      candidate.crc32 = read_u32_be(bytes, 12);
      if (candidate.crc32 == stream_header_crc32(candidate)) parsed = candidate;
    } else {
      parsed = parse_header(majority_header_bytes(repeated_bits, config_.header_repetition));
    }
    if (!parsed.has_value()) {
      lose_lock(result);
      return true;
    }
    if (parsed->schedule_epoch_low != static_cast<std::uint32_t>(config_.expected_schedule_epoch & 0xFFFFFFFFULL) ||
        parsed->modulation != config_.modem.modulation ||
        parsed->header_modulation != config_.header_modulation ||
        parsed->differential_mapping != config_.differential_mapping ||
        parsed->symbols_per_frame != config_.symbols_per_frame ||
        parsed->pilot_interval_symbols != config_.pilot_interval_symbols) {
      state_ = RfStreamState::protocol_error;
      result.state = state_;
      erase_prefix(buffer_, training_header_samples_.size(), first_sample_index_);
      return true;
    }

    header_ = *parsed;
    recent_audio_.clear();
    frame_counter_ = parsed->frame_counter_start;
    frame_symbol_offset_ = 0;
    symbols_until_pilot_ = config_.pilot_interval_symbols;
    startup_pilots_remaining_ = startup_pilot_symbols(config_);
    startup_discard_symbols_ = delay;
    pilot_index_ = 0;
    pending_symbols_.clear();
    pending_symbol_offset_ = 0;
    data_decoder_.reset();
    differential_.reset();
    bad_pilots_ = 0;
    pilot_group_bad_ = false;
    equalizer_.clear_history();
    equalizer_.advance_phase(static_cast<double>(training_header_samples_.size()) /
                                 describe(config_.modem).samples_per_symbol - static_cast<double>(expected_symbols));
    erase_prefix(buffer_, training_header_samples_.size(), first_sample_index_);
    state_ = RfStreamState::locked;
    result.header_valid = true;
    result.header = header_;
    result.state = state_;
    return true;
  }

  bool decode_payload_symbols(std::span<RfStreamSymbol> out, RfStreamReceiveResult& result) {
    if (pending_symbol_offset_ == pending_symbols_.size()) {
      pending_symbols_.resize(256);
      pending_halves_.resize(config_.fractionally_spaced_equalization ? pending_symbols_.size() : 0);
      const auto count = config_.recovery_interval_frames ? std::min<std::size_t>(buffer_.size(), 256) : buffer_.size();
      const auto audio = std::span<const Complex>(buffer_).first(count);
      const auto decoded = data_decoder_.push_samples_matched(correct_samples(audio), pending_symbols_, pending_halves_);
      if (config_.recovery_interval_frames) {
        recent_audio_.insert(recent_audio_.end(), audio.begin(), audio.end());
        const auto keep = reference_.size() * 2U + 256U;
        if (recent_audio_.size() > keep) recent_audio_.erase(recent_audio_.begin(), recent_audio_.end()-static_cast<std::ptrdiff_t>(keep));
      }
      sync_.sample_clock_error_ppm = data_decoder_.recovered_clock_ppm();
      erase_prefix(buffer_, count, first_sample_index_);
      pending_symbols_.resize(decoded.produced_symbols);
      pending_symbol_offset_ = 0;
      if (pending_symbols_.empty()) {
        return false;
      }
    }
    while (pending_symbol_offset_ < pending_symbols_.size() && result.produced_symbols < out.size()) {
      const auto index = pending_symbol_offset_++;
      auto observed = equalizer_.filter(pending_symbols_[index], pending_halves_.empty() ? Complex{} : pending_halves_[index]);
      if (!std::isfinite(observed.real()) || !std::isfinite(observed.imag())) {
        lose_lock(result);
        return true;
      }
      if (startup_pilots_remaining_ == 0 && symbols_until_pilot_ == 0) {
        observed = equalizer_.track_pilot_gain(
            data_constellation_.map_symbol(config_.pilot_sequence[pilot_index_]), observed);
      } else if (config_.compact_header && startup_discard_symbols_ == 0 && startup_pilots_remaining_ != 0) {
        const auto elapsed = startup_pilot_symbols(config_) - startup_pilots_remaining_;
        if (elapsed >= equalizer_.memory_symbols())
          observed = equalizer_.track_pilot_gain(data_constellation_.map_symbol(
              config_.pilot_sequence[elapsed % config_.pilot_sequence.size()]), observed);
      }
      const bool payload = startup_discard_symbols_ == 0 && startup_pilots_remaining_ == 0 && symbols_until_pilot_ != 0;
      const auto rotation = payload ? differential_.physical_rotation() : Complex{1, 0};
      const auto decision = data_constellation_.decide(observed * std::conj(rotation));
      if (!consume_modulation_symbol(decision, observed, rotation, out, result)) {
        return true;
      }
    }
    return true;
  }

  bool consume_modulation_symbol(const SymbolDecision& decision,
                                 Complex observed,
                                 Complex rotation,
                                 std::span<RfStreamSymbol> out,
                                 RfStreamReceiveResult& result) {
    auto symbol = decision.symbol;
    auto confidence = decision.confidence;

    if (startup_discard_symbols_ != 0) {
      equalizer_.update({}, observed, equalizer_step, false);
      --startup_discard_symbols_;
      return true;
    }

    if (startup_pilots_remaining_ != 0) {
      const auto index = (startup_pilot_symbols(config_) - startup_pilots_remaining_) % config_.pilot_sequence.size();
      equalizer_.update(data_constellation_.map_symbol(config_.pilot_sequence[index]), observed, equalizer_step,
                        startup_pilot_symbols(config_) - startup_pilots_remaining_ >= equalizer_.memory_symbols(), true);
      --startup_pilots_remaining_;
      differential_.observe_pilot(observed);
      return true;
    }

    if (symbols_until_pilot_ == 0) {
      const auto expected = config_.pilot_sequence[pilot_index_];
      // One-pole mean squared known-pilot residual (32-pilot time constant).
      // It measures receiver residual error, without channel-model truth.
      const auto residual = std::norm(observed - data_constellation_.map_symbol(expected));
      if (std::isfinite(residual))
        noise_variance_ = std::max(1.0e-4F, noise_variance_ + (residual - noise_variance_) / 32.0F);
      differential_.observe_pilot(observed);
      if (symbol != expected || confidence < config_.pilot_confidence_threshold) {
        pilot_group_bad_ = true;
      }
      // A single damaged pilot is not a sample/bit slip. Its known value can
      // retrain the equalizer; sustained disagreement still drops lock.
      equalizer_.update(data_constellation_.map_symbol(expected), observed, equalizer_step,
                        config_.recursive_equalization ||
                            (symbol == expected && confidence >= config_.pilot_confidence_threshold), true);
      pilot_index_ = (pilot_index_ + 1U) % config_.pilot_sequence.size();
      if (pilot_index_ == 0) {
        bad_pilots_ = pilot_group_bad_ ? bad_pilots_ + 1U : 0U;
        pilot_group_bad_ = false;
        if (bad_pilots_ >= 2U) {
          lose_lock(result);
          return false;
        }
        symbols_until_pilot_ = config_.pilot_interval_symbols;
      }
      return true;
    }

    if (result.produced_symbols == out.size()) {
      return false;
    }
    equalizer_.update(data_constellation_.map_symbol(symbol) * rotation, observed, equalizer_step,
                      confidence >= tracking_confidence);
    if (differential_.enabled()) {
      const auto decoded = differential_.decode(observed);
      symbol = decoded.symbol;
      confidence = decoded.confidence;
    }
    out[result.produced_symbols++] = {.value = symbol,
                                      .bits_per_symbol = static_cast<std::uint8_t>(data_constellation_.bits_per_symbol()),
                                      .frame_counter = frame_counter_,
                                      .frame_symbol_offset = frame_symbol_offset_,
                                      .certain = confidence >= config_.symbol_confidence_threshold,
                                      .confidence = confidence};
    if (config_.soft_demapping) {
      auto& decoded = out[result.produced_symbols - 1];
      decoded.has_soft_bits = true;
      data_constellation_.soft_bits(observed, noise_variance_, decoded.soft_bits);
    }
    ++frame_symbol_offset_;
    --symbols_until_pilot_;
    if (frame_symbol_offset_ == config_.symbols_per_frame) {
      frame_symbol_offset_ = 0;
      ++frame_counter_;
      if (config_.recovery_interval_frames && frame_counter_ - header_->frame_counter_start == config_.recovery_interval_frames) {
        enter_recovery();
        return false;
      }
    }
    return true;
  }

  void lose_lock(RfStreamReceiveResult& result) {
    result.lock_lost = true;
    state_ = config_.recovery_interval_frames ? RfStreamState::recovering : RfStreamState::search;
    qpsk_decoder_.reset();
    data_decoder_.reset();
    bad_pilots_ = 0;
    pilot_group_bad_ = false;
    equalizer_.reset();
    pending_symbols_.clear();
    pending_symbol_offset_ = 0;
    header_ = std::nullopt;
    symbols_until_pilot_ = config_.pilot_interval_symbols;
    startup_pilots_remaining_ = 0;
    pilot_index_ = 0;
    if (config_.recovery_interval_frames) {
      restore_recent_audio();
    } else {
      erase_prefix(buffer_, buffer_.size(), first_sample_index_);
    }
    result.state = RfStreamState::lock_lost;
  }

  void restore_recent_audio() {
    first_sample_index_ -= recent_audio_.size();
    buffer_.insert(buffer_.begin(), recent_audio_.begin(), recent_audio_.end());
    recent_audio_.clear();
  }

  void enter_recovery() {
    // The receive filter may have read ahead into the next preamble. Retain
    // that raw audio when leaving the old segment; never search sliced data.
    restore_recent_audio();
    state_ = RfStreamState::recovering;
    data_decoder_.reset();
    pending_symbols_.clear();
    pending_symbol_offset_ = 0;
  }

  RfStreamConfig config_;
  AcquisitionCorrelator correlator_;
  Decoder qpsk_decoder_;
  Decoder data_decoder_;
  Constellation data_constellation_;
  detail::DifferentialPsk differential_;
  detail::RfEqualizer equalizer_;
  float noise_variance_ = 1.0F;
  std::size_t bad_pilots_ = 0;
  bool pilot_group_bad_ = false;
  std::size_t startup_discard_symbols_ = 0;
  std::vector<Complex> reference_;
  std::vector<Complex> training_header_samples_;
  RfStreamState state_ = RfStreamState::search;
  std::vector<Complex> buffer_;
  std::uint64_t first_sample_index_ = 0;
  std::optional<RfStreamHeader> header_ = std::nullopt;
  RfSyncEstimate sync_ = {};
  std::uint64_t carrier_origin_sample_ = 0;
  std::vector<Complex> corrected_samples_;
  std::vector<Complex> pending_symbols_;
  std::vector<Complex> pending_halves_, recent_audio_;
  std::size_t pending_symbol_offset_ = 0;
  std::uint64_t frame_counter_ = 0;
  std::uint32_t frame_symbol_offset_ = 0;
  std::uint32_t symbols_until_pilot_ = 0;
  std::uint32_t startup_pilots_remaining_ = 0;
  std::size_t pilot_index_ = 0;
};

RfStreamReceiver::RfStreamReceiver(RfStreamConfig config) {
  if (config.waveform == AudioWaveform::single_carrier) impl_ = std::make_unique<Impl>(std::move(config));
  else audio_ = detail::make_audio_receiver(std::move(config));
}
RfStreamReceiver::~RfStreamReceiver() = default;
RfStreamReceiver::RfStreamReceiver(RfStreamReceiver&&) noexcept = default;
RfStreamReceiver& RfStreamReceiver::operator=(RfStreamReceiver&&) noexcept = default;
const RfStreamConfig& RfStreamReceiver::config() const noexcept { return audio_ ? audio_->config() : impl_->config(); }
RfStreamState RfStreamReceiver::state() const noexcept { return audio_ ? audio_->state() : impl_->state(); }
std::optional<RfStreamHeader> RfStreamReceiver::header() const noexcept { return audio_ ? audio_->header() : impl_->header(); }
RfSyncEstimate RfStreamReceiver::sync_estimate() const noexcept { return audio_ ? audio_->sync_estimate() : impl_->sync_estimate(); }
RfStreamReceiveResult RfStreamReceiver::push_samples(std::span<const Complex> samples, std::span<RfStreamSymbol> out) {
  return audio_ ? audio_->push_samples(samples, out) : impl_->push_samples(samples, out);
}
void RfStreamReceiver::reset() { if (audio_) audio_->reset(); else impl_->reset(); }

} // namespace goblin_cannon
