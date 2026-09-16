#include "goblin_cannon/io.hpp"
#include "goblin_cannon/modem.hpp"

#include <array>
#include <cstdint>
#include <iostream>
#include <span>
#include <string>
#include <vector>

int main(int argc, char** argv) {
  using namespace goblin_cannon;

  const std::string payload = argc > 1 ? argv[1] : "Goblin Cannon loopback";

  FrameConfig cfg;
  cfg.modem.sample_rate_hz = 48000.0;
  cfg.modem.bandwidth_hz = 12000.0;
  cfg.modem.modulation = Modulation::qam64;
  cfg.modem.rrc_rolloff = 0.35;
  cfg.preamble_bytes = 96;

  FrameEncoder encoder(cfg);
  encoder.start_frame(static_cast<std::uint32_t>(payload.size()));

  std::vector<Complex> samples;
  std::array<Complex, 512> iq{};
  auto bytes = std::span<const std::uint8_t>(
      reinterpret_cast<const std::uint8_t*>(payload.data()), payload.size());
  std::size_t offset = 0;

  while (encoder.active()) {
    FrameEncodeResult r;
    if (offset < bytes.size()) {
      r = encoder.push_payload(bytes.subspan(offset), iq);
      offset += r.consumed_payload_bytes;
    } else {
      r = encoder.drain(iq);
    }
    samples.insert(samples.end(), iq.begin(), iq.begin() + static_cast<std::ptrdiff_t>(r.produced_samples));
  }

  FrameDecoder decoder(cfg);
  std::vector<std::uint8_t> decoded;
  std::array<std::uint8_t, 64> out{};
  bool complete = false;

  for (std::size_t i = 0; i < samples.size();) {
    const auto n = std::min<std::size_t>(128, samples.size() - i);
    const auto r = decoder.push_samples(std::span<const Complex>(samples).subspan(i, n), out);
    i += r.consumed_samples;
    decoded.insert(decoded.end(), out.begin(), out.begin() + static_cast<std::ptrdiff_t>(r.produced_payload_bytes));
    complete = complete || r.status == FrameStatus::frame_complete;
  }

  std::cout << "samples=" << samples.size()
            << " complete=" << (complete ? "yes" : "no")
            << " decoded=" << std::string(decoded.begin(), decoded.end()) << '\n';
  return complete ? 0 : 1;
}
