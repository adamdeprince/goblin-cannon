#pragma once

#include "goblin_cannon/rf_stream.hpp"

#include <stdexcept>

namespace goblin_cannon::detail {

inline ModemConfig differential_wire_config(const RfStreamConfig& config) {
  auto modem = config.modem;
  if (config.differential_mapping == DifferentialMapping::pi4_dqpsk) modem.modulation = Modulation::psk8;
  return modem;
}

// Differential information is decoded from adjacent equalized observations,
// not from differences between hard coherent decisions. No frequency estimate
// or phase-tracking loop is introduced. Absolute pilots restart the reference.
class DifferentialPsk {
public:
  explicit DifferentialPsk(const RfStreamConfig& config)
      : mode_(config.differential_mapping), constellation_(config.modem.modulation) {
    if ((mode_ == DifferentialMapping::dbpsk && config.modem.modulation != Modulation::bpsk) ||
        ((mode_ == DifferentialMapping::dqpsk || mode_ == DifferentialMapping::pi4_dqpsk) &&
         config.modem.modulation != Modulation::qpsk) ||
        static_cast<unsigned>(mode_) > static_cast<unsigned>(DifferentialMapping::pi4_dqpsk))
      throw std::invalid_argument("differential mapping requires its matching BPSK or QPSK payload");
  }

  void reset() { phase_ = 0; previous_ = {1, 0}; odd_ = false; }
  [[nodiscard]] bool enabled() const { return mode_ != DifferentialMapping::none; }
  std::uint32_t encode(std::uint32_t symbol) {
    if (!enabled()) return symbol;
    // Gray phase increments: DQPSK 00/01/11/10 -> 0/90/180/270 degrees.
    // pi/4 adds 45 degrees, giving 00/01/11/10 -> 45/135/225/315.
    const auto step = mode_ == DifferentialMapping::dbpsk ? 4U * symbol
        : 2U * (symbol ^ (symbol >> 1U)) + (mode_ == DifferentialMapping::pi4_dqpsk ? 1U : 0U);
    phase_ = (phase_ + step) % 8U;
    return wire_symbol();
  }
  std::uint32_t encode_pilot(std::uint32_t symbol) {
    if (!enabled()) return symbol;
    // Pilot numbers use the existing coherent constellation's wire mapping.
    phase_ = mode_ == DifferentialMapping::dbpsk ? symbol * 4U : qpsk_phase[symbol] * 2U;
    return wire_symbol();
  }
  void observe_pilot(Complex sample) { previous_ = sample; odd_ = false; }
  [[nodiscard]] Complex physical_rotation() const {
    return mode_ == DifferentialMapping::pi4_dqpsk && !odd_ ? pi4 : Complex{1, 0};
  }
  SymbolDecision decode(Complex sample) {
    if (!enabled()) return constellation_.decide(sample);
    auto delta = sample * std::conj(previous_);
    previous_ = sample;
    if (mode_ == DifferentialMapping::pi4_dqpsk) delta *= std::conj(pi4);
    auto decision = constellation_.decide(delta);
    if (mode_ != DifferentialMapping::dbpsk) {
      const auto phase = qpsk_phase[decision.symbol];
      decision.symbol = phase ^ (phase >> 1U);
    }
    odd_ = !odd_;
    return decision;
  }

private:
  std::uint32_t wire_symbol() const {
    if (mode_ == DifferentialMapping::dbpsk) return phase_ / 4U;
    // Inverses of the existing WBHF symbol-to-phase mappings. Preserve the
    // established coherent wire format while selecting a physical phase.
    static constexpr std::uint32_t qpsk_symbol[]{0, 3, 1, 2};
    static constexpr std::uint32_t psk8_symbol[]{1, 0, 2, 3, 7, 6, 4, 5};
    return mode_ == DifferentialMapping::dqpsk ? qpsk_symbol[phase_ / 2U] : psk8_symbol[phase_];
  }
  static constexpr std::uint32_t qpsk_phase[]{0, 2, 3, 1};
  static constexpr Complex pi4{0.7071067811865475F, 0.7071067811865475F};
  DifferentialMapping mode_;
  Constellation constellation_;
  std::uint32_t phase_ = 0;
  Complex previous_{1, 0};
  bool odd_ = false;
};

} // namespace goblin_cannon::detail
