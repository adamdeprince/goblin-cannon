#pragma once

#include "wbhf_modem/crypto.hpp"
#include "wbhf_modem/message_stream.hpp"
#include "wbhf_modem/symbols.hpp"

#include <array>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <functional>
#include <memory>
#include <mutex>
#include <optional>
#include <span>
#include <string>
#include <vector>

namespace wbhf_modem {

inline constexpr std::size_t control_symbol_count = market_symbol_count;
using PriceBank = std::array<std::uint64_t, control_symbol_count>;
using PriceBanks = std::array<PriceBank, 2>;
using OptionalPriceBanks = std::array<std::optional<PriceBank>, 2>;
using SymbolPermissionMask = std::array<std::uint8_t, symbol_permission_mask_bytes>;

struct ReceiverRestartConfig {
  RealtimePipelineConfig pipeline = {};
  double center_frequency_hz = 0.0;
  std::uint64_t generation = 0;
};

struct TransmitterRestartConfig {
  RealtimePipelineConfig pipeline = {};
  double center_frequency_hz = 0.0;
  std::uint64_t generation = 0;
};

struct ActiveBankState {
  std::uint8_t bank = 0;
  std::uint64_t generation = 0;
};

struct ReceiverControlSnapshot {
  Aes128Key aes_key = {};
  std::uint64_t key_generation = 0;
  ReceiverRestartConfig active_receiver = {};
  std::uint64_t restart_generation = 0;
  OptionalPriceBanks prices = {};
  std::array<std::uint64_t, 2> bank_generation = {};
  SymbolPermissionMask permissions = {};
  std::uint64_t permissions_generation = 0;
  std::optional<std::uint8_t> active_market_bank = std::nullopt;
  std::array<std::uint64_t, 2> market_bank_deactivation_generation = {};
};

struct TransmitterControlSnapshot {
  Aes128Key aes_key = {};
  std::uint64_t key_generation = 0;
  TransmitterRestartConfig active_transmitter = {};
  std::uint64_t restart_generation = 0;
  PriceBanks prices = {};
  std::array<std::uint64_t, 2> bank_generation = {};
  ActiveBankState active_bank = {};
};

class ReceiverControlState {
public:
  ReceiverControlState();
  explicit ReceiverControlState(RealtimePipelineConfig initial_pipeline);

  [[nodiscard]] ReceiverControlSnapshot snapshot() const;
  [[nodiscard]] Aes128Key aes_key() const;
  [[nodiscard]] std::uint64_t key_generation() const;
  [[nodiscard]] ReceiverRestartConfig active_receiver_config() const;
  [[nodiscard]] std::optional<ReceiverRestartConfig> take_pending_restart();
  [[nodiscard]] std::uint64_t price_units(std::uint8_t bank, std::uint8_t symbol_byte) const;
  [[nodiscard]] std::optional<PriceBank> bank_prices_units(std::uint8_t bank) const;
  [[nodiscard]] bool has_bank(std::uint8_t bank) const;
  [[nodiscard]] std::uint64_t bank_generation(std::uint8_t bank) const;
  [[nodiscard]] SymbolPermissionMask permissions() const;
  [[nodiscard]] std::uint64_t permissions_generation() const;
  [[nodiscard]] bool symbol_allowed(std::uint8_t symbol_byte) const;
  [[nodiscard]] bool accept_received_symbol(std::uint8_t bank, std::uint8_t symbol_byte);

  std::uint64_t update_encryption_key(Aes128Key key);
  ReceiverRestartConfig request_restart(ReceiverRestartConfig config);
  std::uint64_t update_bank(std::uint8_t bank, std::span<const std::uint64_t> prices);
  std::uint64_t replace_bank(std::uint8_t bank,
                             std::span<const std::uint64_t> prices,
                             std::uint64_t generation);
  void clear_banks();
  std::uint64_t update_permissions(std::span<const std::uint8_t> allowed_symbol_mask);

private:
  mutable std::mutex mutex_;
  Aes128Key aes_key_ = {};
  std::uint64_t key_generation_ = 0;
  ReceiverRestartConfig active_receiver_ = {};
  std::optional<ReceiverRestartConfig> pending_restart_ = std::nullopt;
  std::uint64_t restart_generation_ = 0;
  OptionalPriceBanks prices_ = {};
  std::array<std::uint64_t, 2> bank_generation_ = {};
  SymbolPermissionMask permissions_ = {};
  std::uint64_t permissions_generation_ = 0;
  std::optional<std::uint8_t> active_market_bank_ = std::nullopt;
  std::array<std::uint64_t, 2> market_bank_deactivation_generation_ = {};
};

class TransmitterControlState {
public:
  TransmitterControlState();
  explicit TransmitterControlState(RealtimePipelineConfig initial_pipeline);

  [[nodiscard]] TransmitterControlSnapshot snapshot() const;
  [[nodiscard]] Aes128Key aes_key() const;
  [[nodiscard]] std::uint64_t key_generation() const;
  [[nodiscard]] TransmitterRestartConfig active_transmitter_config() const;
  [[nodiscard]] std::optional<TransmitterRestartConfig> take_pending_restart();
  [[nodiscard]] std::uint64_t price_units(std::uint8_t bank, std::uint8_t symbol_byte) const;
  [[nodiscard]] PriceBank bank_prices_units(std::uint8_t bank) const;
  [[nodiscard]] std::uint64_t bank_generation(std::uint8_t bank) const;
  [[nodiscard]] ActiveBankState active_bank() const;
  [[nodiscard]] bool receiver_client_alive(std::uint8_t client_id,
                                           std::chrono::milliseconds timeout = std::chrono::milliseconds(3000)) const;
  [[nodiscard]] std::vector<std::uint8_t> live_receiver_clients(
      std::chrono::milliseconds timeout = std::chrono::milliseconds(3000)) const;

  std::uint64_t update_encryption_key(Aes128Key key);
  TransmitterRestartConfig request_restart(TransmitterRestartConfig config);
  std::uint64_t update_bank(std::uint8_t bank, std::span<const std::uint64_t> prices);
  ActiveBankState use_bank(std::uint8_t bank);
  void register_receiver_client(std::uint8_t client_id);
  void note_receiver_heartbeat(std::uint8_t client_id);
  void note_receiver_bank_delivered(std::uint8_t client_id, std::uint8_t bank, std::uint64_t generation);
  [[nodiscard]] bool live_receiver_clients_have_bank(
      std::uint8_t bank,
      std::uint64_t generation,
      std::chrono::milliseconds timeout = std::chrono::milliseconds(3000)) const;

private:
  mutable std::mutex mutex_;
  Aes128Key aes_key_ = {};
  std::uint64_t key_generation_ = 0;
  TransmitterRestartConfig active_transmitter_ = {};
  std::optional<TransmitterRestartConfig> pending_restart_ = std::nullopt;
  std::uint64_t restart_generation_ = 0;
  PriceBanks prices_ = {};
  std::array<std::uint64_t, 2> bank_generation_ = {};
  ActiveBankState active_bank_ = {};
  std::array<std::chrono::steady_clock::time_point, Clients> receiver_last_heartbeat_ = {};
  std::array<bool, Clients> receiver_seen_ = {};
  std::array<std::array<std::uint64_t, 2>, Clients> receiver_delivered_bank_generation_ = {};
};

class ControlledRealtimeReceiver {
public:
  explicit ControlledRealtimeReceiver(SpscRingBuffer<DelimitedMessage>& output);
  ControlledRealtimeReceiver(std::shared_ptr<ReceiverControlState> control,
                             SpscRingBuffer<DelimitedMessage>& output);
  ControlledRealtimeReceiver(RealtimePipelineConfig initial_pipeline,
                             SpscRingBuffer<DelimitedMessage>& output);

  [[nodiscard]] std::shared_ptr<ReceiverControlState> control_state() const noexcept { return control_; }
  [[nodiscard]] bool active() const noexcept { return receiver_ != nullptr; }

  void set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept;
  bool apply_pending_restart();
  [[nodiscard]] RealtimeReceiveResult push_samples(std::span<const Complex> samples);

private:
  std::shared_ptr<ReceiverControlState> control_;
  SpscRingBuffer<DelimitedMessage>& output_;
  std::unique_ptr<RealtimeReceiver> receiver_;
  DelimitedMessageObserver* observer_ = nullptr;
};

class ControlledRealtimeTransmitter {
public:
  explicit ControlledRealtimeTransmitter(SpscRingBuffer<DelimitedMessage>& input);
  ControlledRealtimeTransmitter(std::shared_ptr<TransmitterControlState> control,
                                SpscRingBuffer<DelimitedMessage>& input);
  ControlledRealtimeTransmitter(RealtimePipelineConfig initial_pipeline,
                                SpscRingBuffer<DelimitedMessage>& input);

  [[nodiscard]] std::shared_ptr<TransmitterControlState> control_state() const noexcept { return control_; }
  [[nodiscard]] bool active() const noexcept { return transmitter_ != nullptr; }

  bool apply_pending_restart();
  bool apply_active_bank();
  [[nodiscard]] RealtimeTransmitResult push_samples(std::span<Complex> out);

private:
  std::shared_ptr<TransmitterControlState> control_;
  SpscRingBuffer<DelimitedMessage>& input_;
  std::unique_ptr<RealtimeTransmitter> transmitter_;
  std::uint64_t observed_bank_generation_ = static_cast<std::uint64_t>(-1);
};

struct ReceiverControlServerConfig {
  std::string listen_address = "127.0.0.1:50051";
};

class ReceiverControlServer {
public:
  ReceiverControlServer(std::shared_ptr<ReceiverControlState> control,
                        ReceiverControlServerConfig config = {});
  ~ReceiverControlServer();

  ReceiverControlServer(const ReceiverControlServer&) = delete;
  ReceiverControlServer& operator=(const ReceiverControlServer&) = delete;
  ReceiverControlServer(ReceiverControlServer&&) noexcept;
  ReceiverControlServer& operator=(ReceiverControlServer&&) noexcept;

  void start();
  void stop();

  [[nodiscard]] bool running() const noexcept;
  [[nodiscard]] std::string bound_address() const;
  [[nodiscard]] std::shared_ptr<ReceiverControlState> control_state() const noexcept;

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

struct TransmitterControlServerConfig {
  std::string listen_address = "127.0.0.1:50052";
  std::shared_ptr<SpscRingBuffer<DelimitedMessage>> transmit_queue = {};
  std::shared_ptr<SpscRingBuffer<BidMessageLogRecord>> log_queue = {};
  std::shared_ptr<std::mutex> log_queue_mutex = {};
  std::function<std::optional<PriceBank>(std::uint8_t next_bank)> bank_price_provider = {};
  std::array<std::uint64_t, Clients> client_expected_latency_ns = {};
};

class TransmitterControlServer {
public:
  TransmitterControlServer(std::shared_ptr<TransmitterControlState> control,
                           TransmitterControlServerConfig config = {});
  ~TransmitterControlServer();

  TransmitterControlServer(const TransmitterControlServer&) = delete;
  TransmitterControlServer& operator=(const TransmitterControlServer&) = delete;
  TransmitterControlServer(TransmitterControlServer&&) noexcept;
  TransmitterControlServer& operator=(TransmitterControlServer&&) noexcept;

  void start();
  void stop();

  [[nodiscard]] bool running() const noexcept;
  [[nodiscard]] std::string bound_address() const;
  [[nodiscard]] std::shared_ptr<TransmitterControlState> control_state() const noexcept;

private:
  class Impl;
  std::unique_ptr<Impl> impl_;
};

} // namespace wbhf_modem
