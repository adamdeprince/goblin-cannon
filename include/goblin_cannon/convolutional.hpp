#pragma once

#include "goblin_cannon/crypto.hpp"
#include "goblin_cannon/modem.hpp"

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace goblin_cannon {

struct PuncturedConvolutionalCodeConfig {
  std::uint8_t constraint_length = 7;
  std::uint32_t generator0 = 0171;
  std::uint32_t generator1 = 0133;
  std::vector<std::uint8_t> puncture_pattern = {1, 1};
  float decoded_bit_confidence_threshold = 0.20F;

  [[nodiscard]] static PuncturedConvolutionalCodeConfig rate_1_2();
  [[nodiscard]] static PuncturedConvolutionalCodeConfig rate_2_3();
  [[nodiscard]] static PuncturedConvolutionalCodeConfig rate_3_4();
};

void validate(const PuncturedConvolutionalCodeConfig& config);

struct ViterbiDecodeResult {
  std::vector<SoftBit> bits;
  std::vector<Token> bytes;
  std::size_t consumed_soft_bits = 0;
  float path_metric = 0.0F;
};

class PuncturedConvolutionalEncoder {
public:
  explicit PuncturedConvolutionalEncoder(PuncturedConvolutionalCodeConfig config = {});

  [[nodiscard]] const PuncturedConvolutionalCodeConfig& config() const noexcept { return config_; }
  [[nodiscard]] std::vector<std::uint8_t> push_bit(std::uint8_t bit);
  [[nodiscard]] std::vector<std::uint8_t> push_bytes(std::span<const std::uint8_t> bytes);
  // Alloc-free hot-path variants: append coded bits to the caller's buffer
  // instead of allocating a fresh vector per call.
  void push_bit_append(std::uint8_t bit, std::vector<std::uint8_t>& out);
  void push_bytes_append(std::span<const std::uint8_t> bytes, std::vector<std::uint8_t>& out);
  void reset() noexcept;

private:
  PuncturedConvolutionalCodeConfig config_;
  std::uint32_t shift_register_ = 0;
  std::size_t mother_bit_index_ = 0;
};

class SoftViterbiDecoder {
public:
  explicit SoftViterbiDecoder(PuncturedConvolutionalCodeConfig config = {});

  [[nodiscard]] const PuncturedConvolutionalCodeConfig& config() const noexcept { return config_; }
  [[nodiscard]] ViterbiDecodeResult decode(std::span<const SoftBit> coded_bits,
                                           std::size_t output_bits) const;
  [[nodiscard]] ViterbiDecodeResult decode_bytes(std::span<const SoftBit> coded_bits,
                                                 std::size_t output_bytes) const;

private:
  PuncturedConvolutionalCodeConfig config_;
};

class StreamingSoftViterbiDecoder {
public:
  explicit StreamingSoftViterbiDecoder(PuncturedConvolutionalCodeConfig config = {},
                                       std::size_t traceback_bits = 0);

  [[nodiscard]] const PuncturedConvolutionalCodeConfig& config() const noexcept { return config_; }
  [[nodiscard]] std::vector<Token> push(std::span<const SoftBit> coded_bits);
  // Alloc-free hot-path variant: appends produced tokens to caller buffer.
  void push_append(std::span<const SoftBit> coded_bits, std::vector<Token>& out);
  void reset();

private:
  struct Decision {
    std::uint16_t previous_state = 0;
    std::uint8_t bit = 0;
    float confidence = 0.0F;
    bool valid = false;
  };

  [[nodiscard]] std::size_t observations_required_for_next_bit() const noexcept;
  void process_bit(std::span<const SoftBit> observations);
  void emit_ready_bytes(std::vector<Token>& out);
  [[nodiscard]] std::size_t history_steps_in_flight() const noexcept {
    return history_step_count_ - history_emitted_count_;
  }
  [[nodiscard]] Decision& history_row(std::size_t step, std::size_t state) noexcept {
    return history_storage_[(step % history_capacity_) * states_ + state];
  }
  [[nodiscard]] const Decision& history_row(std::size_t step, std::size_t state) const noexcept {
    return history_storage_[(step % history_capacity_) * states_ + state];
  }

  PuncturedConvolutionalCodeConfig config_;
  std::size_t traceback_bits_ = 0;
  std::uint32_t states_ = 0;
  std::uint32_t state_mask_ = 0;
  std::uint32_t full_mask_ = 0;
  std::size_t mother_bit_index_ = 0;
  std::vector<SoftBit> pending_;
  std::size_t pending_head_ = 0;
  std::vector<float> metrics_;
  std::vector<float> next_metrics_;
  // Flat preallocated history: history_storage_[(step % history_capacity_) * states_ + state].
  std::vector<Decision> history_storage_;
  std::size_t history_capacity_ = 0;
  std::size_t history_step_count_ = 0;
  std::size_t history_emitted_count_ = 0;
  // Scratch traceback buffer to avoid per-emit allocation.
  std::vector<SoftBit> traceback_bits_buffer_;
};

class Aes128CtrBitXor {
public:
  explicit Aes128CtrBitXor(Aes128Key key, Aes128CtrCounter counter = {});

  [[nodiscard]] std::uint8_t xor_bit(std::uint8_t bit);
  [[nodiscard]] SoftBit xor_soft_bit(SoftBit bit);
  [[nodiscard]] std::vector<std::uint8_t> xor_bits(std::span<const std::uint8_t> bits);
  [[nodiscard]] std::vector<SoftBit> xor_soft_bits(std::span<const SoftBit> bits);
  // Alloc-free in-place XOR for the hot path.
  void xor_bits_in_place(std::span<std::uint8_t> bits);

private:
  // Refills the keystream buffer in one EVP call, then serves bits/bytes
  // from the buffer. Amortizes ~64x the per-byte OpenSSL crossing.
  static constexpr std::size_t keystream_buffer_bytes = 64;
  [[nodiscard]] std::uint8_t next_keystream_bit();
  void refill_keystream_byte();

  Aes128CtrKeystream stream_;
  std::array<std::uint8_t, keystream_buffer_bytes> keystream_buffer_{};
  std::size_t keystream_buffer_pos_ = keystream_buffer_bytes;  // start empty
  std::uint8_t current_byte_ = 0;
  std::uint8_t remaining_bits_ = 0;
};

[[nodiscard]] std::vector<std::uint8_t> convolutional_encode_bytes(
    std::span<const std::uint8_t> bytes,
    const PuncturedConvolutionalCodeConfig& config = {});

[[nodiscard]] std::size_t convolutional_coded_bits_for_input_bits(
    std::size_t input_bits,
    const PuncturedConvolutionalCodeConfig& config = {});

[[nodiscard]] std::size_t convolutional_coded_bits_for_input_bytes(
    std::size_t input_bytes,
    const PuncturedConvolutionalCodeConfig& config = {});

[[nodiscard]] std::vector<std::uint8_t> aes128_ctr_xor_bits(std::span<const std::uint8_t> bits,
                                                            Aes128Key key,
                                                            Aes128CtrCounter counter = {});

[[nodiscard]] std::vector<SoftBit> aes128_ctr_descramble_soft_bits(std::span<const SoftBit> bits,
                                                                   Aes128Key key,
                                                                   Aes128CtrCounter counter = {});

[[nodiscard]] std::vector<SoftBit> hard_bits_to_soft(std::span<const std::uint8_t> bits,
                                                     float confidence = 1.0F);

struct ConvolutionalLatencyEstimate {
  std::size_t input_bytes = 0;
  std::size_t input_bits = 0;
  std::size_t coded_bits = 0;
  std::size_t qam_symbols = 0;
  double symbol_rate_hz = 0.0;
  double coded_airtime_seconds = 0.0;
  double encode_decode_latency_seconds = 0.0;
  double effective_code_rate = 0.0;
};

[[nodiscard]] ConvolutionalLatencyEstimate estimate_convolutional_latency(
    std::size_t input_bytes,
    std::uint8_t bits_per_qam_symbol,
    double symbol_rate_hz,
    const PuncturedConvolutionalCodeConfig& config = {});

} // namespace goblin_cannon
