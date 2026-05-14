#pragma once

#include "wbhf_modem/crypto.hpp"
#include "wbhf_modem/modem.hpp"

#include <cstddef>
#include <cstdint>
#include <span>
#include <vector>

namespace wbhf_modem {

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

class Aes128CtrBitXor {
public:
  explicit Aes128CtrBitXor(Aes128Key key, Aes128CtrCounter counter = {});

  [[nodiscard]] std::uint8_t xor_bit(std::uint8_t bit);
  [[nodiscard]] SoftBit xor_soft_bit(SoftBit bit);
  [[nodiscard]] std::vector<std::uint8_t> xor_bits(std::span<const std::uint8_t> bits);
  [[nodiscard]] std::vector<SoftBit> xor_soft_bits(std::span<const SoftBit> bits);

private:
  [[nodiscard]] std::uint8_t next_keystream_bit();

  Aes128CtrKeystream stream_;
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

} // namespace wbhf_modem
