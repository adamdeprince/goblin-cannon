// Simulated channel alternative-waveform regressions: assert / quick, seed 0x71A006.
#include "channel_simulator.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/message_stream.hpp"
#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
using namespace goblin_cannon;
namespace {
constexpr unsigned seed = 0x71A006;
void require(bool ok, const char* why) {
  if (!ok)
    throw std::runtime_error(why);
}
RfStreamConfig config(AudioWaveform wave, int band) {
  RfStreamConfig c;
  c.waveform = wave;
  c.modem.bandwidth_hz = band;
  c.modem.modulation = wave == AudioWaveform::fsk4   ? Modulation::qpsk
                       : wave == AudioWaveform::fsk8 ? Modulation::psk8
                                                     : Modulation::bpsk;
  c.acquisition_sequence = make_default_qpsk_sequence(64, seed);
  c.equalizer_training_sequence = make_default_qpsk_sequence(128, seed + 1);
  c.pilot_sequence = {0, (1U << bits_per_symbol(c.modem.modulation)) - 1};
  c.symbols_per_frame = 64;
  c.pilot_interval_symbols = 32;
  c.carrier_correction = false;
  c.recursive_equalization = true;
  c.soft_demapping = true;
  c.compact_header = true;
  c.recovery_interval_frames = 16;
  c.fractionally_spaced_equalization = true;
  c.equalizer_reselect_interval = 128;
  c.acquisition_confidence_threshold = .25F;
  return c;
}
std::vector<Complex> encode(const RfStreamConfig& c, const std::vector<std::uint32_t>& payload,
                            unsigned chunk) {
  RfStreamEncoder tx(c);
  tx.start_epoch(7000);
  std::vector<Complex> out, block(chunk);
  std::size_t at = 0;
  while (tx.active()) {
    const auto r =
        at < payload.size() ? tx.push_symbols(std::span(payload).subspan(at), block) : tx.drain(block);
    at += r.consumed_symbols;
    out.insert(out.end(), block.begin(), block.begin() + r.produced_samples);
  }
  require(at == payload.size(), "alternative TX truncated payload");
  return out;
}
void waveform_test(const RfStreamConfig& c, unsigned symbols = 128) {
  std::mt19937 random(seed);
  std::vector<std::uint32_t> payload(symbols);
  for (auto& s : payload)
    s = random() & ((1U << bits_per_symbol(c.modem.modulation)) - 1);
  auto audio = encode(c, payload, 257);
  require(audio == encode(c, payload, 17), "waveform depends on TX chunks");
  double power = 0;
  for (auto s : audio)
    power += std::norm(s);
  const auto nominal =
      c.modem.tx_gain * c.modem.tx_gain * c.modem.bandwidth_hz / 1.25 / c.modem.sample_rate_hz;
  // Finite RRC sequences have startup/tail power; the steady noncoherent tone
  // waveform must have the same nominal power to floating-point precision.
  if (c.waveform == AudioWaveform::fsk4 || c.waveform == AudioWaveform::fsk8)
    require(std::abs(power / audio.size() - nominal) < 1e-6,
            "FSK total power differs from nominal RRC power");
  audio.insert(audio.end(), 960, Complex{});
  if (c.waveform == AudioWaveform::fsk4 || c.waveform == AudioWaveform::fsk8) {
    test::Impairments impairment;
    impairment.legacy.phase_rad = 1.2;
    test::SimulatedChannel channel(c.modem.sample_rate_hz, nominal, impairment, seed);
    channel.residual_offset_hz = 3;
    std::vector<Complex> shifted;
    channel.process(audio, shifted);
    audio.swap(shifted);
  }
  for (unsigned chunk : {17U, 127U}) {
    RfStreamReceiver rx(c);
    std::array<RfStreamSymbol, 256> out{};
    std::size_t seen = 0;
    for (std::size_t at = 0; at < audio.size(); at += chunk) {
      const auto r =
          rx.push_samples(std::span(audio).subspan(at, std::min<std::size_t>(chunk, audio.size() - at)), out);
      require(r.consumed_samples == std::min<std::size_t>(chunk, audio.size() - at),
              "alternative RX backpressure violated");
      for (unsigned i = 0; i < r.produced_symbols; ++i) {
        const auto index = (out[i].frame_counter - 7000) * c.symbols_per_frame + out[i].frame_symbol_offset;
        if (index >= payload.size())
          continue;
        if (index != seen || out[i].value != payload[index]) {
          std::cerr << "mode=" << static_cast<int>(c.waveform) << " band=" << c.modem.bandwidth_hz
                    << " index=" << index << " expected_index=" << seen << " value=" << out[i].value
                    << " expected=" << payload[index] << '\n';
          throw std::runtime_error("alternative RF symbol/boundary mismatch");
        }
        require(out[i].has_soft_bits, "alternative RF missing bit metrics");
        ++seen;
      }
    }
    if (seen != payload.size())
      std::cerr << "mode=" << static_cast<int>(c.waveform) << " band=" << c.modem.bandwidth_hz
                << " seen=" << seen << " state=" << static_cast<int>(rx.state()) << '\n';
    require(seen == payload.size(), "alternative RX failed a complete null simulated channel stream");
  }
}
void pipeline_test(AudioWaveform wave, PayloadCodingConfig coding, Modulation mode = Modulation::bpsk) {
  RealtimePipelineConfig c;
  c.rf = config(wave, 24000);
  if (wave == AudioWaveform::single_carrier) {
    c.rf.modem.modulation = mode;
    c.rf.pilot_sequence = {0, (1U << bits_per_symbol(mode)) - 1};
  }
  c.coding = coding;
  c.sync_timestamp.enabled = false;
  c.convolutional.decoded_bit_confidence_threshold = 0;
  c.frame_counter_start = 7000;
  SpscRingBuffer<DelimitedMessage> input(256), output(256);
  RealtimeTransmitter tx(c, input);
  RealtimeReceiver rx(c, output);
  std::array<Complex, 48> audio{};
  const bool fsk = wave == AudioWaveform::fsk4 || wave == AudioWaveform::fsk8;
  const unsigned ticks = fsk ? 30000 : 2200;
  test::Impairments impairment;
  impairment.dropout_start_s = ticks / 2000.0;
  impairment.dropout_duration_s = .2;
  test::SimulatedChannel channel(48000, .65 * .65 * .4, impairment, seed);
  std::vector<Complex> impaired;
  unsigned created = 0, delivered = 0, after_gap = 0;
  std::int64_t last = -1;
  for (unsigned tick = 0; tick < ticks; ++tick) {
    if (tick % 200 == 0) {
      require(input.try_push(encode_bank_symbol_integer(0, 2, created++)), "unit source overflow");
    }
    const auto sent = tx.push_samples(audio);
    require(sent.produced_samples == audio.size(), "block code failed to fill TX audio");
    channel.process(audio, impaired);
    (void)rx.push_samples(impaired);
    DelimitedMessage message;
    while (output.try_pop(message)) {
      const auto decoded = decode_bank_symbol_integer(message);
      require(decoded && decoded->bank == 0 && decoded->symbol == 2 && decoded->value >= 0 &&
                  decoded->value < created,
              "coding pipeline wrong payload");
      require(decoded->value > last, "coding pipeline duplicated/reordered a message");
      last = decoded->value;
      ++delivered;
      after_gap += tick > ticks / 2 + 200;
    }
  }
  if (!delivered || !after_gap)
    std::cerr << "pipeline mode=" << static_cast<int>(wave) << " bch=" << coding.bch
              << " walsh=" << unsigned(coding.walsh_bits) << " rows=" << coding.interleaver_rows
              << " delivered=" << delivered << " recovered=" << after_gap << '\n';
  require(delivered > 0 && after_gap > 0, "coding/audio pipeline failed to recover after dropout");
}
void diversity_controls_test() {
  for (int band : {10000, 24000}) {
    auto c = config(AudioWaveform::bpsk_frequency_diversity, band);
    c.diversity_branch_bandwidth_hz = band * .4;
    for (auto separation : {band * .5, band * .5 + 137, band * .55 + 137}) {
      c.diversity_separation_hz = separation;
      for (unsigned mask : {1U, 2U, 3U}) {
        c.diversity_branch_mask = mask;
        waveform_test(c);
      }
    }
    // Generated long streams check finite-waveform power against the same
    // full-power single-copy controls. The 2% tolerance covers RRC truncation
    // and finite-record cross terms; it is not an RF acceptance threshold.
    std::mt19937 random(seed);
    std::vector<std::uint32_t> payload(8192);
    for (auto& symbol : payload) symbol = random() & 1;
    std::array<double, 3> power{};
    std::array<std::vector<Complex>, 3> samples;
    for (unsigned mask : {1U, 2U, 3U}) {
      c.diversity_branch_mask = mask;
      samples[mask - 1] = encode(c, payload, 257);
      power[mask - 1] = test::mean_power(samples[mask - 1]);
    }
    require(std::abs(power[0] / power[1] - 1) < 1e-6, "single-copy controls have unequal power");
    require(std::abs(power[2] / power[0] - 1) < .02, "diversity changes total finite-waveform power");
    require(samples[0] != samples[1], "diversity controls did not select different frequencies");
    auto legacy = config(AudioWaveform::bpsk_frequency_diversity, band);
    auto explicit_defaults = legacy;
    explicit_defaults.diversity_branch_bandwidth_hz = band / 2;
    explicit_defaults.diversity_separation_hz = band / 2;
    require(encode(legacy, payload, 257) == encode(explicit_defaults, payload, 257),
            "explicit legacy diversity geometry changes samples");
    for (unsigned invalid = 0; invalid < 5; ++invalid) {
      auto bad = c;
      if (invalid == 0) bad.diversity_branch_bandwidth_hz = -1;
      if (invalid == 1) bad.diversity_separation_hz = band * .3;
      if (invalid == 2) bad.diversity_separation_hz = band * .7;
      if (invalid == 3) bad.diversity_branch_mask = 0;
      if (invalid == 4) bad.diversity_separation_hz = std::numeric_limits<double>::quiet_NaN();
      bool rejected = false;
      try { validate(bad); } catch (const std::invalid_argument&) { rejected = true; }
      require(rejected, "invalid diversity geometry was accepted");
    }
  }
}
} // namespace
int main() {
  try {
    std::cout << "simulated channel audio waveforms / assert / quick / seed=" << seed << '\n';
    for (auto w : {AudioWaveform::fsk4, AudioWaveform::fsk8, AudioWaveform::bpsk_frequency_diversity})
      for (int band : {10000, 24000})
        waveform_test(config(w, band));
    for (auto w : {AudioWaveform::fsk4, AudioWaveform::fsk8, AudioWaveform::bpsk_frequency_diversity})
      pipeline_test(w, {});
    for (auto coding :
         {PayloadCodingConfig{true}, PayloadCodingConfig{false, 3}, PayloadCodingConfig{false, 0, 4, 8},
          PayloadCodingConfig{false, 0, 16, 128}, PayloadCodingConfig{true, 3, 4, 16}})
      pipeline_test(AudioWaveform::single_carrier, coding);
    for (auto mode : {Modulation::qpsk, Modulation::psk8})
      pipeline_test(AudioWaveform::single_carrier, PayloadCodingConfig{true}, mode);
    diversity_controls_test();
    for (auto cadence : {std::pair{16U,16U}, {32U,16U}, {64U,16U}, {32U,4U}, {32U,64U}}) {
      auto c = config(AudioWaveform::single_carrier, 24000);
      c.pilot_interval_symbols = cadence.first;
      c.recovery_interval_frames = cadence.second;
      waveform_test(c, 2 * cadence.second * c.symbols_per_frame);
    }
    std::cout << "RF chunking, fixed FSK power, message correctness and dropout recovery passed\n";
  } catch (const std::exception& e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
}
