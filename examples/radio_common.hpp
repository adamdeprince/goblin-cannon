#pragma once

#include "goblin_cannon/io.hpp"
#include "goblin_cannon/modem.hpp"

#include <pthread.h>
#include <sched.h>
#include <sys/mman.h>

#include <cerrno>
#include <cstring>
#include <iostream>
#include <stdexcept>
#include <string>
#include <thread>

namespace radio_example {

// Best-effort RT setup. Each step is silently skipped if the process lacks
// the necessary capability (CAP_SYS_NICE / CAP_IPC_LOCK) so the demo binaries
// still run as a normal user but get the kernel-side latency benefits when
// run with `setcap` or `sudo`.
inline void prepare_realtime_process(const char* label) {
  if (::mlockall(MCL_CURRENT | MCL_FUTURE) != 0) {
    std::cerr << label << ": mlockall skipped (" << std::strerror(errno) << ")\n";
  }
}

inline void promote_to_realtime(const char* label, int priority = 50, int cpu = -1) {
  sched_param sp{};
  sp.sched_priority = priority;
  if (::pthread_setschedparam(::pthread_self(), SCHED_FIFO, &sp) != 0) {
    std::cerr << label << ": SCHED_FIFO skipped (" << std::strerror(errno) << ")\n";
  }
  if (cpu >= 0) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(cpu, &set);
    if (::pthread_setaffinity_np(::pthread_self(), sizeof(set), &set) != 0) {
      std::cerr << label << ": pin to CPU " << cpu << " skipped (" << std::strerror(errno) << ")\n";
    }
  }
}

inline int parse_int_or(const std::string& value, int fallback) {
  try {
    return std::stoi(value);
  } catch (...) {
    return fallback;
  }
}

inline goblin_cannon::Modulation parse_modulation(const std::string& value) {
  if (value == "qpsk") {
    return goblin_cannon::Modulation::qpsk;
  }
  if (value == "8psk") {
    return goblin_cannon::Modulation::psk8;
  }
  if (value == "16qam") {
    return goblin_cannon::Modulation::qam16;
  }
  if (value == "64qam") {
    return goblin_cannon::Modulation::qam64;
  }
  if (value == "256qam") {
    return goblin_cannon::Modulation::qam256;
  }
  if (value == "1024qam") {
    return goblin_cannon::Modulation::qam1024;
  }
  if (value == "16qci" || value == "16-qci") {
    return goblin_cannon::Modulation::qci16;
  }
  if (value == "64qci" || value == "64-qci") {
    return goblin_cannon::Modulation::qci64;
  }
  if (value == "256qci" || value == "256-qci") {
    return goblin_cannon::Modulation::qci256;
  }
  if (value == "1024qci" || value == "1024-qci") {
    return goblin_cannon::Modulation::qci1024;
  }
  throw std::invalid_argument("unknown modulation: " + value);
}

inline goblin_cannon::SampleFormat parse_sample_format(const std::string& value) {
  if (value == "fc32_iq") {
    return goblin_cannon::SampleFormat::fc32_iq;
  }
  if (value == "sc16_iq") {
    return goblin_cannon::SampleFormat::sc16_iq;
  }
  if (value == "f32_stereo_iq") {
    return goblin_cannon::SampleFormat::f32_stereo_iq;
  }
  if (value == "s16_stereo_iq") {
    return goblin_cannon::SampleFormat::s16_stereo_iq;
  }
  throw std::invalid_argument("unknown sample format: " + value);
}

} // namespace radio_example
