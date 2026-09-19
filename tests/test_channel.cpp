#include "goblin_cannon/rf_stream.hpp"
#include "demapper.hpp"
#include "channel_simulator.hpp"

#include <algorithm>
#include <array>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <limits>
#include <numbers>
#include <optional>
#include <random>
#include <span>
#include <stdexcept>
#include <string>
#include <string_view>
#include <utility>
#include <vector>

using namespace goblin_cannon;
using goblin_cannon::test::Channel;
using goblin_cannon::test::mean_power;
using goblin_cannon::test::through_channel;

namespace {

constexpr double tau = 2.0 * std::numbers::pi;
constexpr std::array<std::uint32_t, 3> noise_seeds = {0x71A001U, 0x71A002U, 0x71A003U};

struct ModulationCase {
  Modulation modulation;
  std::string_view name;
  double noise_snr_db;
  double tracking_snr_db;
  double small_phase_degrees;
  double fade_depth_db;
  double fade_rate_hz;
  double combined_fade_depth_db;
};

// Reproducible zero-error regression points, not minimum operating SNRs.
constexpr std::array modulation_cases = {
    ModulationCase{Modulation::qpsk, "QPSK (4-QAM)", 14.0, 24.0, 20.0, 12.0, 5.0, 6.0},
    ModulationCase{Modulation::qam16, "16QAM", 24.0, 30.0, 10.0, 6.0, 2.0, 6.0},
    ModulationCase{Modulation::qam64, "64QAM", 34.0, 36.0, 1.0, 3.0, 1.0, 3.0},
};

void require(bool condition, std::string_view message) {
  if (!condition) {
    throw std::runtime_error(std::string(message));
  }
}

RfStreamConfig make_config(Modulation modulation = Modulation::qam64) {
  RfStreamConfig config;
  config.modem.sample_rate_hz = 48000.0;
  config.modem.bandwidth_hz = 12000.0;
  config.modem.symbol_rate_hz = 9600.0;
  config.modem.modulation = modulation;
  config.modem.rrc_rolloff = 0.35;
  config.expected_schedule_epoch = 0x1020304050607080ULL;
  config.acquisition_sequence = make_default_qpsk_sequence(64, 0xA5A50001U);
  config.equalizer_training_sequence = make_default_qpsk_sequence(32, 0x5A5A0002U);
  config.pilot_sequence = {0, (1U << bits_per_symbol(modulation)) - 1U};
  config.symbols_per_frame = 64;
  config.pilot_interval_symbols = 32;
  config.acquisition_confidence_threshold = 0.25F;
  config.pilot_confidence_threshold = 0.08F;
  config.symbol_confidence_threshold = 0.08F;
  config.acquisition_sidelobe_guard_samples = 48;
  return config;
}

std::vector<std::uint32_t> make_payload(const RfStreamConfig& config, std::size_t count) {
  std::mt19937 random(0xC011AB1EU);
  std::vector<std::uint32_t> payload(count);
  const auto mask = (1U << bits_per_symbol(config.modem.modulation)) - 1U;
  for (auto& symbol : payload) {
    symbol = random() & mask;
  }
  return payload;
}

std::vector<Complex> encode(const RfStreamConfig& config,
                            std::span<const std::uint32_t> payload,
                            std::uint64_t frame_start = 7000, std::size_t chunk_size = 193) {
  RfStreamEncoder encoder(config);
  encoder.start_epoch(frame_start);
  std::vector<Complex> samples;
  std::vector<Complex> chunk(chunk_size);
  std::size_t offset = 0;
  for (std::size_t guard = 0; guard < 100000 && encoder.active(); ++guard) {
    const auto result = offset < payload.size()
        ? encoder.push_symbols(payload.subspan(offset), chunk) : encoder.drain(chunk);
    offset += result.consumed_symbols;
    samples.insert(samples.end(), chunk.begin(), chunk.begin() + result.produced_samples);
  }
  require(offset == payload.size() && !encoder.active(), "RF encoder did not finish");
  return samples;
}

struct Reception {
  std::vector<RfStreamSymbol> symbols;
  RfSyncEstimate sync;
  std::size_t consumed_samples = 0;
  std::optional<std::size_t> first_lock_loss_sample;
  bool acquired = false;
  bool header_valid = false;
  bool lock_lost = false;
};

void receive(RfStreamReceiver& receiver, std::span<const Complex> samples,
             Reception& reception, std::size_t chunk_size = 157) {
  // More output capacity than any input chunk can produce, including the
  // buffered matched-filter tail. Chunk boundaries are unrelated to symbols.
  std::array<RfStreamSymbol, 512> output{};
  for (std::size_t offset = 0; offset < samples.size();) {
    const auto count = std::min(chunk_size, samples.size() - offset);
    const auto result = receiver.push_samples(samples.subspan(offset, count), output);
    require(result.consumed_samples == count, "receiver did not consume input chunk");
    offset += result.consumed_samples;
    reception.consumed_samples += result.consumed_samples;
    if (result.lock_lost && !reception.first_lock_loss_sample.has_value()) {
      reception.first_lock_loss_sample = reception.consumed_samples;
    }
    reception.acquired |= result.acquisition_found;
    reception.header_valid |= result.header_valid;
    reception.lock_lost |= result.lock_lost;
    reception.sync = result.sync;
    reception.symbols.insert(reception.symbols.end(), output.begin(), output.begin() + result.produced_symbols);
  }
}

void check_payload(const RfStreamConfig& config, const Reception& reception,
                   std::span<const std::uint32_t> payload, std::uint64_t frame_start = 7000) {
  require(reception.acquired, "receiver did not acquire");
  require(reception.header_valid, "receiver did not validate header (training EVM=" +
      std::to_string(reception.sync.training_evm) + ", carrier frequency offset=" +
      std::to_string(reception.sync.carrier_frequency_offset_hz) + " Hz)");
  require(!reception.lock_lost, "receiver lost lock");
  require(reception.symbols.size() >= payload.size(), "receiver truncated payload");
  std::size_t errors = 0;
  std::size_t first_error = payload.size();
  for (std::size_t i = 0; i < payload.size(); ++i) {
    if (reception.symbols[i].value != payload[i]) {
      ++errors;
      first_error = std::min(first_error, i);
    }
    require(reception.symbols[i].frame_counter == frame_start + i / config.symbols_per_frame,
            "frame counter slipped");
    require(reception.symbols[i].frame_symbol_offset == i % config.symbols_per_frame,
            "frame symbol offset slipped");
    require(std::isfinite(reception.symbols[i].confidence), "non-finite confidence");
  }
  require(errors == 0, "payload symbol errors: " + std::to_string(errors) +
      ", first index=" + std::to_string(first_error) + ", training EVM=" + std::to_string(reception.sync.training_evm));
}

void test_matched_filter_sample_support() {
  // Simulated channel, no impairments. A drained block must decode completely
  // without samples from a following block. Odd/even lengths exercise both
  // integer and fractional final-symbol support boundaries at 2.5 samples/symbol.
  for (const double samples_per_symbol : {2.0, 2.5, 3.125, 5.0, 6.0}) {
    for (const std::size_t count : {32U, 33U}) {
      auto config = make_config(Modulation::qpsk);
      config.modem.symbol_rate_hz = config.modem.sample_rate_hz / samples_per_symbol;
      config.modem.bandwidth_hz = *config.modem.symbol_rate_hz / 0.8;
      config.modem.rrc_rolloff = 0.25;
      const auto payload = make_payload(config, count);
      const Constellation constellation(Modulation::qpsk);
      std::vector<std::uint8_t> bits(count * 2U);
      for (std::size_t i = 0; i < count; ++i) {
        constellation.symbol_to_bits(payload[i], std::span(bits).subspan(i * 2U, 2U));
      }
      Encoder encoder(config.modem);
      std::array<Complex, 19> chunk{};
      std::vector<Complex> samples;
      const auto pushed = encoder.push_bits(bits, chunk);
      require(pushed.consumed == bits.size(), "sample-support fixture truncated input");
      samples.insert(samples.end(), chunk.begin(), chunk.begin() + pushed.produced);
      for (;;) {
        const auto drained = encoder.drain(chunk);
        samples.insert(samples.end(), chunk.begin(), chunk.begin() + drained.produced);
        if (drained.produced == 0) break;
      }

      Decoder decoder(config.modem);
      std::vector<Complex> matched(count + 1U);
      const auto prefix = decoder.push_samples_matched(
          std::span<const Complex>(samples).first(samples.size() - 1U), matched);
      require(prefix.produced_symbols == count - 1U,
              "decoder emitted final symbol before its last required sample");
      const auto tail = decoder.push_samples_matched(
          std::span<const Complex>(samples).last(1), std::span(matched).subspan(prefix.produced_symbols));
      require(tail.produced_symbols == 1U,
              "drained block withheld final symbol at " + std::to_string(samples_per_symbol) + " samples/symbol");
      require(decoder.push_samples_matched({}, std::span(matched).last(1)).produced_symbols == 0U,
              "drained block emitted an extra symbol");
      for (std::size_t i = 0; i < count; ++i) {
        require(constellation.nearest_symbol(matched[i] / config.modem.tx_gain) == payload[i],
                "sample-support fixture corrupted a symbol");
      }
      std::cout << "simulated channel sample_support: samples_per_symbol=" << samples_per_symbol
                << " symbols=" << count << " seed=" << 0xC011AB1EU << '\n';
    }
  }
}

void test_clean_profiles() {
  // Use the acceptance matrix's radio boundary and profile settings. The
  // channel is null; acquisition, header validation and every payload symbol
  // must survive audio chunks unrelated to the symbol or header boundaries.
  for (const double bandwidth_hz : {24000.0, 10000.0}) {
    for (const auto& mode : modulation_cases) {
      auto config = make_config(mode.modulation);
      config.modem.bandwidth_hz = bandwidth_hz;
      config.modem.symbol_rate_hz.reset();
      config.modem.rrc_rolloff = 0.25;
      config.equalizer_training_sequence = make_default_qpsk_sequence(64, 0x5A5A0002U);
      config.carrier_correction = false;
      config.adaptive_equalization = true;
      const auto payload = make_payload(config, 1024);
      const auto encoded = encode(config, payload);
      std::vector<Complex> samples(17);
      samples.insert(samples.end(), encoded.begin(), encoded.end());
      for (const std::size_t chunk_size : {1U, 48U, 157U, 512U}) {
        RfStreamReceiver receiver(config);
        Reception reception;
        receive(receiver, samples, reception, chunk_size);
        check_payload(config, reception, payload);
        require(reception.symbols.size() == payload.size(), "clean profile emitted extra payload symbols");
        std::cout << "simulated channel clean_profile: bandwidth_hz=" << bandwidth_hz
                  << " modulation=" << mode.name << " chunk_samples=" << chunk_size
                  << " carrier_correction=0 adaptive_equalization=1 symbols=" << payload.size()
                  << " seed=" << 0xC011AB1EU << '\n';
      }
    }
  }
}

void test_acquisition() {
  const auto config = make_config();
  AcquisitionCorrelator correlator(config);
  const auto reference = correlator.reference_samples();
  std::vector<Complex> clean(17);
  clean.insert(clean.end(), reference.begin(), reference.end());
  clean.resize(clean.size() + 31);
  for (const double gain : {0.1, 0.5, 2.0}) {
    for (const double phase : {-std::numbers::pi, -1.2, 0.0, std::numbers::pi / 2.0}) {
      const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(reference),
          {.gain = gain, .phase_rad = phase, .snr_db = 40.0}, noise_seeds[0]);
      const auto result = correlator.scan(samples);
      require(result.found, "gain/phase/noise prevented preamble acquisition");
      require(result.sample_index == 17, "gain/phase/noise shifted acquisition timing");
      require(result.peak_metric > 0.95F, "gain/phase/noise degraded preamble metric");
    }
  }

  for (const double phase : {-std::numbers::pi, -1.2, 0.0, std::numbers::pi / 2.0}) {
    RfStreamReceiver receiver(config);
    std::array<RfStreamSymbol, 8> output{};
    const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(reference),
        {.phase_rad = phase}, noise_seeds[0]);
    const auto result = receiver.push_samples(samples, output);
    require(result.acquisition_found, "phase estimate did not acquire");
    require(std::abs(std::remainder(result.sync.carrier_phase_rad - phase, tau)) < 0.001,
            "carrier phase estimate incorrect");
    require(result.produced_symbols == 0 && !result.header_valid, "preamble alone emitted payload");
  }

  for (const double offset_hz : {-10.0, -0.5, 0.5, 10.0}) {
    RfStreamReceiver receiver(config);
    std::array<RfStreamSymbol, 8> output{};
    const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(reference),
        {.frequency_offset_hz = offset_hz}, noise_seeds[0]);
    const auto result = receiver.push_samples(samples, output);
    require(result.acquisition_found, "frequency offset prevented acquisition");
    // This is a coarse two-half estimate: nonuniform reference energy biases
    // the effective separation of the two halves. Allow 10% relative error.
    require(std::abs(result.sync.carrier_frequency_offset_hz - offset_hz) < 0.1 * std::abs(offset_hz),
            "carrier frequency estimate incorrect: expected " + std::to_string(offset_hz) +
                " Hz, got " + std::to_string(result.sync.carrier_frequency_offset_hz) + " Hz");
  }

  // End the first chunk on the rising correlation slope, three samples before
  // a full preamble is available. Acquisition must wait for the true peak.
  const auto payload = make_payload(config, 256);
  const auto stream = encode(config, payload);
  std::vector<Complex> delayed(17);
  delayed.insert(delayed.end(), stream.begin(), stream.end());
  const auto split = 17 + reference.size() - 3;
  RfStreamReceiver receiver(config);
  Reception reception;
  receive(receiver, std::span<const Complex>(delayed).first(split), reception, split);
  require(!reception.acquired, "receiver acquired on a rising correlation peak at a chunk boundary");
  receive(receiver, std::span<const Complex>(delayed).subspan(split), reception, 37);
  check_payload(config, reception, payload);
}

void test_noise_rejection() {
  const auto config = make_config();
  AcquisitionCorrelator correlator(config);

  // Calibrate the injected noise independently of decoding: E[|n|^2] = 0.01
  // at 20 dB SNR with unit reference power, split equally between I and Q.
  const std::vector<Complex> calibration_input(100000);
  const auto calibration = through_channel(calibration_input, config.modem.sample_rate_hz,
                                           1.0, {.snr_db = 20.0}, noise_seeds[0]);
  double i_power = 0.0;
  double q_power = 0.0;
  Complex mean{};
  for (const auto sample : calibration) {
    i_power += sample.real() * sample.real();
    q_power += sample.imag() * sample.imag();
    mean += sample;
  }
  require(std::abs(mean_power(calibration) - 0.01) < 0.0003, "AWGN power does not match configured SNR");
  require(std::abs(i_power / calibration.size() - 0.005) < 0.0002 &&
              std::abs(q_power / calibration.size() - 0.005) < 0.0002,
          "AWGN power is not split equally between I and Q");
  require(std::abs(mean / static_cast<float>(calibration.size())) < 0.001F, "AWGN mean is not near zero");
  const auto faded_noise = through_channel(calibration_input, config.modem.sample_rate_hz,
      1.0, {.gain = 0.0, .fade_depth_db = 20.0, .fade_rate_hz = 5.0, .snr_db = 20.0}, noise_seeds[0]);
  require(faded_noise == calibration, "fading scaled the receiver noise floor");

  const std::vector<Complex> silence(4096);
  require(!correlator.scan(silence).found, "silence falsely acquired");
  for (const auto seed : noise_seeds) {
    const auto noise = through_channel(silence, config.modem.sample_rate_hz, 1.0, {.snr_db = 0.0}, seed);
    require(!correlator.scan(noise).found, "noise falsely acquired");
    // No sidelobe comparison is possible in these short scan windows. Noise
    // must still be rejected even if the relative peak confidence is high.
    for (const auto extra : {0U, 17U, 48U}) {
      require(!correlator.scan(std::span<const Complex>(noise).first(
                  correlator.reference_samples().size() + extra)).found,
              "noise falsely acquired inside the sidelobe guard");
    }
    RfStreamReceiver receiver(config);
    Reception reception;
    receive(receiver, noise, reception);
    require(!reception.acquired && !reception.header_valid && reception.symbols.empty(),
            "noise accepted as an RF stream");
    require(receiver.state() == RfStreamState::search, "noise left receiver outside search state");
  }
}

void test_decoding(std::string_view family) {
  struct Case {
    std::string_view family;
    std::string_view name;
    Channel channel;
    double symbol_rate_hz = 9600.0;
  };
  for (const auto& mode : modulation_cases) {
    const double small_phase = mode.small_phase_degrees * tau / 360.0;
    const std::array cases = {
        Case{"noise", "AWGN", {.snr_db = mode.noise_snr_db}},
        Case{"noise", "AWGN at 24 ksym/s", {.snr_db = mode.noise_snr_db}, 24000.0},
        Case{"phase", "positive small phase", {.phase_rad = small_phase}},
        Case{"phase", "negative small phase", {.phase_rad = -small_phase}},
        Case{"phase", "+0.1 Hz carrier frequency offset", {.frequency_offset_hz = 0.1}},
        Case{"phase", "-0.1 Hz carrier frequency offset", {.frequency_offset_hz = -0.1}},
        Case{"phase", "+135 degrees, +30 Hz carrier frequency offset",
             {.phase_rad = 3.0 * tau / 8.0, .frequency_offset_hz = 30.0, .snr_db = mode.tracking_snr_db}},
        Case{"phase", "-135 degrees, -30 Hz carrier frequency offset",
             {.phase_rad = -3.0 * tau / 8.0, .frequency_offset_hz = -30.0, .snr_db = mode.tracking_snr_db}},
        Case{"phase", "180 degrees, carrier frequency drift 50 Hz/s",
             {.phase_rad = tau / 2.0, .frequency_offset_hz = 10.0, .frequency_rate_hz_per_second = 50.0,
              .snr_db = mode.tracking_snr_db}},
        Case{"fading", "smooth fade", {.fade_depth_db = mode.fade_depth_db, .fade_rate_hz = mode.fade_rate_hz}},
        Case{"combined", "fade/phase/noise",
             {.phase_rad = tau / 36.0, .fade_depth_db = mode.combined_fade_depth_db,
              .fade_rate_hz = mode.fade_rate_hz, .snr_db = mode.tracking_snr_db}},
    };
    for (const auto& test : cases) {
      if (test.family != family) {
        continue;
      }
      auto config = make_config(mode.modulation);
      config.modem.symbol_rate_hz = test.symbol_rate_hz;
      if (test.symbol_rate_hz == 24000.0) {
        config.modem.bandwidth_hz = 48000.0;
      }
      const auto payload = make_payload(config, 4096);
      const auto clean = encode(config, payload);
      // A clean control uses the identical payload and receiver settings.
      std::cout << mode.name << ' ' << test.name << " clean control" << std::endl;
      RfStreamReceiver control(config);
      Reception baseline;
      receive(control, clean, baseline);
      check_payload(config, baseline, payload);
      for (const auto seed : noise_seeds) {
        std::cout << mode.name << ' ' << test.name << " SNR=" << test.channel.snr_db
                  << " dB fade=" << test.channel.fade_depth_db << " dB seed=" << seed << std::endl;
        const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean), test.channel, seed);
        RfStreamReceiver receiver(config);
        Reception reception;
        receive(receiver, samples, reception, seed == noise_seeds[0] ? 37 : 157);
        check_payload(config, reception, payload);
      }
    }
  }
}

void test_loss_and_recovery(const ModulationCase& mode) {
  struct Case {
    std::string_view name;
    Channel channel;
  };
  // Simulated channel rejection/reacquisition regressions. Delayed echoes are
  // exercised by equalization tests: an improved equalizer may decode them,
  // so their mere presence cannot require a loss-of-lock event.
  const std::array cases = {
      Case{"complete fade with receiver noise", {.gain = 0.0, .snr_db = 24.0}},
      Case{"90 degree phase step", {.phase_rad = std::numbers::pi / 2.0}},
      Case{"noise burst at -10 dB SNR", {.snr_db = -10.0}},
  };
  const auto config = make_config(mode.modulation);
  const auto payload = make_payload(config, 2048);
  const auto clean = encode(config, payload);
  const auto split = clean.size() / 2;
  const auto recovery_payload = make_payload(config, 256);
  const auto recovery_clean = encode(config, recovery_payload, 9000);
  for (const auto& test : cases) {
    std::cout << mode.name << ' ' << test.name << std::endl;
    RfStreamReceiver receiver(config);
    Reception before;
    receive(receiver, std::span<const Complex>(clean).first(split), before);
    require(before.symbols.size() >= 512, "outage began before useful payload");
    check_payload(config, before, std::span<const std::uint32_t>(payload).first(before.symbols.size()));
    require(receiver.state() == RfStreamState::locked, "receiver not locked before impairment");

    auto channel = test.channel;
    // A frequency step starts with continuous phase at the transition.
    channel.phase_rad -= tau * channel.frequency_offset_hz * static_cast<double>(split) / config.modem.sample_rate_hz;
    const auto impaired = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean), channel, noise_seeds[0]);
    Reception during;
    receive(receiver, std::span<const Complex>(impaired).subspan(split), during);
    require(during.lock_lost, "severe impairment did not report lock loss");
    require(receiver.state() == RfStreamState::search && !receiver.header().has_value(),
            "severe impairment did not clear stale stream state");
    require(during.symbols.size() <= 2U * (config.pilot_interval_symbols + config.modem.filter_span_symbols),
            "receiver kept emitting symbols beyond two pilot intervals after impairment");
    const auto loss_budget = static_cast<std::size_t>(std::ceil(
        (2U * (config.pilot_interval_symbols + config.pilot_sequence.size()) + config.modem.filter_span_symbols) *
        describe(config.modem).samples_per_symbol)) + 157U;
    require(during.first_lock_loss_sample.has_value() && *during.first_lock_loss_sample <= loss_budget,
            "receiver reported lock loss too late (including one input chunk of observation delay)");

    const auto recovery = through_channel(recovery_clean, config.modem.sample_rate_hz, mean_power(recovery_clean),
        {.gain = 0.6, .phase_rad = -2.1, .frequency_offset_hz = -25.0, .snr_db = mode.tracking_snr_db}, noise_seeds[1]);
    Reception after;
    receive(receiver, recovery, after, 37);
    check_payload(config, after, recovery_payload, 9000);
  }
}

void test_equalization(const ModulationCase& mode) {
  for (const double delay_ms : {1.0, 3.0, 7.0}) {
    auto config = make_config(mode.modulation);
    config.equalizer_feedback_taps = static_cast<std::uint32_t>(std::ceil(
        delay_ms * derived_symbol_rate_hz(config.modem) / 1000.0)) + 8U;
    config.equalizer_training_sequence = make_default_qpsk_sequence(1024, 0x5A5A0002U);
    const auto payload = make_payload(config, 4096);
    const auto clean = encode(config, payload);
    const Channel channel{.phase_rad = 1.1, .frequency_offset_hz = 10.0, .snr_db = mode.tracking_snr_db,
                          .echo_delay_ms = delay_ms, .echo_gain = 0.45, .echo_frequency_offset_hz = 0.5};
    std::cout << mode.name << " adaptive equalization, delay=" << delay_ms << " ms clean control" << std::endl;
    RfStreamReceiver control(config);
    Reception baseline;
    receive(control, clean, baseline);
    check_payload(config, baseline, payload);
    for (const auto seed : noise_seeds) {
      std::cout << mode.name << " adaptive equalization, delay=" << delay_ms
                << " ms SNR=" << channel.snr_db << " dB seed=" << seed << std::endl;
      const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean), channel, seed);
      RfStreamReceiver receiver(config);
      Reception reception;
      receive(receiver, samples, reception, 37);
      check_payload(config, reception, payload);
      require(reception.sync.training_evm < 0.25F, "equalizer did not converge during training");

      if (seed == noise_seeds[0]) {
        // Same samples and wire configuration. QPSK may already tolerate this
        // echo, but must still show improved training error with equalization.
        auto bypass_config = config;
        bypass_config.adaptive_equalization = false;
        RfStreamReceiver uncorrected(bypass_config);
        Reception without_equalizer;
        receive(uncorrected, samples, without_equalizer);
        std::cout << "training EVM: equalized=" << reception.sync.training_evm
                  << " bypass=" << without_equalizer.sync.training_evm << std::endl;
        require(reception.sync.training_evm < 0.5F * without_equalizer.sync.training_evm,
                "equalization did not halve the training error");
        const bool all_correct = without_equalizer.symbols.size() >= payload.size() &&
            std::equal(payload.begin(), payload.end(), without_equalizer.symbols.begin(),
                [](std::uint32_t expected, const RfStreamSymbol& symbol) { return expected == symbol.value; });
        if (mode.modulation != Modulation::qpsk) {
          require(!all_correct, "echo test did not exercise the adaptive equalizer");
        }
      }
    }
  }
}

void test_carrier_step(const ModulationCase& mode) {
  std::cout << mode.name << " continuous-phase 10 Hz step" << std::endl;
  const auto config = make_config(mode.modulation);
  const auto payload = make_payload(config, 4096);
  const auto clean = encode(config, payload);
  const auto split = clean.size() / 2;
  RfStreamReceiver receiver(config);
  Reception reception;
  receive(receiver, std::span<const Complex>(clean).first(split), reception);
  const auto shifted = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean),
      {.phase_rad = -tau * 10.0 * static_cast<double>(split) / config.modem.sample_rate_hz,
       .frequency_offset_hz = 10.0}, noise_seeds[0]);
  receive(receiver, std::span<const Complex>(shifted).subspan(split), reception);
  check_payload(config, reception, payload);
}

void test_streaming_output(const ModulationCase& mode) {
  const auto config = make_config(mode.modulation);
  const auto payload = make_payload(config, 513);
  const auto clean = encode(config, payload);
  const auto samples = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean),
      {.phase_rad = -2.3, .frequency_offset_hz = -20.0, .snr_db = mode.tracking_snr_db}, noise_seeds[0]);
  for (const std::size_t output_size : {1U, 7U, 128U}) {
    std::cout << mode.name << " output capacity=" << output_size << std::endl;
    RfStreamReceiver receiver(config);
    std::vector<RfStreamSymbol> output(output_size);
    Reception reception;
    // All input is accepted immediately; repeated empty pushes must preserve
    // every queued symbol and all tracking state under output backpressure.
    for (std::size_t call = 0; call < payload.size() + 100 && reception.symbols.size() < payload.size(); ++call) {
      const auto result = receiver.push_samples(call == 0 ? std::span<const Complex>(samples) : std::span<const Complex>{}, output);
      require(result.consumed_samples == (call == 0 ? samples.size() : 0U), "streaming input count mismatch");
      require(result.produced_symbols != 0, "receiver stalled while draining queued symbols");
      reception.acquired |= result.acquisition_found;
      reception.header_valid |= result.header_valid;
      reception.lock_lost |= result.lock_lost;
      reception.symbols.insert(reception.symbols.end(), output.begin(), output.begin() + result.produced_symbols);
    }
    check_payload(config, reception, payload);

    receiver.reset();
    const auto second_clean = encode(config, payload, 9000);
    const auto second = through_channel(second_clean, config.modem.sample_rate_hz, mean_power(second_clean),
        {.gain = 0.7, .phase_rad = 2.1, .frequency_offset_hz = 25.0, .snr_db = mode.tracking_snr_db}, noise_seeds[1]);
    Reception after_reset;
    receive(receiver, second, after_reset, 37);
    check_payload(config, after_reset, payload, 9000);
  }
}

void test_tracking_config() {
  for (const auto& [forward, feedback] : {std::pair{0U, 4U}, std::pair{65U, 4U},
                                       std::pair{3U, 513U}, std::pair{3U, 32U}}) {
    auto config = make_config();
    config.equalizer_feedforward_taps = forward;
    config.equalizer_feedback_taps = feedback;
    bool rejected = false;
    try {
      RfStreamReceiver receiver(config);
    } catch (const std::invalid_argument&) {
      rejected = true;
    }
    require(rejected, "invalid equalizer span or insufficient training was accepted");
  }

  auto config = make_config();
  config.carrier_correction = false;
  config.adaptive_equalization = false;
  config.equalizer_feedforward_taps = 1;
  config.equalizer_feedback_taps = 0;
  const auto payload = make_payload(config, 256);
  const auto clean = encode(config, payload);
  RfStreamReceiver bypass(config);
  Reception clean_reception;
  receive(bypass, clean, clean_reception);
  check_payload(config, clean_reception, payload);

  // An arbitrary phase rotation requires actual correction. Disabling both
  // the NCO/PLL and the complex equalizer must disable that compensation.
  const auto rotated = through_channel(clean, config.modem.sample_rate_hz, mean_power(clean),
      {.phase_rad = 2.1, .frequency_offset_hz = 20.0}, noise_seeds[0]);
  bypass.reset();
  Reception rejected;
  receive(bypass, rotated, rejected);
  require(!rejected.header_valid && rejected.symbols.empty(), "tracking bypass still corrected the rotated stream");
}

void test_equalizer_decision_delay() {
  // Simulated channel; exact noise-free framing/alignment regression, seed
  // 0xC011AB1E. The delay changes modem residence, never message/frame indices.
  for (const auto& mode : modulation_cases) {
    for (const auto delay : {1U, 8U, 32U}) {
      auto config=make_config(mode.modulation);
      config.carrier_correction=false;
      config.recursive_equalization=true;
      config.equalizer_delay_symbols=delay;
      config.equalizer_feedforward_taps=2*delay+3;
      config.equalizer_feedback_taps=delay+4;
      config.equalizer_training_sequence=make_default_qpsk_sequence(256,0x5A5A0002);
      const auto payload=make_payload(config,1024);
      RfStreamReceiver receiver(config);Reception reception;
      receive(receiver,encode(config,payload),reception,37);
      check_payload(config,reception,payload);
    }
  }
}

void test_transmit_chunks() {
  for (const auto& mode : modulation_cases) {
    auto config=make_config(mode.modulation);
    config.modem.symbol_rate_hz=19200;
    config.modem.bandwidth_hz=24000;
    const auto payload=make_payload(config,1024);
    const auto reference=encode(config,payload);
    for(const auto chunk : {1U,2U,5U,48U,257U}) {
      const auto actual=encode(config,payload,7000,chunk);
      const auto mismatch=std::mismatch(actual.begin(),actual.end(),reference.begin(),reference.end());
      require(actual==reference,
              "transmit block size changed audio: chunk="+std::to_string(chunk)+
              " length="+std::to_string(actual.size())+" expected="+std::to_string(reference.size())+
              " first mismatch="+std::to_string(mismatch.first-actual.begin()));
    }
  }
}

} // namespace

int main(int argc, char** argv) {
  if (argc < 2 || argc > 3) {
    std::cerr << "usage: goblin_cannon_channel_tests acquisition|noise|phase|fading|combined|recovery|equalization|streaming|config|sample_support|profiles [--require-avx512]\n";
    return 2;
  }
  const std::string_view family(argv[1]);
  try {
    const auto isa = detail::active_demapper_isa();
    if (argc == 3) {
      require(std::string_view(argv[2]) == "--require-avx512", "unknown test option");
      require(isa == detail::DemapperIsa::avx512, "AVX-512 demapper dispatch is required for this test run");
    }
    std::cout << "demapper=" << (isa == detail::DemapperIsa::avx512 ? "AVX-512" :
                                 isa == detail::DemapperIsa::avx2 ? "AVX2" : "scalar") << '\n';
    if (family == "sample_support") {
      test_matched_filter_sample_support();
    } else if (family == "profiles") {
      test_clean_profiles();
    } else if (family == "decision_delay") {
      test_equalizer_decision_delay();
    } else if (family == "transmit_chunks") {
      test_transmit_chunks();
    } else if (family == "acquisition") {
      test_acquisition();
    } else if (family == "recovery") {
      for (const auto& mode : modulation_cases) {
        test_loss_and_recovery(mode);
      }
    } else if (family == "equalization") {
      for (const auto& mode : modulation_cases) {
        test_equalization(mode);
      }
    } else if (family == "streaming") {
      for (const auto& mode : modulation_cases) {
        test_streaming_output(mode);
      }
    } else if (family == "config") {
      test_tracking_config();
    } else if (family == "noise" || family == "phase" || family == "fading" || family == "combined") {
      if (family == "noise") {
        test_noise_rejection();
      }
      test_decoding(family);
      if (family == "phase") {
        for (const auto& mode : modulation_cases) {
          test_carrier_step(mode);
        }
      }
    } else {
      throw std::runtime_error("unknown channel test family");
    }
  } catch (const std::exception& error) {
    std::cerr << family << ": " << error.what() << '\n';
    return 1;
  }
  std::cout << family << " channel tests passed\n";
  return 0;
}
