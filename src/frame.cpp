#include "wbhf_modem/modem.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <cmath>
#include <stdexcept>

namespace wbhf_modem {

namespace {

constexpr std::uint32_t sync_word = 0xD391A6C5U;
constexpr std::size_t no_locked_branch = static_cast<std::size_t>(-1);

bool terminal_status(FrameStatus status) {
  return status == FrameStatus::frame_complete ||
         status == FrameStatus::protocol_error;
}

void set_status(FrameDecodeResult& result, FrameStatus status) {
  if (!terminal_status(result.status)) {
    result.status = status;
  }
}

void append_u32_be(std::vector<std::uint8_t>& out, std::uint32_t value) {
  out.push_back(static_cast<std::uint8_t>((value >> 24U) & 0xFFU));
  out.push_back(static_cast<std::uint8_t>((value >> 16U) & 0xFFU));
  out.push_back(static_cast<std::uint8_t>((value >> 8U) & 0xFFU));
  out.push_back(static_cast<std::uint8_t>(value & 0xFFU));
}

} // namespace

FrameEncoder::FrameEncoder(FrameConfig config)
    : config_(std::move(config)), encoder_(config_.modem) {
  validate(config_.modem);
  if (config_.preamble_bytes < 8) {
    throw std::invalid_argument("preamble_bytes must be at least 8");
  }
  if (config_.max_payload_bytes == 0) {
    throw std::invalid_argument("max_payload_bytes must be positive");
  }
  if (config_.sync_max_bit_errors > 8) {
    throw std::invalid_argument("sync_max_bit_errors must be <= 8");
  }
}

bool FrameEncoder::active() const noexcept {
  return state_ != TxState::idle && state_ != TxState::complete;
}

std::uint32_t FrameEncoder::remaining_payload_bytes() const noexcept {
  if (continuous_stream_) {
    return 0;
  }
  return payload_expected_ - payload_consumed_;
}

void FrameEncoder::start_frame(std::uint32_t payload_bytes) {
  if (active()) {
    throw std::logic_error("frame encoder is already active");
  }
  if (payload_bytes > config_.max_payload_bytes) {
    throw std::invalid_argument("payload exceeds max_payload_bytes");
  }
  reset();
  continuous_stream_ = false;
  payload_expected_ = payload_bytes;
  queue_header(payload_bytes);
  state_ = TxState::control;
}

void FrameEncoder::start_stream() {
  if (active()) {
    throw std::logic_error("frame encoder is already active");
  }
  reset();
  continuous_stream_ = true;
  queue_header(std::nullopt);
  state_ = TxState::control;
}

FrameEncodeResult FrameEncoder::push_payload(std::span<const std::uint8_t> payload, std::span<Complex> out) {
  return pump(payload, out);
}

FrameEncodeResult FrameEncoder::push_tokens(std::span<const std::uint8_t> tokens, std::span<Complex> out) {
  return pump(tokens, out);
}

FrameEncodeResult FrameEncoder::drain(std::span<Complex> out) {
  if (continuous_stream_ && active()) {
    closing_stream_ = true;
  }
  return pump({}, out);
}

void FrameEncoder::reset() {
  encoder_.reset();
  state_ = TxState::idle;
  control_.clear();
  control_offset_ = 0;
  continuous_stream_ = false;
  closing_stream_ = false;
  payload_expected_ = 0;
  payload_consumed_ = 0;
}

FrameEncodeResult FrameEncoder::pump(std::span<const std::uint8_t> payload, std::span<Complex> out) {
  FrameEncodeResult result{.status = active() ? FrameStatus::transmitting : FrameStatus::idle};
  std::size_t payload_offset = 0;

  while (result.produced_samples < out.size()) {
    const auto remaining_out = out.subspan(result.produced_samples);

    if (state_ == TxState::idle || state_ == TxState::complete) {
      result.status = state_ == TxState::complete ? FrameStatus::complete : FrameStatus::idle;
      break;
    }

    if (state_ == TxState::control) {
      if (control_offset_ < control_.size()) {
        const auto byte_span = std::span<const std::uint8_t>(&control_[control_offset_], 1);
        const auto r = encoder_.push_bytes(byte_span, remaining_out);
        result.produced_samples += r.produced;
        control_offset_ += r.consumed;
        if (r.produced == 0 && r.consumed == 0) {
          break;
        }
        continue;
      }
      control_.clear();
      control_offset_ = 0;
      state_ = TxState::payload;
      continue;
    }

    if (state_ == TxState::payload) {
      if (continuous_stream_) {
        if (payload_offset < payload.size()) {
          const auto byte_span = std::span<const std::uint8_t>(&payload[payload_offset], 1);
          const auto r = encoder_.push_bytes(byte_span, remaining_out);
          result.produced_samples += r.produced;
          if (r.consumed != 0) {
            ++payload_offset;
            ++result.consumed_payload_bytes;
          }
          if (r.produced == 0 && r.consumed == 0) {
            break;
          }
          continue;
        }
        if (closing_stream_) {
          state_ = TxState::draining;
          continue;
        }
        result.status = FrameStatus::transmitting;
        break;
      }

      if (payload_consumed_ < payload_expected_) {
        if (payload_offset >= payload.size()) {
          result.status = FrameStatus::transmitting;
          break;
        }
        const auto byte_span = std::span<const std::uint8_t>(&payload[payload_offset], 1);
        const auto r = encoder_.push_bytes(byte_span, remaining_out);
        result.produced_samples += r.produced;
        if (r.consumed != 0) {
          ++payload_offset;
          ++payload_consumed_;
          ++result.consumed_payload_bytes;
        }
        if (payload_consumed_ == payload_expected_) {
          state_ = TxState::draining;
        }
        if (r.produced == 0 && r.consumed == 0) {
          break;
        }
        continue;
      }
      state_ = TxState::draining;
      continue;
    }

    if (state_ == TxState::draining) {
      const auto r = encoder_.drain(remaining_out);
      result.produced_samples += r.produced;
      if (r.produced == 0) {
        state_ = TxState::complete;
        result.status = FrameStatus::complete;
        break;
      }
      continue;
    }
  }

  if (state_ == TxState::complete) {
    result.status = FrameStatus::complete;
  } else if (active()) {
    result.status = FrameStatus::transmitting;
  }
  return result;
}

void FrameEncoder::queue_header(std::optional<std::uint32_t> payload_bytes) {
  control_.assign(config_.preamble_bytes, 0x55U);
  append_u32_be(control_, sync_word);
  if (payload_bytes.has_value()) {
    append_u32_be(control_, *payload_bytes);
  }
  control_offset_ = 0;
}

FrameDecoder::TimingBranch::TimingBranch(ModemConfig modem, double timing_offset_symbols)
    : decoder(std::move(modem), timing_offset_symbols) {}

FrameDecoder::FrameDecoder(FrameConfig config)
    : config_(std::move(config)),
      preroll_(config_.carrier.preroll_samples == 0 ? 1 : config_.carrier.preroll_samples) {
  validate(config_.modem);
  if (config_.max_payload_bytes == 0) {
    throw std::invalid_argument("max_payload_bytes must be positive");
  }
  if (config_.sync_max_bit_errors > 8) {
    throw std::invalid_argument("sync_max_bit_errors must be <= 8");
  }
  branches_.reserve(config_.modem.receiver_oversampling);
  for (std::uint8_t phase = 0; phase < config_.modem.receiver_oversampling; ++phase) {
    branches_.emplace_back(config_.modem,
                           static_cast<double>(phase) / static_cast<double>(config_.modem.receiver_oversampling));
  }
}

FrameDecodeResult FrameDecoder::push_samples(std::span<const Complex> samples, std::span<std::uint8_t> out_payload) {
  std::vector<Token> tokens(out_payload.size());
  auto result = push_samples(samples, std::span<Token>(tokens));
  for (std::size_t i = 0; i < result.produced_payload_bytes; ++i) {
    out_payload[i] = tokens[i].value;
  }
  return result;
}

FrameDecodeResult FrameDecoder::push_samples(std::span<const Complex> samples, std::span<Token> out_tokens) {
  FrameDecodeResult result{.consumed_samples = 0,
                           .produced_payload_bytes = 0,
                           .status = carrier_present_ ? FrameStatus::receiving : FrameStatus::idle,
                           .carrier_present = carrier_present_};
  std::array<SoftBit, 64> bit_buffer{};

  for (const auto sample : samples) {
    const bool was_present = carrier_present_;
    update_carrier(sample);
    result.carrier_present = carrier_present_;
    ++result.consumed_samples;

    if (!was_present && carrier_present_) {
      result.status = FrameStatus::carrier_detected;
      for (auto& branch : branches_) {
        branch.decoder.reset();
      }
      reset_frame_parser();
      const auto preroll_count = preroll_full_ ? preroll_.size() : preroll_write_;
      const auto preroll_start = preroll_full_ ? preroll_write_ : 0U;
      if (preroll_count != 0) {
        std::size_t first_signal = 0;
        const float threshold = std::max(config_.carrier.close_threshold, config_.carrier.open_threshold * 0.25F);
        while (first_signal + 1U < preroll_count) {
          const auto idx = (preroll_start + first_signal) % preroll_.size();
          if (std::norm(preroll_[idx]) >= threshold) {
            break;
          }
          ++first_signal;
        }
        for (std::size_t n = first_signal; n < preroll_count; ++n) {
          const auto idx = (preroll_start + n) % preroll_.size();
          if (!push_sample_to_branches(preroll_[idx], out_tokens, result, bit_buffer)) {
            return result;
          }
        }
      }
    }

    if (!carrier_present_) {
      preroll_[preroll_write_] = sample;
      preroll_write_ = (preroll_write_ + 1U) % preroll_.size();
      preroll_full_ = preroll_full_ || preroll_write_ == 0;
      if (was_present) {
        reset_frame_parser();
        for (auto& branch : branches_) {
          branch.decoder.reset();
        }
        if (!terminal_status(result.status)) {
          result.status = FrameStatus::idle;
        }
      }
      continue;
    }

    if (!push_sample_to_branches(sample, out_tokens, result, bit_buffer)) {
      return result;
    }
  }

  result.carrier_present = carrier_present_;
  return result;
}

void FrameDecoder::reset() {
  for (auto& branch : branches_) {
    branch.decoder.reset();
  }
  reset_frame_parser();
  carrier_present_ = false;
  attack_count_ = 0;
  release_count_ = 0;
  energy_ = 0.0F;
  preroll_write_ = 0;
  preroll_full_ = false;
}

void FrameDecoder::reset_frame_parser() {
  locked_branch_ = no_locked_branch;
  for (std::size_t branch = 0; branch < branches_.size(); ++branch) {
    reset_branch_parser(branch);
  }
}

void FrameDecoder::reset_branch_parser(std::size_t branch_index) {
  auto& branch = branches_[branch_index];
  branch.state = RxState::searching_sync;
  branch.sync_shift = 0;
  branch.sync_bits = 0;
  branch.current_byte = 0;
  branch.current_byte_bits = 0;
  branch.current_byte_certain = true;
  branch.current_byte_confidence = 1.0F;
  branch.length = 0;
  branch.length_shift = 0;
  branch.payload_received = 0;
  branch.pending_payload = 0;
  branch.pending_payload_certain = true;
  branch.pending_payload_confidence = 1.0F;
  branch.has_pending_payload = false;
}

bool FrameDecoder::push_sample_to_branches(Complex sample,
                                           std::span<Token> out_payload,
                                           FrameDecodeResult& result,
                                           std::span<SoftBit> bit_buffer) {
  if (locked_branch_ != no_locked_branch) {
    const auto branch_index = locked_branch_;
    if (!flush_pending_payload(branch_index, out_payload, result)) {
      return false;
    }
    auto& branch = branches_[branch_index];
    const auto r = branch.decoder.push_samples_soft(std::span<const Complex>(&sample, 1), bit_buffer);
    for (std::size_t i = 0; i < r.produced_bits; ++i) {
      if (!push_branch_bit(branch_index, bit_buffer[i], out_payload, result)) {
        return false;
      }
    }
    return true;
  }

  for (std::size_t branch_index = 0; branch_index < branches_.size(); ++branch_index) {
    auto& branch = branches_[branch_index];
    const auto r = branch.decoder.push_samples_soft(std::span<const Complex>(&sample, 1), bit_buffer);
    for (std::size_t i = 0; i < r.produced_bits; ++i) {
      if (!push_branch_bit(branch_index, bit_buffer[i], out_payload, result)) {
        return false;
      }
      if (locked_branch_ != no_locked_branch && locked_branch_ != branch_index) {
        break;
      }
    }
    if (locked_branch_ != no_locked_branch) {
      break;
    }
  }

  return true;
}

bool FrameDecoder::push_branch_bit(std::size_t branch_index,
                                   SoftBit bit,
                                   std::span<Token> out_payload,
                                   FrameDecodeResult& result) {
  if (!flush_pending_payload(branch_index, out_payload, result)) {
    return false;
  }
  auto& branch = branches_[branch_index];
  if (branch.state == RxState::searching_sync) {
    branch.sync_shift = (branch.sync_shift << 1U) | (bit.value & 1U);
    branch.sync_bits = std::min<std::uint8_t>(32, static_cast<std::uint8_t>(branch.sync_bits + 1U));
    if (branch.sync_bits == 32 &&
        std::popcount(branch.sync_shift ^ sync_word) <= config_.sync_max_bit_errors) {
      locked_branch_ = branch_index;
      branch.current_byte = 0;
      branch.current_byte_bits = 0;
      branch.current_byte_certain = true;
      branch.current_byte_confidence = 1.0F;
      branch.state = config_.continuous_stream ? RxState::payload : RxState::length;
      branch.length = 0;
      branch.length_shift = 0;
      set_status(result, FrameStatus::receiving);
    }
    return true;
  }

  branch.current_byte = static_cast<std::uint8_t>((branch.current_byte << 1U) | (bit.value & 1U));
  branch.current_byte_certain = branch.current_byte_certain && bit.certain;
  branch.current_byte_confidence = std::min(branch.current_byte_confidence, bit.confidence);
  ++branch.current_byte_bits;
  if (branch.current_byte_bits != 8U) {
    return true;
  }

  const auto byte = branch.current_byte;
  const bool certain = branch.current_byte_certain;
  const float confidence = branch.current_byte_confidence;
  branch.current_byte = 0;
  branch.current_byte_bits = 0;
  branch.current_byte_certain = true;
  branch.current_byte_confidence = 1.0F;
  return push_branch_byte(branch_index, byte, certain, confidence, out_payload, result);
}

bool FrameDecoder::push_branch_byte(std::size_t branch_index,
                                    std::uint8_t byte,
                                    bool certain,
                                    float confidence,
                                    std::span<Token> out_payload,
                                    FrameDecodeResult& result) {
  if (!flush_pending_payload(branch_index, out_payload, result)) {
    return false;
  }
  auto& branch = branches_[branch_index];
  switch (branch.state) {
  case RxState::searching_sync:
    return true;

  case RxState::length:
    branch.length = (branch.length << 8U) | byte;
    ++branch.length_shift;
    if (branch.length_shift == 4U) {
      if (branch.length > config_.max_payload_bytes) {
        result.status = FrameStatus::protocol_error;
        reset_frame_parser();
        return true;
      }
      branch.payload_received = 0;
      if (branch.length == 0) {
        result.status = FrameStatus::frame_complete;
        reset_frame_parser();
      } else {
        branch.state = RxState::payload;
      }
    }
    return true;

  case RxState::payload:
    return emit_payload_byte(branch_index, byte, certain, confidence, out_payload, result);
  }
  return true;
}

bool FrameDecoder::emit_payload_byte(std::size_t branch_index,
                                     std::uint8_t byte,
                                     bool certain,
                                     float confidence,
                                     std::span<Token> out_payload,
                                     FrameDecodeResult& result) {
  auto& branch = branches_[branch_index];
  if (result.produced_payload_bytes >= out_payload.size()) {
    branch.pending_payload = byte;
    branch.pending_payload_certain = certain;
    branch.pending_payload_confidence = confidence;
    branch.has_pending_payload = true;
    return false;
  }
  out_payload[result.produced_payload_bytes++] = {.value = byte, .certain = certain, .confidence = confidence};
  ++branch.payload_received;
  if (!config_.continuous_stream && branch.payload_received == branch.length) {
    result.status = FrameStatus::frame_complete;
    reset_frame_parser();
  } else {
    set_status(result, FrameStatus::receiving);
  }
  return true;
}

bool FrameDecoder::flush_pending_payload(std::size_t branch_index,
                                         std::span<Token> out_payload,
                                         FrameDecodeResult& result) {
  auto& branch = branches_[branch_index];
  if (!branch.has_pending_payload) {
    return true;
  }
  const auto byte = branch.pending_payload;
  const bool certain = branch.pending_payload_certain;
  const float confidence = branch.pending_payload_confidence;
  branch.pending_payload = 0;
  branch.pending_payload_certain = true;
  branch.pending_payload_confidence = 1.0F;
  branch.has_pending_payload = false;
  return emit_payload_byte(branch_index, byte, certain, confidence, out_payload, result);
}

void FrameDecoder::update_carrier(Complex sample) {
  const float p = std::norm(sample);
  energy_ = 0.98F * energy_ + 0.02F * p;

  if (!carrier_present_) {
    if (energy_ >= config_.carrier.open_threshold) {
      ++attack_count_;
      if (attack_count_ >= config_.carrier.attack_samples) {
        carrier_present_ = true;
        release_count_ = 0;
      }
    } else {
      attack_count_ = 0;
    }
    return;
  }

  if (energy_ <= config_.carrier.close_threshold) {
    ++release_count_;
    if (release_count_ >= config_.carrier.release_samples) {
      carrier_present_ = false;
      attack_count_ = 0;
    }
  } else {
    release_count_ = 0;
  }
}

} // namespace wbhf_modem
