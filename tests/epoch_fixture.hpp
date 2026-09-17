#pragma once
#include "goblin_cannon/crypto.hpp"
#include <cstdlib>
#include <filesystem>
#include <stdexcept>
#include <string>

namespace goblin_cannon::test {
// Simulated channel only. Fresh isolated state makes seeded waveform tests
// repeatable; these fixture keys MUST NOT be used by an actual transmitter.
class EpochFixture {
public:
  EpochFixture() {
    char pattern[] = "/tmp/goblin-cannon-test-epoch.XXXXXX";
    const auto* directory = mkdtemp(pattern);
    if (!directory) throw std::runtime_error("cannot create epoch fixture");
    directory_ = directory;
    path = directory_ + "/epoch";
    initialize_transmitter_epoch_store(path);
    if (const auto* old = std::getenv("GOBLIN_CANNON_EPOCH_STATE")) previous_ = old;
    setenv("GOBLIN_CANNON_EPOCH_STATE", path.c_str(), 1);
  }
  ~EpochFixture() {
    if (previous_.empty()) unsetenv("GOBLIN_CANNON_EPOCH_STATE");
    else setenv("GOBLIN_CANNON_EPOCH_STATE", previous_.c_str(), 1);
    std::error_code error; std::filesystem::remove_all(directory_, error);
  }
  std::string path;
private:
  std::string directory_, previous_;
};
}
