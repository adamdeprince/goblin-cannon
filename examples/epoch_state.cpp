#include "goblin_cannon/crypto.hpp"
#include <iostream>

int main(int argc, char** argv) {
  if (argc != 3 || std::string(argv[1]) != "init") {
    std::cerr << "Usage: goblin_cannon_epoch init PATH\nProvision once. Never replace this file while retaining the key.\n";
    return 2;
  }
  try {
    goblin_cannon::initialize_transmitter_epoch_store(argv[2]);
    std::cout << "Provisioned transmitter epoch journal. Set GOBLIN_CANNON_EPOCH_STATE to this path.\n";
  } catch (const std::exception& e) { std::cerr << e.what() << '\n'; return 1; }
}
