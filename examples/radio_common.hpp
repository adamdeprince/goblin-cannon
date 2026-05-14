#pragma once

#include "wbhf_modem/io.hpp"
#include "wbhf_modem/modem.hpp"

#include <stdexcept>
#include <string>

namespace radio_example {

inline wbhf_modem::Modulation parse_modulation(const std::string& value) {
  if (value == "qpsk") {
    return wbhf_modem::Modulation::qpsk;
  }
  if (value == "8psk") {
    return wbhf_modem::Modulation::psk8;
  }
  if (value == "16qam") {
    return wbhf_modem::Modulation::qam16;
  }
  if (value == "64qam") {
    return wbhf_modem::Modulation::qam64;
  }
  if (value == "256qam") {
    return wbhf_modem::Modulation::qam256;
  }
  if (value == "1024qam") {
    return wbhf_modem::Modulation::qam1024;
  }
  throw std::invalid_argument("unknown modulation: " + value);
}

inline wbhf_modem::SampleFormat parse_sample_format(const std::string& value) {
  if (value == "fc32_iq") {
    return wbhf_modem::SampleFormat::fc32_iq;
  }
  if (value == "sc16_iq") {
    return wbhf_modem::SampleFormat::sc16_iq;
  }
  if (value == "f32_stereo_iq") {
    return wbhf_modem::SampleFormat::f32_stereo_iq;
  }
  if (value == "s16_stereo_iq") {
    return wbhf_modem::SampleFormat::s16_stereo_iq;
  }
  throw std::invalid_argument("unknown sample format: " + value);
}

} // namespace radio_example
