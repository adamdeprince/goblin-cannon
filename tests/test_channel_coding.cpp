#include "epoch_fixture.hpp"
// Simulated channel coding regressions: assert / quick, seed 0x71A005.
#include "goblin_cannon/channel_coding.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/message_stream.hpp"
#include <algorithm>
#include <bit>
#include <iostream>
#include <random>
#include <stdexcept>
using namespace goblin_cannon;
namespace {
constexpr unsigned seed = 0x71A005;
void require(bool ok, const char* why) {
  if (!ok)
    throw std::runtime_error(why);
}
void bch_test() {
  Bch63_45 code;
  require(code.generator() == 0x782cf, "BCH generator differs from (63,45,7) polynomial");
  require(code.encode(1) == 0x782cf, "BCH systematic unit vector");
  std::mt19937 random(seed);
  // Every three-error pattern on the zero word; linearity extends the guarantee
  // to every codeword. Include randomized nonzero codewords and 0/1/2 errors.
  for (unsigned a = 0; a < 63; ++a)
    for (unsigned b = a + 1; b < 63; ++b)
      for (unsigned c = b + 1; c < 63; ++c) {
        const auto result = code.decode((1ULL << a) | (1ULL << b) | (1ULL << c));
        require(result.valid && result.data == 0 && result.corrected_bits == 3, "BCH three-error correction");
      }
  for (unsigned i = 0; i < 1024; ++i) {
    const auto data = ((std::uint64_t(random()) << 32) | random()) & ((1ULL << 45) - 1);
    auto word = code.encode(data);
    std::uint64_t errors = 0;
    while (std::popcount(errors) < i % 4)
      errors |= 1ULL << (random() % 63);
    const auto result = code.decode(word ^ errors);
    require(result.valid && result.data == data && result.corrected_bits == i % 4,
            "BCH nonzero codeword correction");
  }
  unsigned rejected = 0;
  for (unsigned i = 0; i < 256; ++i) {
    std::uint64_t errors = 0;
    while (std::popcount(errors) < 4)
      errors |= 1ULL << (random() % 63);
    rejected += !code.decode(errors).valid;
  }
  require(rejected != 0, "BCH failed to report any uncorrectable word");
}
void soft_test() {
  Constellation bpsk(Modulation::bpsk);
  std::array<SoftBit, 10> bits{};
  bpsk.soft_bits({.25F, .6F}, .5F, bits);
  require(std::abs(bits[0].log_likelihood_ratio - 2.0F) < 1e-6F, "BPSK LLR is not 4*real/N0");
  for (auto mode :
       {Modulation::bpsk, Modulation::qpsk, Modulation::psk8, Modulation::qam16, Modulation::qam64}) {
    Constellation constellation(mode);
    for (unsigned symbol = 0; symbol < constellation.size(); ++symbol) {
      constellation.soft_bits(constellation.map_symbol(symbol), .3F, bits);
      for (unsigned bit = 0; bit < constellation.bits_per_symbol(); ++bit)
        require(bits[bit].value == ((symbol >> (constellation.bits_per_symbol() - bit - 1)) & 1),
                "per-bit mapping disagrees with wire labeling");
    }
  }
  Aes128Key key{};
  Aes128CtrBitXor hard(key), soft(key);
  for (unsigned i = 0; i < 1000; ++i) {
    const auto value = i & 1;
    const auto expected = hard.xor_bit(value);
    const auto result =
        soft.xor_soft_bit({static_cast<std::uint8_t>(value), false, .01F, value ? -2.0F : 2.0F});
    require(result.value == expected && ((result.log_likelihood_ratio < 0) == (expected != 0)),
            "CTR failed to invert LLR sign");
  }
  std::vector<std::uint8_t> source(256);
  std::mt19937 random(seed);
  for (auto& b : source)
    b = random();
  for (auto config :
       {PuncturedConvolutionalCodeConfig::rate_1_2(), PuncturedConvolutionalCodeConfig::k9_rate_1_2(),
        PuncturedConvolutionalCodeConfig::k9_rate_1_3()}) {
    auto coded = convolutional_encode_bytes(source, config);
    auto soft_bits = hard_bits_to_soft(coded);
    for (std::size_t i = 0; i < coded.size(); ++i) {
      const bool wrong = i % 53 == 11;
      const auto llr = (coded[i] ? -1.0F : 1.0F) * (wrong ? -.02F : 4.0F);
      soft_bits[i] = {static_cast<std::uint8_t>(llr < 0), false, .01F, llr};
    }
    const auto decoded = SoftViterbiDecoder(config).decode_bytes(soft_bits, source.size());
    for (std::size_t i = 0; i < source.size(); ++i)
      require(decoded.bytes[i].value == source[i],
              "Viterbi discarded soft observations or failed weak errors");
  }
}
void stream_test() {
  std::mt19937 random(seed);
  std::vector<std::uint8_t> source(600);
  for (auto& b : source)
    b = random();
  Aes128Key key{};
  for (auto& b : key.bytes)
    b = random();
  Aes128CtrCounter ctr{};
  ctr[15] = 27;
  for (auto fec :
       {PuncturedConvolutionalCodeConfig::rate_1_2(), PuncturedConvolutionalCodeConfig::rate_2_3(),
        PuncturedConvolutionalCodeConfig::rate_3_4(), PuncturedConvolutionalCodeConfig::k9_rate_1_2(),
        PuncturedConvolutionalCodeConfig::k9_rate_1_3()}) {
    for (bool bch : {false, true})
      for (unsigned walsh : {0U, 3U})
        for (unsigned rows : {0U, 4U, 16U}) {
          PayloadCodingConfig c{bch, static_cast<std::uint8_t>(walsh), rows, rows ? 16U : 0U};
          ChannelCodingEncoder tx(fec, c), bulk(fec, c);
          std::vector<std::uint8_t> coded, reference;
          for (const auto& byte : source)
            tx.push_bytes_append(std::span(&byte, 1), coded);
          bulk.push_bytes_append(source, reference);
          require(coded == reference, "coding output depends on chunk size");
          if (!bch && !walsh && !rows)
            require(coded == convolutional_encode_bytes(source, fec),
                    "FEC-only bytes changed");
          auto soft = hard_bits_to_soft(coded);
          for (auto& bit : soft)
            bit.log_likelihood_ratio = bit.value ? -8 : 8;
          for (unsigned chunk : {1U, 127U}) {
            ChannelCodingDecoder rx(fec, c);
            std::vector<Token> decoded;
            for (std::size_t at = 0; at < soft.size(); at += chunk)
              rx.push_append(std::span(soft).subspan(at, std::min<std::size_t>(chunk, soft.size() - at)),
                             decoded);
            require(decoded.size() > source.size() - 80, "coding lost an unexpected tail");
            for (std::size_t i = 0; i < decoded.size(); ++i)
              require(decoded[i].certain && decoded[i].value == source[i], "coding stream roundtrip");
            for (unsigned lost : {1U, 17U, 129U, 517U}) {
              decoded.clear();
              const auto skip = rx.resume_at_wire_bit(lost);
              const auto at = lost + skip;
              rx.push_append(std::span(soft).subspan(at), decoded);
              require(decoded.size() > 300, "recovery discarded too much data");
              // An unknown convolutional history discards a few source bytes. Find
              // the first 8-byte witness then require the entire remaining stream.
              std::size_t begin = 0;
              for (; begin + decoded.size() <= source.size(); ++begin) {
                bool match = true;
                for (unsigned i = 0; i < 8; ++i)
                  match &= decoded[i].value == source[begin + i];
                if (match)
                  break;
              }
              require(begin + decoded.size() <= source.size(), "resume did not align code or CTR position");
              for (std::size_t i = 0; i < decoded.size(); ++i)
                require(decoded[i].value == source[begin + i], "resume lost source alignment");
            }
          }
        }
  }
}
} // namespace
int main() {
  goblin_cannon::test::EpochFixture epoch_fixture;
  try {
    std::cout << "simulated channel coding / assert / quick / seed=" << seed << '\n';
    bch_test();
    soft_test();
    stream_test();
    std::cout
        << "BCH complete three-error pattern set, bit LLRs, stronger FEC, chunking and gap recovery passed\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
