#include "goblin_cannon/channel_coding.hpp"

#include <algorithm>
#include <bit>
#include <cmath>
#include <limits>
#include <numeric>
#include <stdexcept>

namespace goblin_cannon {

Bch63_45::Bch63_45() {
  unsigned x = 1;
  for (unsigned i = 0; i < 63; ++i) {
    exp_[i] = static_cast<std::uint8_t>(x);
    log_[x] = static_cast<std::uint8_t>(i);
    x <<= 1;
    if (x & 64)
      x ^= 0x43;
  }
  for (unsigned i = 63; i < 126; ++i)
    exp_[i] = exp_[i - 63];
  // Product over the conjugacy classes of roots alpha^1 .. alpha^6.
  std::array<bool, 63> root{};
  for (unsigned i = 1; i <= 6; ++i) {
    unsigned j = i;
    do {
      root[j] = true;
      j = (2 * j) % 63;
    } while (j != i);
  }
  std::vector<std::uint8_t> polynomial{1};
  for (unsigned r = 0; r < 63; ++r)
    if (root[r]) {
      std::vector<std::uint8_t> next(polynomial.size() + 1);
      for (std::size_t i = 0; i < polynomial.size(); ++i) {
        next[i] ^= multiply(polynomial[i], exp_[r]);
        next[i + 1] ^= polynomial[i];
      }
      polynomial.swap(next);
    }
  if (polynomial.size() != 19)
    throw std::logic_error("BCH generator degree");
  for (unsigned i = 0; i < polynomial.size(); ++i) {
    if (polynomial[i] > 1)
      throw std::logic_error("BCH generator is not binary");
    generator_ |= static_cast<std::uint32_t>(polynomial[i]) << i;
  }
}
std::uint8_t Bch63_45::multiply(std::uint8_t a, std::uint8_t b) const noexcept {
  return !a || !b ? 0 : exp_[log_[a] + log_[b]];
}
std::uint8_t Bch63_45::divide(std::uint8_t a, std::uint8_t b) const {
  if (!b)
    throw std::logic_error("BCH division by zero");
  return !a ? 0 : exp_[(log_[a] + 63 - log_[b]) % 63];
}
std::array<std::uint8_t, 6> Bch63_45::syndromes(std::uint64_t word) const {
  std::array<std::uint8_t, 6> s{};
  for (unsigned i = 0; i < 63; ++i)
    if ((word >> i) & 1)
      for (unsigned j = 1; j <= 6; ++j)
        s[j - 1] ^= exp_[(i * j) % 63];
  return s;
}
std::uint64_t Bch63_45::encode(std::uint64_t data) const {
  if (data >> 45)
    throw std::invalid_argument("BCH source exceeds 45 bits");
  const auto systematic = data << 18;
  auto remainder = systematic;
  for (int bit = 62; bit >= 18; --bit)
    if ((remainder >> bit) & 1)
      remainder ^= static_cast<std::uint64_t>(generator_) << (bit - 18);
  return systematic | remainder;
}
BchDecodeResult Bch63_45::decode(std::uint64_t word) const {
  if (word >> 63)
    throw std::invalid_argument("BCH word exceeds 63 bits");
  const auto s = syndromes(word);
  if (std::all_of(s.begin(), s.end(), [](auto v) { return v == 0; }))
    return {word >> 18, true, 0};
  // Standard Berlekamp-Massey recurrence, then a direct Chien root search.
  std::array<std::uint8_t, 7> c{1}, b{1};
  unsigned degree = 0, shift = 1;
  std::uint8_t previous_discrepancy = 1;
  for (unsigned n = 0; n < 6; ++n) {
    auto discrepancy = s[n];
    for (unsigned i = 1; i <= degree; ++i)
      discrepancy ^= multiply(c[i], s[n - i]);
    if (!discrepancy) {
      ++shift;
      continue;
    }
    const auto old = c;
    const auto scale = divide(discrepancy, previous_discrepancy);
    for (unsigned i = 0; i + shift < c.size(); ++i)
      c[i + shift] ^= multiply(scale, b[i]);
    if (2 * degree <= n) {
      degree = n + 1 - degree;
      b = old;
      previous_discrepancy = discrepancy;
      shift = 1;
    } else
      ++shift;
  }
  if (degree == 0 || degree > 3)
    return {};
  unsigned roots = 0;
  for (unsigned i = 0; i < 63; ++i) {
    std::uint8_t value = c[0];
    for (unsigned j = 1; j <= degree; ++j)
      value ^= multiply(c[j], exp_[(63 - i) * j % 63]);
    if (!value) {
      word ^= std::uint64_t{1} << i;
      ++roots;
    }
  }
  if (roots != degree)
    return {};
  const auto check = syndromes(word);
  if (std::any_of(check.begin(), check.end(), [](auto v) { return v != 0; }))
    return {};
  return {word >> 18, true, roots};
}

void validate(const PayloadCodingConfig& c) {
  if (c.walsh_bits != 0 && c.walsh_bits != 3)
    throw std::invalid_argument("Walsh uses 0 or 3 bits per 8-chip row");
  const auto block = static_cast<std::uint64_t>(c.interleaver_rows) * c.interleaver_columns;
  if ((c.interleaver_rows == 0) != (c.interleaver_columns == 0) || block > 65536)
    throw std::invalid_argument(
        "interleaver dimensions must both be zero or give a block of at most 65536 bits");
}
double payload_coding_rate(const PayloadCodingConfig& c, const PuncturedConvolutionalCodeConfig& fec) {
  validate(c);
  validate(fec);
  const auto kept =
      std::count_if(fec.puncture_pattern.begin(), fec.puncture_pattern.end(), [](auto x) { return x != 0; });
  const double rate =
      c.bch ? 40.0 / 58.0 : static_cast<double>(fec.puncture_pattern.size()) / (fec.mother_outputs() * kept);
  return rate * (c.walsh_bits ? 3.0 / 8.0 : 1.0);
}

class ChannelCodingEncoder::Impl {
public:
  Impl(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig config, Aes128Key key,
       Aes128CtrCounter counter)
      : coding(config), convolutional(std::move(fec)), cipher(key, counter) {
    validate(coding);
  }
  void push(std::span<const std::uint8_t> bytes, std::vector<std::uint8_t>& out) {
    coded.clear();
    if (!coding.bch)
      convolutional.push_bytes_append(bytes, coded);
    else
      for (auto byte : bytes) {
        bch_data = (bch_data << 8) | byte;
        if (++bch_bytes == 5) {
          const auto word = bch.encode(bch_data);
          for (int i = 57; i >= 0; --i)
            coded.push_back((word >> i) & 1);
          bch_data = 0;
          bch_bytes = 0;
        }
      }
    cipher.xor_bits_in_place(coded);
    for (auto bit : coded) {
      if (!coding.walsh_bits)
        interleave(bit, out);
      else {
        walsh_row = (walsh_row << 1) | bit;
        if (++walsh_count == 3) {
          for (unsigned chip = 0; chip < 8; ++chip)
            interleave(std::popcount(walsh_row & chip) & 1, out);
          walsh_row = 0;
          walsh_count = 0;
        }
      }
    }
  }

private:
  void interleave(std::uint8_t bit, std::vector<std::uint8_t>& out) {
    if (!coding.interleaver_rows) {
      out.push_back(bit);
      return;
    }
    permutation.push_back(bit);
    if (permutation.size() == coding.interleaver_rows * coding.interleaver_columns) {
      for (unsigned column = 0; column < coding.interleaver_columns; ++column)
        for (unsigned row = 0; row < coding.interleaver_rows; ++row)
          out.push_back(permutation[row * coding.interleaver_columns + column]);
      permutation.clear();
    }
  }
  PayloadCodingConfig coding;
  PuncturedConvolutionalEncoder convolutional;
  Aes128CtrBitXor cipher;
  Bch63_45 bch;
  std::uint64_t bch_data = 0;
  unsigned bch_bytes = 0, walsh_row = 0, walsh_count = 0;
  std::vector<std::uint8_t> coded, permutation;
};

class ChannelCodingDecoder::Impl {
public:
  Impl(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig config, Aes128Key k, Aes128CtrCounter ctr)
      : coding(config), viterbi(std::move(fec)), key(k), counter(ctr), cipher(k, ctr) {
    validate(coding);
  }
  void reset() {
    viterbi.reset();
    cipher = Aes128CtrBitXor(key, counter);
    permutation.clear();
    walsh.clear();
    fec_bits.clear();
    bch_bits.clear();
    fec_skip = 0;
  }
  std::size_t resume(std::uint64_t position) {
    reset();
    const auto permutation_size =
        std::max<std::uint64_t>(1, coding.interleaver_rows * coding.interleaver_columns);
    const auto alignment = std::lcm<std::uint64_t>(permutation_size, coding.walsh_bits ? 8 : 1);
    const auto skip = (alignment - position % alignment) % alignment;
    if (position > std::numeric_limits<std::uint64_t>::max() - skip)
      throw std::overflow_error("coded stream position overflow");
    auto fec_position = position + skip;
    if (coding.walsh_bits)
      fec_position = fec_position / 8 * 3;
    cipher = Aes128CtrBitXor(key, counter, fec_position);
    fec_skip = coding.bch ? (58 - fec_position % 58) % 58 : viterbi.resume_at_coded_bit(fec_position);
    if (fec_position == 0) {
      viterbi.reset();
      fec_skip = 0;
    }
    return skip;
  }
  void push(std::span<const SoftBit> bits, std::vector<Token>& out) {
    fec_bits.clear();
    for (auto bit : bits) {
      if (!coding.interleaver_rows)
        despread(bit);
      else {
        permutation.push_back(bit);
        if (permutation.size() == coding.interleaver_rows * coding.interleaver_columns) {
          for (unsigned row = 0; row < coding.interleaver_rows; ++row)
            for (unsigned column = 0; column < coding.interleaver_columns; ++column)
              despread(permutation[column * coding.interleaver_rows + row]);
          permutation.clear();
        }
      }
    }
    if (!coding.bch) {
      viterbi.push_append(fec_bits, out);
      return;
    }
    for (auto bit : fec_bits) {
      bch_bits.push_back(bit);
      if (bch_bits.size() != 58)
        continue;
      std::uint64_t word = 0;
      for (auto b : bch_bits)
        word = (word << 1) | (b.value & 1);
      const auto decoded = bch.decode(word);
      const bool valid = decoded.valid && (decoded.data >> 40) == 0;
      for (int i = 4; i >= 0; --i)
        out.push_back({static_cast<std::uint8_t>(decoded.data >> (8 * i)), valid, valid ? 1.0F : 0.0F});
      bch_bits.clear();
    }
  }

private:
  void clear_bit(SoftBit bit) {
    bit = cipher.xor_soft_bit(bit);
    if (fec_skip)
      --fec_skip;
    else
      fec_bits.push_back(bit);
  }
  void despread(SoftBit bit) {
    if (!coding.walsh_bits) {
      clear_bit(bit);
      return;
    }
    walsh.push_back(bit);
    if (walsh.size() != 8)
      return;
    std::array<float, 8> score{};
    for (unsigned row = 0; row < 8; ++row)
      for (unsigned chip = 0; chip < 8; ++chip) {
        const auto& b = walsh[chip];
        const auto llr = std::isfinite(b.log_likelihood_ratio)
                             ? b.log_likelihood_ratio
                             : (b.certain ? (b.value ? -1 : 1) * b.confidence : 0);
        score[row] += (std::popcount(row & chip) & 1) ? -llr : llr;
      }
    // Ordinary correlation-bank maximum-log bit likelihoods; no iterative
    // Walsh-constrained equalizer or frequency-modulated CROW waveform.
    for (unsigned index = 0; index < 3; ++index) {
      float best[2] = {-INFINITY, -INFINITY};
      for (unsigned row = 0; row < 8; ++row) {
        const auto b = (row >> (2 - index)) & 1;
        best[b] = std::max(best[b], score[row]);
      }
      const auto llr = std::clamp((best[0] - best[1]) * 0.5F, -64.0F, 64.0F);
      clear_bit({static_cast<std::uint8_t>(llr < 0), llr != 0, std::tanh(std::abs(llr) * 0.5F), llr});
    }
    walsh.clear();
  }
  PayloadCodingConfig coding;
  StreamingSoftViterbiDecoder viterbi;
  Aes128Key key;
  Aes128CtrCounter counter;
  Aes128CtrBitXor cipher;
  Bch63_45 bch;
  std::vector<SoftBit> permutation, walsh, fec_bits, bch_bits;
  std::size_t fec_skip = 0;
};

ChannelCodingEncoder::ChannelCodingEncoder(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig coding,
                                           Aes128Key key, Aes128CtrCounter counter)
    : impl_(std::make_unique<Impl>(std::move(fec), coding, key, counter)) {
}
ChannelCodingEncoder::~ChannelCodingEncoder() = default;
void ChannelCodingEncoder::push_bytes_append(std::span<const std::uint8_t> bytes,
                                             std::vector<std::uint8_t>& out) {
  impl_->push(bytes, out);
}
ChannelCodingDecoder::ChannelCodingDecoder(PuncturedConvolutionalCodeConfig fec, PayloadCodingConfig coding,
                                           Aes128Key key, Aes128CtrCounter counter)
    : impl_(std::make_unique<Impl>(std::move(fec), coding, key, counter)) {
}
ChannelCodingDecoder::~ChannelCodingDecoder() = default;
void ChannelCodingDecoder::push_append(std::span<const SoftBit> bits, std::vector<Token>& out) {
  impl_->push(bits, out);
}
void ChannelCodingDecoder::reset() {
  impl_->reset();
}
std::size_t ChannelCodingDecoder::resume_at_wire_bit(std::uint64_t position) {
  return impl_->resume(position);
}

} // namespace goblin_cannon
