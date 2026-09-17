#pragma once

#include "goblin_cannon/convolutional.hpp"

#include <array>
#include <memory>

namespace goblin_cannon {

// Conventional binary primitive BCH(63,45,7), GF(64), p(x)=x^6+x+1.
// Systematic data occupy bits 62..18; bounded-distance decoding corrects <=3
// errors. A success is a codeword, not authentication; verify the AEAD record.
struct BchDecodeResult {
  std::uint64_t data = 0;
  bool valid = false;
  unsigned corrected_bits = 0;
};
class Bch63_45 {
public:
  Bch63_45();
  [[nodiscard]] std::uint64_t encode(std::uint64_t data) const;
  [[nodiscard]] BchDecodeResult decode(std::uint64_t word) const;
  [[nodiscard]] std::uint32_t generator() const noexcept { return generator_; }

private:
  std::uint8_t multiply(std::uint8_t a, std::uint8_t b) const noexcept;
  std::uint8_t divide(std::uint8_t a, std::uint8_t b) const;
  std::array<std::uint8_t, 6> syndromes(std::uint64_t word) const;
  std::array<std::uint8_t, 126> exp_{};
  std::array<std::uint8_t, 64> log_{};
  std::uint32_t generator_ = 0;
};

struct PayloadCodingConfig {
  // Replace the convolutional code with shortened BCH(58,40,7): 5 bytes/block.
  bool bch = false;
  // Zero disables spreading. Three coded bits select one 8-chip Walsh row.
  std::uint8_t walsh_bits = 0;
  // Plain rectangular row-write/column-read permutation. Zero/zero disables.
  std::uint32_t interleaver_rows = 0;
  std::uint32_t interleaver_columns = 0;
};
void validate(const PayloadCodingConfig& config);
[[nodiscard]] double payload_coding_rate(const PayloadCodingConfig& config,
                                         const PuncturedConvolutionalCodeConfig& fec);

// Order: authenticated message record -> FEC -> optional Walsh -> interleaver.
// The receiver reverses these stages. All parameters are configured over fiber.
class ChannelCodingEncoder {
public:
  ChannelCodingEncoder(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig coding);
  ~ChannelCodingEncoder();
  void push_bytes_append(std::span<const std::uint8_t> bytes, std::vector<std::uint8_t>& out);

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};
class ChannelCodingDecoder {
public:
  ChannelCodingDecoder(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig coding);
  ~ChannelCodingDecoder();
  void push_append(std::span<const SoftBit> bits, std::vector<Token>& out);
  void reset();
  // Discard partial interleaver/spreading blocks. Returned skip is in wire bits;
  // FEC resumes at the matching absolute position. AEAD resumes by record.
  [[nodiscard]] std::size_t resume_at_wire_bit(std::uint64_t position);

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace goblin_cannon
