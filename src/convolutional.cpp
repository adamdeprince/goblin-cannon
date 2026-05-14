#include "wbhf_modem/convolutional.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace wbhf_modem {

namespace {

struct Observation {
  std::uint8_t mother_index = 0;
  SoftBit bit = {};
};

struct Decision {
  std::uint16_t previous_state = 0;
  std::uint8_t bit = 0;
  float confidence = 0.0F;
  bool valid = false;
};

std::uint8_t parity(std::uint32_t value) noexcept {
  value ^= value >> 16U;
  value ^= value >> 8U;
  value ^= value >> 4U;
  value &= 0xFU;
  return static_cast<std::uint8_t>((0x6996U >> value) & 1U);
}

std::uint8_t keystream_bit(std::span<const std::uint8_t> bytes, std::size_t bit_index) {
  return static_cast<std::uint8_t>((bytes[bit_index / 8U] >> (7U - (bit_index % 8U))) & 1U);
}

std::vector<std::uint8_t> bytes_to_bits(std::span<const std::uint8_t> bytes) {
  std::vector<std::uint8_t> bits;
  bits.reserve(bytes.size() * 8U);
  for (const auto byte : bytes) {
    for (int bit = 7; bit >= 0; --bit) {
      bits.push_back(static_cast<std::uint8_t>((byte >> bit) & 1U));
    }
  }
  return bits;
}

std::vector<Token> pack_soft_bits_to_tokens(std::span<const SoftBit> bits, float threshold) {
  std::vector<Token> bytes;
  bytes.reserve(bits.size() / 8U);
  for (std::size_t offset = 0; offset + 8U <= bits.size(); offset += 8U) {
    std::uint8_t value = 0;
    bool certain = true;
    float confidence = 1.0F;
    for (std::size_t bit = 0; bit < 8U; ++bit) {
      const auto soft = bits[offset + bit];
      value = static_cast<std::uint8_t>((value << 1U) | (soft.value & 1U));
      confidence = std::min(confidence, soft.confidence);
      certain = certain && soft.certain && soft.confidence >= threshold;
    }
    bytes.push_back({.value = value, .certain = certain, .confidence = confidence});
  }
  return bytes;
}

float branch_metric(std::span<const Observation> observations,
                    std::uint8_t expected0,
                    std::uint8_t expected1,
                    float& confidence) {
  float metric = 0.0F;
  float confidence_sum = 0.0F;
  std::size_t confidence_count = 0;

  for (const auto& observation : observations) {
    const auto expected = observation.mother_index == 0U ? expected0 : expected1;
    if (!observation.bit.certain || observation.bit.confidence <= 0.0F) {
      continue;
    }
    const auto clamped = std::clamp(observation.bit.confidence, 0.0F, 1.0F);
    confidence_sum += clamped;
    ++confidence_count;
    if ((observation.bit.value & 1U) != expected) {
      metric += clamped;
    }
  }

  confidence = confidence_count == 0U ? 0.0F : confidence_sum / static_cast<float>(confidence_count);
  return metric;
}

} // namespace

PuncturedConvolutionalCodeConfig PuncturedConvolutionalCodeConfig::rate_1_2() {
  return {.constraint_length = 7,
          .generator0 = 0171,
          .generator1 = 0133,
          .puncture_pattern = {1, 1},
          .decoded_bit_confidence_threshold = 0.20F};
}

PuncturedConvolutionalCodeConfig PuncturedConvolutionalCodeConfig::rate_2_3() {
  return {.constraint_length = 7,
          .generator0 = 0171,
          .generator1 = 0133,
          .puncture_pattern = {1, 1, 1, 0},
          .decoded_bit_confidence_threshold = 0.20F};
}

PuncturedConvolutionalCodeConfig PuncturedConvolutionalCodeConfig::rate_3_4() {
  return {.constraint_length = 7,
          .generator0 = 0171,
          .generator1 = 0133,
          .puncture_pattern = {1, 1, 1, 0, 0, 1},
          .decoded_bit_confidence_threshold = 0.20F};
}

void validate(const PuncturedConvolutionalCodeConfig& config) {
  if (config.constraint_length < 3U || config.constraint_length > 12U) {
    throw std::invalid_argument("constraint_length must be in [3, 12]");
  }
  if (config.generator0 == 0U || config.generator1 == 0U) {
    throw std::invalid_argument("convolutional generators must be non-zero");
  }
  if (config.puncture_pattern.empty()) {
    throw std::invalid_argument("puncture_pattern must not be empty");
  }
  if (std::none_of(config.puncture_pattern.begin(), config.puncture_pattern.end(), [](std::uint8_t keep) {
        return keep != 0U;
      })) {
    throw std::invalid_argument("puncture_pattern must keep at least one coded bit");
  }
  if (!std::isfinite(config.decoded_bit_confidence_threshold) ||
      config.decoded_bit_confidence_threshold < 0.0F ||
      config.decoded_bit_confidence_threshold > 1.0F) {
    throw std::invalid_argument("decoded_bit_confidence_threshold must be in [0, 1]");
  }
}

PuncturedConvolutionalEncoder::PuncturedConvolutionalEncoder(PuncturedConvolutionalCodeConfig config)
    : config_(std::move(config)) {
  validate(config_);
}

std::vector<std::uint8_t> PuncturedConvolutionalEncoder::push_bit(std::uint8_t bit) {
  const auto full_mask = (1U << config_.constraint_length) - 1U;
  shift_register_ = ((shift_register_ << 1U) | (bit & 1U)) & full_mask;
  const std::array<std::uint8_t, 2> mother = {
      parity(shift_register_ & config_.generator0),
      parity(shift_register_ & config_.generator1),
  };

  std::vector<std::uint8_t> out;
  out.reserve(2);
  for (std::uint8_t i = 0; i < 2U; ++i) {
    if (config_.puncture_pattern[mother_bit_index_ % config_.puncture_pattern.size()] != 0U) {
      out.push_back(mother[i]);
    }
    ++mother_bit_index_;
  }
  return out;
}

std::vector<std::uint8_t> PuncturedConvolutionalEncoder::push_bytes(std::span<const std::uint8_t> bytes) {
  std::vector<std::uint8_t> out;
  out.reserve(bytes.size() * 2U * 8U);
  for (const auto bit : bytes_to_bits(bytes)) {
    auto coded = push_bit(bit);
    out.insert(out.end(), coded.begin(), coded.end());
  }
  return out;
}

void PuncturedConvolutionalEncoder::reset() noexcept {
  shift_register_ = 0;
  mother_bit_index_ = 0;
}

SoftViterbiDecoder::SoftViterbiDecoder(PuncturedConvolutionalCodeConfig config)
    : config_(std::move(config)) {
  validate(config_);
}

ViterbiDecodeResult SoftViterbiDecoder::decode(std::span<const SoftBit> coded_bits,
                                               std::size_t output_bits) const {
  const auto states = 1U << (config_.constraint_length - 1U);
  const auto state_mask = states - 1U;
  const auto full_mask = (1U << config_.constraint_length) - 1U;
  constexpr float inf = std::numeric_limits<float>::infinity();

  std::vector<float> metrics(states, inf);
  std::vector<float> next_metrics(states, inf);
  metrics[0] = 0.0F;
  std::vector<std::vector<Decision>> history(output_bits, std::vector<Decision>(states));

  std::size_t coded_offset = 0;
  std::size_t mother_bit_index = 0;
  for (std::size_t step = 0; step < output_bits; ++step) {
    std::array<Observation, 2> observation_storage{};
    std::size_t observation_count = 0;
    for (std::uint8_t mother = 0; mother < 2U; ++mother) {
      if (config_.puncture_pattern[mother_bit_index % config_.puncture_pattern.size()] != 0U) {
        if (coded_offset >= coded_bits.size()) {
          throw std::invalid_argument("not enough coded soft bits for requested Viterbi output length");
        }
        observation_storage[observation_count++] = {.mother_index = mother, .bit = coded_bits[coded_offset++]};
      }
      ++mother_bit_index;
    }
    const auto observations = std::span<const Observation>(observation_storage).first(observation_count);

    std::fill(next_metrics.begin(), next_metrics.end(), inf);
    for (auto& decision : history[step]) {
      decision = {};
    }

    for (std::uint32_t previous = 0; previous < states; ++previous) {
      if (!std::isfinite(metrics[previous])) {
        continue;
      }
      for (std::uint8_t bit = 0; bit < 2U; ++bit) {
        const auto reg = ((previous << 1U) | bit) & full_mask;
        const auto next_state = reg & state_mask;
        const auto expected0 = parity(reg & config_.generator0);
        const auto expected1 = parity(reg & config_.generator1);
        float confidence = 0.0F;
        const auto metric = branch_metric(observations, expected0, expected1, confidence);
        const auto candidate = metrics[previous] + metric;
        if (candidate < next_metrics[next_state]) {
          next_metrics[next_state] = candidate;
          history[step][next_state] = {.previous_state = static_cast<std::uint16_t>(previous),
                                       .bit = bit,
                                       .confidence = confidence,
                                       .valid = true};
        }
      }
    }
    metrics.swap(next_metrics);
  }

  const auto best = std::min_element(metrics.begin(), metrics.end());
  if (best == metrics.end() || !std::isfinite(*best)) {
    throw std::runtime_error("Viterbi decoder could not find a valid path");
  }
  auto state = static_cast<std::uint32_t>(std::distance(metrics.begin(), best));

  ViterbiDecodeResult result;
  result.bits.resize(output_bits);
  result.consumed_soft_bits = coded_offset;
  result.path_metric = *best;
  for (std::size_t step = output_bits; step-- > 0U;) {
    const auto decision = history[step][state];
    if (!decision.valid) {
      throw std::runtime_error("Viterbi traceback encountered an invalid decision");
    }
    result.bits[step] = {.value = decision.bit,
                         .certain = decision.confidence >= config_.decoded_bit_confidence_threshold,
                         .confidence = decision.confidence};
    state = decision.previous_state;
  }
  result.bytes = pack_soft_bits_to_tokens(result.bits, config_.decoded_bit_confidence_threshold);
  return result;
}

ViterbiDecodeResult SoftViterbiDecoder::decode_bytes(std::span<const SoftBit> coded_bits,
                                                     std::size_t output_bytes) const {
  return decode(coded_bits, output_bytes * 8U);
}

std::vector<std::uint8_t> convolutional_encode_bytes(std::span<const std::uint8_t> bytes,
                                                     const PuncturedConvolutionalCodeConfig& config) {
  PuncturedConvolutionalEncoder encoder(config);
  return encoder.push_bytes(bytes);
}

std::size_t convolutional_coded_bits_for_input_bits(std::size_t input_bits,
                                                   const PuncturedConvolutionalCodeConfig& config) {
  validate(config);
  std::size_t coded_bits = 0;
  for (std::size_t i = 0; i < input_bits * 2U; ++i) {
    coded_bits += config.puncture_pattern[i % config.puncture_pattern.size()] != 0U ? 1U : 0U;
  }
  return coded_bits;
}

std::size_t convolutional_coded_bits_for_input_bytes(std::size_t input_bytes,
                                                    const PuncturedConvolutionalCodeConfig& config) {
  return convolutional_coded_bits_for_input_bits(input_bytes * 8U, config);
}

Aes128CtrBitXor::Aes128CtrBitXor(Aes128Key key, Aes128CtrCounter counter)
    : stream_(key, counter) {}

std::uint8_t Aes128CtrBitXor::next_keystream_bit() {
  if (remaining_bits_ == 0U) {
    std::array<std::uint8_t, 1> next{};
    stream_.generate(next);
    current_byte_ = next[0];
    remaining_bits_ = 8U;
  }
  const auto shift = static_cast<std::uint8_t>(remaining_bits_ - 1U);
  const auto bit = static_cast<std::uint8_t>((current_byte_ >> shift) & 1U);
  --remaining_bits_;
  return bit;
}

std::uint8_t Aes128CtrBitXor::xor_bit(std::uint8_t bit) {
  return static_cast<std::uint8_t>((bit & 1U) ^ next_keystream_bit());
}

SoftBit Aes128CtrBitXor::xor_soft_bit(SoftBit bit) {
  bit.value = xor_bit(bit.value);
  return bit;
}

std::vector<std::uint8_t> Aes128CtrBitXor::xor_bits(std::span<const std::uint8_t> bits) {
  std::vector<std::uint8_t> out;
  out.reserve(bits.size());
  for (const auto bit : bits) {
    out.push_back(xor_bit(bit));
  }
  return out;
}

std::vector<SoftBit> Aes128CtrBitXor::xor_soft_bits(std::span<const SoftBit> bits) {
  std::vector<SoftBit> out;
  out.reserve(bits.size());
  for (const auto bit : bits) {
    out.push_back(xor_soft_bit(bit));
  }
  return out;
}

std::vector<std::uint8_t> aes128_ctr_xor_bits(std::span<const std::uint8_t> bits,
                                              Aes128Key key,
                                              Aes128CtrCounter counter) {
  std::vector<std::uint8_t> keystream((bits.size() + 7U) / 8U, 0U);
  Aes128CtrKeystream stream(key, counter);
  stream.generate(keystream);

  std::vector<std::uint8_t> out(bits.size());
  for (std::size_t i = 0; i < bits.size(); ++i) {
    out[i] = static_cast<std::uint8_t>((bits[i] & 1U) ^ keystream_bit(keystream, i));
  }
  return out;
}

std::vector<SoftBit> aes128_ctr_descramble_soft_bits(std::span<const SoftBit> bits,
                                                     Aes128Key key,
                                                     Aes128CtrCounter counter) {
  std::vector<std::uint8_t> keystream((bits.size() + 7U) / 8U, 0U);
  Aes128CtrKeystream stream(key, counter);
  stream.generate(keystream);

  std::vector<SoftBit> out(bits.begin(), bits.end());
  for (std::size_t i = 0; i < out.size(); ++i) {
    out[i].value = static_cast<std::uint8_t>((out[i].value & 1U) ^ keystream_bit(keystream, i));
  }
  return out;
}

std::vector<SoftBit> hard_bits_to_soft(std::span<const std::uint8_t> bits, float confidence) {
  std::vector<SoftBit> soft;
  soft.reserve(bits.size());
  for (const auto bit : bits) {
    soft.push_back({.value = static_cast<std::uint8_t>(bit & 1U),
                    .certain = confidence > 0.0F,
                    .confidence = confidence});
  }
  return soft;
}

ConvolutionalLatencyEstimate estimate_convolutional_latency(std::size_t input_bytes,
                                                            std::uint8_t bits_per_qam_symbol,
                                                            double symbol_rate_hz,
                                                            const PuncturedConvolutionalCodeConfig& config) {
  validate(config);
  if (bits_per_qam_symbol == 0U) {
    throw std::invalid_argument("bits_per_qam_symbol must be positive");
  }
  if (!std::isfinite(symbol_rate_hz) || symbol_rate_hz <= 0.0) {
    throw std::invalid_argument("symbol_rate_hz must be positive");
  }

  const auto input_bits = input_bytes * 8U;
  const auto coded_bits = convolutional_coded_bits_for_input_bits(input_bits, config);
  const auto qam_symbols = (coded_bits + bits_per_qam_symbol - 1U) / bits_per_qam_symbol;
  const auto airtime = static_cast<double>(qam_symbols) / symbol_rate_hz;

  return {.input_bytes = input_bytes,
          .input_bits = input_bits,
          .coded_bits = coded_bits,
          .qam_symbols = qam_symbols,
          .symbol_rate_hz = symbol_rate_hz,
          .coded_airtime_seconds = airtime,
          .encode_decode_latency_seconds = 2.0 * airtime,
          .effective_code_rate = coded_bits == 0U ? 0.0 : static_cast<double>(input_bits) / coded_bits};
}

} // namespace wbhf_modem
