#include "goblin_cannon/convolutional.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>
#include <utility>

namespace goblin_cannon {

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
                    std::span<const std::uint8_t> expected,
                    float& confidence) {
  float metric = 0.0F;
  float confidence_sum = 0.0F;
  std::size_t confidence_count = 0;

  for (const auto& observation : observations) {
    const auto wanted = expected[observation.mother_index];
    if (std::isfinite(observation.bit.log_likelihood_ratio)) {
      const auto llr = observation.bit.log_likelihood_ratio;
      // A bitwise log-likelihood branch cost, up to a branch-independent constant.
      metric += ((llr < 0) != (wanted != 0)) ? std::abs(llr) : 0.0F;
      confidence_sum += std::tanh(std::abs(llr) * 0.5F);
      ++confidence_count;
      continue;
    }
    if (!observation.bit.certain || observation.bit.confidence <= 0.0F) {
      continue;
    }
    const auto clamped = std::clamp(observation.bit.confidence, 0.0F, 1.0F);
    confidence_sum += clamped;
    ++confidence_count;
    if ((observation.bit.value & 1U) != wanted) {
      metric += clamped;
    }
  }

  confidence = confidence_count == 0U ? 0.0F : confidence_sum / static_cast<float>(confidence_count);
  return metric;
}

std::size_t default_traceback_bits(const PuncturedConvolutionalCodeConfig& config) noexcept {
  return std::max<std::size_t>(5U * config.constraint_length, 24U);
}

void validate_streaming_puncture_pattern(const PuncturedConvolutionalCodeConfig& config) {
  const auto outputs = config.mother_outputs();
  const auto period = config.puncture_pattern.size() / std::gcd(config.puncture_pattern.size(), outputs);
  for (std::size_t step = 0; step < period; ++step) {
    bool kept = false;
    for (std::size_t i = 0; i < outputs; ++i)
      kept = kept || config.puncture_pattern[(step * outputs + i) % config.puncture_pattern.size()] != 0;
    if (!kept) throw std::invalid_argument("streaming Viterbi requires each input bit to retain at least one coded bit");
  }
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

PuncturedConvolutionalCodeConfig PuncturedConvolutionalCodeConfig::k9_rate_1_2() {
  auto config = rate_1_2();
  config.constraint_length = 9;
  config.generator0 = 0753;
  config.generator1 = 0561;
  return config;
}

PuncturedConvolutionalCodeConfig PuncturedConvolutionalCodeConfig::k9_rate_1_3() {
  auto config = k9_rate_1_2();
  config.generator0 = 0557;
  config.generator1 = 0663;
  config.generator2 = 0711;
  config.puncture_pattern = {1, 1, 1};
  return config;
}

void validate(const PuncturedConvolutionalCodeConfig& config) {
  if (config.constraint_length < 3U || config.constraint_length > 12U) {
    throw std::invalid_argument("constraint_length must be in [3, 12]");
  }
  if (config.generator0 == 0U || config.generator1 == 0U) {
    throw std::invalid_argument("convolutional generators must be non-zero");
  }
  const auto mask = (1U << config.constraint_length) - 1U;
  if ((config.generator0 | config.generator1 | config.generator2) & ~mask)
    throw std::invalid_argument("convolutional generator exceeds constraint length");
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

void PuncturedConvolutionalEncoder::push_bit_append(std::uint8_t bit, std::vector<std::uint8_t>& out) {
  const auto full_mask = (1U << config_.constraint_length) - 1U;
  shift_register_ = ((shift_register_ << 1U) | (bit & 1U)) & full_mask;
  const std::array generators{config_.generator0, config_.generator1, config_.generator2};
  for (std::size_t i = 0; i < config_.mother_outputs(); ++i) {
    if (config_.puncture_pattern[mother_bit_index_ % config_.puncture_pattern.size()])
      out.push_back(parity(shift_register_ & generators[i]));
    ++mother_bit_index_;
  }
}

void PuncturedConvolutionalEncoder::push_bytes_append(std::span<const std::uint8_t> bytes,
                                                      std::vector<std::uint8_t>& out) {
  out.reserve(out.size() + bytes.size() * config_.mother_outputs() * 8U);
  for (const auto byte : bytes) {
    for (int bit_index = 7; bit_index >= 0; --bit_index) {
      push_bit_append(static_cast<std::uint8_t>((byte >> bit_index) & 1U), out);
    }
  }
}

std::vector<std::uint8_t> PuncturedConvolutionalEncoder::push_bit(std::uint8_t bit) {
  std::vector<std::uint8_t> out;
  out.reserve(config_.mother_outputs());
  push_bit_append(bit, out);
  return out;
}

std::vector<std::uint8_t> PuncturedConvolutionalEncoder::push_bytes(std::span<const std::uint8_t> bytes) {
  std::vector<std::uint8_t> out;
  push_bytes_append(bytes, out);
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
    std::array<Observation, 3> observation_storage{};
    std::size_t observation_count = 0;
    for (std::uint8_t mother = 0; mother < config_.mother_outputs(); ++mother) {
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
        const std::array expected{parity(reg & config_.generator0), parity(reg & config_.generator1), parity(reg & config_.generator2)};
        float confidence = 0.0F;
        const auto metric = branch_metric(observations, expected, confidence);
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

StreamingSoftViterbiDecoder::StreamingSoftViterbiDecoder(PuncturedConvolutionalCodeConfig config,
                                                         std::size_t traceback_bits)
    : config_(std::move(config)),
      traceback_bits_(traceback_bits == 0U ? default_traceback_bits(config_) : traceback_bits),
      states_(1U << (config_.constraint_length - 1U)),
      state_mask_(states_ - 1U),
      full_mask_((1U << config_.constraint_length) - 1U) {
  validate(config_);
  validate_streaming_puncture_pattern(config_);
  if (traceback_bits_ < 8U) {
    throw std::invalid_argument("streaming Viterbi traceback_bits must be at least 8");
  }
  // History needs to hold up to traceback_bits_ + 8 steps before emit; pad
  // one byte's worth to give emit_ready_bytes headroom.
  history_capacity_ = traceback_bits_ + 16U;
  history_storage_.assign(history_capacity_ * states_, Decision{});
  traceback_bits_buffer_.assign(history_capacity_, SoftBit{});
  reset();
}

void StreamingSoftViterbiDecoder::reset() {
  constexpr float inf = std::numeric_limits<float>::infinity();
  mother_bit_index_ = 0;
  resume_discard_bytes_ = 0;
  pending_.clear();
  pending_head_ = 0;
  metrics_.assign(states_, inf);
  next_metrics_.assign(states_, inf);
  metrics_[0] = 0.0F;
  // Reset history bookkeeping but keep the preallocated storage.
  history_step_count_ = 0;
  history_emitted_count_ = 0;
}

std::size_t StreamingSoftViterbiDecoder::resume_at_coded_bit(std::uint64_t offset) {
  reset();
  const auto period = std::lcm<std::uint64_t>(8U * config_.mother_outputs(), config_.puncture_pattern.size());
  const auto kept = std::count_if(config_.puncture_pattern.begin(), config_.puncture_pattern.end(),
                                  [](auto bit) { return bit != 0; });
  const auto coded_period = period / config_.puncture_pattern.size() * kept;
  const auto remainder = offset % coded_period;
  std::size_t mother = 0, coded = 0;
  while (coded < remainder) {
    for (std::size_t i = 0; i < 8U * config_.mother_outputs(); ++i, ++mother)
      coded += config_.puncture_pattern[mother % config_.puncture_pattern.size()] != 0;
  }
  mother_bit_index_ = mother % config_.puncture_pattern.size();
  std::fill(metrics_.begin(), metrics_.end(), 0.0F); // unknown encoder history
  resume_discard_bytes_ = (config_.constraint_length - 1U + 7U) / 8U;
  return coded - remainder;
}

std::size_t StreamingSoftViterbiDecoder::observations_required_for_next_bit() const noexcept {
  std::size_t required = 0;
  for (std::uint8_t mother = 0; mother < config_.mother_outputs(); ++mother) {
    required += config_.puncture_pattern[(mother_bit_index_ + mother) % config_.puncture_pattern.size()] != 0U
                    ? 1U
                    : 0U;
  }
  return required;
}

void StreamingSoftViterbiDecoder::process_bit(std::span<const SoftBit> observations_in) {
  std::array<Observation, 3> observation_storage{};
  std::size_t index = 0;
  for (std::size_t mother = 0; mother < config_.mother_outputs(); ++mother) {
    if (config_.puncture_pattern[(mother_bit_index_ + mother) % config_.puncture_pattern.size()]) {
      observation_storage[index] = {.mother_index = static_cast<std::uint8_t>(mother), .bit = observations_in[index]};
      ++index;
    }
  }

  constexpr float inf = std::numeric_limits<float>::infinity();
  std::fill(next_metrics_.begin(), next_metrics_.end(), inf);

  // Write decisions directly into the preallocated history slot for this step.
  const auto step = history_step_count_;
  Decision* const decisions = &history_storage_[(step % history_capacity_) * states_];
  for (std::size_t s = 0; s < states_; ++s) {
    decisions[s] = Decision{};
  }

  const auto observations = std::span<const Observation>(observation_storage).first(observations_in.size());
  for (std::uint32_t previous = 0; previous < states_; ++previous) {
    if (!std::isfinite(metrics_[previous])) {
      continue;
    }
    for (std::uint8_t bit = 0; bit < 2U; ++bit) {
      const auto reg = ((previous << 1U) | bit) & full_mask_;
      const auto next_state = reg & state_mask_;
      const std::array expected{parity(reg & config_.generator0), parity(reg & config_.generator1), parity(reg & config_.generator2)};
      float confidence = 0.0F;
      const auto metric = branch_metric(observations, expected, confidence);
      const auto candidate = metrics_[previous] + metric;
      if (candidate < next_metrics_[next_state]) {
        next_metrics_[next_state] = candidate;
        decisions[next_state] = {.previous_state = static_cast<std::uint16_t>(previous),
                                 .bit = bit,
                                 .confidence = confidence,
                                 .valid = true};
      }
    }
  }

  metrics_.swap(next_metrics_);
  const auto best = std::min_element(metrics_.begin(), metrics_.end());
  if (best != metrics_.end() && std::isfinite(*best) && *best > 1024.0F) {
    const auto offset = *best;
    for (auto& metric : metrics_) {
      if (std::isfinite(metric)) {
        metric -= offset;
      }
    }
  }
  ++history_step_count_;
  mother_bit_index_ += config_.mother_outputs();
}

void StreamingSoftViterbiDecoder::emit_ready_bytes(std::vector<Token>& out) {
  while (history_steps_in_flight() >= traceback_bits_ + 8U) {
    const auto best = std::min_element(metrics_.begin(), metrics_.end());
    if (best == metrics_.end() || !std::isfinite(*best)) {
      throw std::runtime_error("streaming Viterbi decoder could not find a valid path");
    }

    auto state = static_cast<std::uint32_t>(std::distance(metrics_.begin(), best));
    const auto in_flight = history_steps_in_flight();
    // Traceback walks from the most recent step (history_step_count_ - 1) down
    // to history_emitted_count_, writing into the scratch buffer. We only emit
    // bytes from the oldest 8 of these steps below.
    for (std::size_t i = in_flight; i-- > 0U;) {
      const auto step = history_emitted_count_ + i;
      const auto& decision = history_row(step, state);
      if (!decision.valid) {
        throw std::runtime_error("streaming Viterbi traceback encountered an invalid decision");
      }
      traceback_bits_buffer_[i] = {.value = decision.bit,
                                   .certain = decision.confidence >= config_.decoded_bit_confidence_threshold,
                                   .confidence = decision.confidence};
      state = decision.previous_state;
    }

    std::uint8_t value = 0;
    bool certain = true;
    float confidence = 1.0F;
    for (std::size_t bit = 0; bit < 8U; ++bit) {
      const auto soft = traceback_bits_buffer_[bit];
      value = static_cast<std::uint8_t>((value << 1U) | (soft.value & 1U));
      confidence = std::min(confidence, soft.confidence);
      certain = certain && soft.certain && soft.confidence >= config_.decoded_bit_confidence_threshold;
    }
    if (resume_discard_bytes_) --resume_discard_bytes_;
    else out.push_back({.value = value, .certain = certain, .confidence = confidence});
    history_emitted_count_ += 8U;
  }
}

void StreamingSoftViterbiDecoder::push_append(std::span<const SoftBit> coded_bits,
                                              std::vector<Token>& out) {
  pending_.insert(pending_.end(), coded_bits.begin(), coded_bits.end());

  while (true) {
    const auto required = observations_required_for_next_bit();
    if (pending_.size() - pending_head_ < required) {
      break;
    }
    process_bit(std::span<const SoftBit>(pending_.data() + pending_head_, required));
    pending_head_ += required;
    emit_ready_bytes(out);
  }

  // Amortized compaction: only shift the residual when half (or more) of
  // the buffer is consumed. The per-bit cost remains O(1).
  if (pending_head_ > 0U && pending_head_ * 2U >= pending_.size()) {
    pending_.erase(pending_.begin(),
                   pending_.begin() + static_cast<std::ptrdiff_t>(pending_head_));
    pending_head_ = 0U;
  }
}

std::vector<Token> StreamingSoftViterbiDecoder::push(std::span<const SoftBit> coded_bits) {
  std::vector<Token> out;
  push_append(coded_bits, out);
  return out;
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
  for (std::size_t i = 0; i < input_bits * config.mother_outputs(); ++i) {
    coded_bits += config.puncture_pattern[i % config.puncture_pattern.size()] != 0U ? 1U : 0U;
  }
  return coded_bits;
}

std::size_t convolutional_coded_bits_for_input_bytes(std::size_t input_bytes,
                                                    const PuncturedConvolutionalCodeConfig& config) {
  return convolutional_coded_bits_for_input_bits(input_bytes * 8U, config);
}

Aes128CtrBitXor::Aes128CtrBitXor(Aes128Key key, Aes128CtrCounter counter, std::uint64_t bit_offset)
    : stream_(key, [&] {
        auto blocks = bit_offset / 128U;
        for (std::size_t i = counter.size(); i-- > 0;) {
          const auto sum = static_cast<std::uint16_t>(counter[i]) + (blocks & 0xffU);
          counter[i] = static_cast<std::uint8_t>(sum);
          blocks = (blocks >> 8U) + (sum >> 8U);
        }
        if (blocks) throw std::overflow_error("AES counter overflow while seeking");
        return counter;
      }()) {
  for (std::uint64_t i = 0; i < bit_offset % 128U; ++i) (void)next_keystream_bit();
}

void Aes128CtrBitXor::refill_keystream_byte() {
  if (keystream_buffer_pos_ >= keystream_buffer_.size()) {
    stream_.generate(keystream_buffer_);
    keystream_buffer_pos_ = 0;
  }
  current_byte_ = keystream_buffer_[keystream_buffer_pos_++];
  remaining_bits_ = 8U;
}

std::uint8_t Aes128CtrBitXor::next_keystream_bit() {
  if (remaining_bits_ == 0U) {
    refill_keystream_byte();
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
  const auto mask = next_keystream_bit();
  bit.value = (bit.value & 1U) ^ mask;
  if (mask) bit.log_likelihood_ratio = -bit.log_likelihood_ratio;
  return bit;
}

std::vector<std::uint8_t> Aes128CtrBitXor::xor_bits(std::span<const std::uint8_t> bits) {
  std::vector<std::uint8_t> out(bits.begin(), bits.end());
  xor_bits_in_place(out);
  return out;
}

void Aes128CtrBitXor::xor_bits_in_place(std::span<std::uint8_t> bits) {
  for (auto& bit : bits) {
    bit = static_cast<std::uint8_t>((bit & 1U) ^ next_keystream_bit());
  }
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

} // namespace goblin_cannon
