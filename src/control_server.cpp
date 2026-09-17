#include "goblin_cannon/control_server.hpp"

#include "goblin_cannon/accounting.hpp"
#include "goblin_cannon/control/v1/receiver_control.grpc.pb.h"

#include <grpcpp/grpcpp.h>

#include <algorithm>
#include <atomic>
#include <chrono>
#include <cmath>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>
#include <thread>
#include <utility>
#include <vector>

namespace goblin_cannon {

namespace {

namespace pb = ::goblin_cannon::control::v1;

void validate_bank(std::uint8_t bank) {
  if (bank > 1U) {
    throw std::invalid_argument("bank must be 0 or 1");
  }
}

std::uint8_t parse_bank_value(std::uint32_t bank, std::string_view context) {
  if (bank > 1U) {
    throw std::invalid_argument(std::string(context) + " bank must be 0 or 1");
  }
  return static_cast<std::uint8_t>(bank);
}

void validate_price_symbol(std::uint8_t symbol_byte) {
  if (!is_market_symbol_byte(symbol_byte)) {
    (void)market_symbol_to_index(symbol_byte);
  }
}

SymbolPermissionMask allow_all_symbol_permissions() {
  SymbolPermissionMask mask{};
  mask.fill(0xFFU);
  const auto unused_bits = mask.size() * 8U - total_symbol_count;
  if (unused_bits != 0U) {
    mask.back() = static_cast<std::uint8_t>(mask.back() & (0xFFU >> unused_bits));
  }
  return mask;
}

bool symbol_allowed_by_mask(const SymbolPermissionMask& mask, std::uint8_t symbol_byte) {
  if (!is_symbol_byte(symbol_byte)) {
    return false;
  }
  const auto index = static_cast<std::size_t>(symbol_byte - symbol_min_byte);
  const auto byte_index = index / 8U;
  const auto bit_index = index % 8U;
  return (mask[byte_index] & (static_cast<std::uint8_t>(1U) << bit_index)) != 0U;
}

Modulation from_proto_modulation(pb::Modulation modulation) {
  switch (modulation) {
  case pb::MODULATION_BPSK:
    return Modulation::bpsk;
  case pb::MODULATION_QPSK:
    return Modulation::qpsk;
  case pb::MODULATION_8PSK:
    return Modulation::psk8;
  case pb::MODULATION_16QAM:
    return Modulation::qam16;
  case pb::MODULATION_64QAM:
    return Modulation::qam64;
  case pb::MODULATION_256QAM:
    return Modulation::qam256;
  case pb::MODULATION_1024QAM:
    return Modulation::qam1024;
  case pb::MODULATION_16QCI:
    return Modulation::qci16;
  case pb::MODULATION_64QCI:
    return Modulation::qci64;
  case pb::MODULATION_256QCI:
    return Modulation::qci256;
  case pb::MODULATION_1024QCI:
    return Modulation::qci1024;
  case pb::MODULATION_UNSPECIFIED:
  default:
    throw std::invalid_argument("restart request modulation is unspecified");
  }
}

std::vector<std::uint32_t> copy_u32_repeated(const google::protobuf::RepeatedField<std::uint32_t>& values) {
  return {values.begin(), values.end()};
}

std::vector<std::uint8_t> copy_puncture_pattern(const google::protobuf::RepeatedField<std::uint32_t>& values) {
  std::vector<std::uint8_t> pattern;
  pattern.reserve(static_cast<std::size_t>(values.size()));
  for (const auto value : values) {
    if (value > 1U) {
      throw std::invalid_argument("puncture_pattern entries must be 0 or 1");
    }
    pattern.push_back(static_cast<std::uint8_t>(value));
  }
  return pattern;
}

Aes128Key parse_key(std::string_view bytes) {
  if (bytes.size() != aes128_key_bytes) {
    throw std::invalid_argument("AES-128 key update must contain exactly 16 bytes");
  }
  Aes128Key key;
  std::copy(bytes.begin(), bytes.end(), key.bytes.begin());
  return key;
}

ReceiverRestartConfig parse_restart_request(const pb::RestartRequest& request) {
  if (!request.has_fec()) {
    throw std::invalid_argument("restart request must include convolutional FEC parameters");
  }
  if (request.sample_rate_hz() <= 0.0 || request.bandwidth_hz() <= 0.0) {
    throw std::invalid_argument("restart request sample_rate_hz and bandwidth_hz must be positive");
  }
  if (request.receiver_oversampling() > std::numeric_limits<std::uint8_t>::max()) {
    throw std::invalid_argument("restart request receiver_oversampling exceeds uint8 range");
  }
  if (request.header_repetition() > std::numeric_limits<std::uint8_t>::max()) {
    throw std::invalid_argument("restart request header_repetition exceeds uint8 range");
  }

  ReceiverRestartConfig config;
  config.center_frequency_hz = request.center_frequency_hz();
  config.pipeline.frame_counter_start = request.frame_counter_start();
  config.pipeline.rf.expected_schedule_epoch = request.expected_schedule_epoch();
  config.pipeline.rf.modem.sample_rate_hz = request.sample_rate_hz();
  config.pipeline.rf.modem.bandwidth_hz = request.bandwidth_hz();
  if (request.symbol_rate_hz() > 0.0) {
    config.pipeline.rf.modem.symbol_rate_hz = request.symbol_rate_hz();
  }
  config.pipeline.rf.modem.modulation = from_proto_modulation(request.modulation());
  config.pipeline.rf.modem.receiver_oversampling = static_cast<std::uint8_t>(request.receiver_oversampling());
  if (request.rrc_rolloff() > 0.0) {
    config.pipeline.rf.modem.rrc_rolloff = request.rrc_rolloff();
  }
  if (request.filter_span_symbols() != 0U) {
    config.pipeline.rf.modem.filter_span_symbols = request.filter_span_symbols();
  }

  config.pipeline.rf.symbols_per_frame = request.symbols_per_frame();
  config.pipeline.rf.pilot_interval_symbols = request.pilot_interval_symbols();
  config.pipeline.rf.header_repetition = static_cast<std::uint8_t>(request.header_repetition());
  config.pipeline.rf.acquisition_sequence = copy_u32_repeated(request.acquisition_sequence());
  config.pipeline.rf.equalizer_training_sequence = copy_u32_repeated(request.equalizer_training_sequence());
  config.pipeline.rf.pilot_sequence = copy_u32_repeated(request.pilot_sequence());
  config.pipeline.rf.acquisition_confidence_threshold = request.acquisition_confidence_threshold();
  config.pipeline.rf.pilot_confidence_threshold = request.pilot_confidence_threshold();
  config.pipeline.rf.symbol_confidence_threshold = request.symbol_confidence_threshold();
  if (request.has_carrier_correction()) {
    config.pipeline.rf.carrier_correction = request.carrier_correction();
  }
  if (request.has_adaptive_equalization()) {
    config.pipeline.rf.adaptive_equalization = request.adaptive_equalization();
  }
  if (request.has_sample_clock_recovery()) {
    config.pipeline.rf.sample_clock_recovery = request.sample_clock_recovery();
  }
  if (request.has_message_sequence_numbers()) {
    config.pipeline.sequence_numbers = request.message_sequence_numbers();
  }
  if (request.has_recursive_equalization()) {
    config.pipeline.rf.recursive_equalization = request.recursive_equalization();
  }
  if (request.has_equalizer_delay_symbols()) {
    config.pipeline.rf.equalizer_delay_symbols = request.equalizer_delay_symbols();
  }
  if (request.has_compact_header()) config.pipeline.rf.compact_header = request.compact_header();
  if (request.has_header_modulation()) config.pipeline.rf.header_modulation = from_proto_modulation(request.header_modulation());
  if (request.has_differential_mapping()) {
    switch (request.differential_mapping()) {
    case pb::DIFFERENTIAL_NONE: config.pipeline.rf.differential_mapping = DifferentialMapping::none; break;
    case pb::DIFFERENTIAL_DBPSK: config.pipeline.rf.differential_mapping = DifferentialMapping::dbpsk; break;
    case pb::DIFFERENTIAL_DQPSK: config.pipeline.rf.differential_mapping = DifferentialMapping::dqpsk; break;
    case pb::DIFFERENTIAL_PI4_DQPSK: config.pipeline.rf.differential_mapping = DifferentialMapping::pi4_dqpsk; break;
    default: throw std::invalid_argument("unknown differential mapping");
    }
  }
  if (request.has_recovery_interval_frames()) config.pipeline.rf.recovery_interval_frames = request.recovery_interval_frames();
  if (request.has_fractionally_spaced_equalization())
    config.pipeline.rf.fractionally_spaced_equalization = request.fractionally_spaced_equalization();
  if (request.has_equalizer_reselect_interval())
    config.pipeline.rf.equalizer_reselect_interval = request.equalizer_reselect_interval();
  if (request.has_equalizer_feedforward_taps()) {
    config.pipeline.rf.equalizer_feedforward_taps = request.equalizer_feedforward_taps();
  }
  if (request.has_equalizer_feedback_taps()) {
    config.pipeline.rf.equalizer_feedback_taps = request.equalizer_feedback_taps();
  }

  if (request.has_audio_waveform()) {
    switch (request.audio_waveform()) {
      case pb::AUDIO_SINGLE_CARRIER: config.pipeline.rf.waveform = AudioWaveform::single_carrier; break;
      case pb::AUDIO_FSK4: config.pipeline.rf.waveform = AudioWaveform::fsk4; break;
      case pb::AUDIO_FSK8: config.pipeline.rf.waveform = AudioWaveform::fsk8; break;
      case pb::AUDIO_BPSK_FREQUENCY_DIVERSITY: config.pipeline.rf.waveform = AudioWaveform::bpsk_frequency_diversity; break;
      default: throw std::invalid_argument("unknown audio waveform");
    }
  }
  if (request.has_fsk_useful_ms()) config.pipeline.rf.fsk_useful_ms = request.fsk_useful_ms();
  if (request.has_fsk_guard_ms()) config.pipeline.rf.fsk_guard_ms = request.fsk_guard_ms();
  if (request.has_diversity_wait_ms()) config.pipeline.rf.diversity_wait_ms = request.diversity_wait_ms();
  if (request.has_soft_demapping()) config.pipeline.rf.soft_demapping = request.soft_demapping();
  if (request.has_bch_payload()) config.pipeline.coding.bch = request.bch_payload();
  if (request.has_walsh_bits()) {
    if (request.walsh_bits() != 0 && request.walsh_bits() != 3) throw std::invalid_argument("Walsh requires zero or three bits");
    config.pipeline.coding.walsh_bits = request.walsh_bits();
  }
  if (request.has_interleaver_rows()) config.pipeline.coding.interleaver_rows = request.interleaver_rows();
  if (request.has_interleaver_columns()) config.pipeline.coding.interleaver_columns = request.interleaver_columns();
  validate(config.pipeline.coding);
  const auto& fec = request.fec();
  config.pipeline.convolutional.constraint_length = static_cast<std::uint8_t>(fec.constraint_length());
  config.pipeline.convolutional.generator0 = fec.generator0();
  config.pipeline.convolutional.generator1 = fec.generator1();
  config.pipeline.convolutional.generator2 = fec.generator2();
  config.pipeline.convolutional.puncture_pattern = copy_puncture_pattern(fec.puncture_pattern());
  config.pipeline.convolutional.decoded_bit_confidence_threshold = fec.decoded_bit_confidence_threshold();
  config.pipeline.sync_timestamp.enabled = request.sync_timestamp_enabled();
  config.pipeline.sync_timestamp.max_clock_skew_seconds = request.sync_timestamp_max_skew_seconds();

  validate(config.pipeline.rf);
  validate(config.pipeline.convolutional);
  if (config.pipeline.sync_timestamp.enabled) {
    const auto skew = config.pipeline.sync_timestamp.max_clock_skew_seconds;
    if (skew <= 0.0 || !std::isfinite(skew)) {
      throw std::invalid_argument("restart request timestamp skew must be positive when enabled");
    }
  }
  return config;
}

TransmitterRestartConfig parse_transmitter_restart_request(const pb::RestartRequest& request) {
  auto receiver_config = parse_restart_request(request);
  TransmitterRestartConfig config;
  config.pipeline = std::move(receiver_config.pipeline);
  config.center_frequency_hz = receiver_config.center_frequency_hz;
  config.generation = receiver_config.generation;
  return config;
}

std::vector<std::uint64_t> parse_bank_prices(const pb::BankUpdate& request) {
  if (request.prices_units_size() != static_cast<int>(control_symbol_count)) {
    throw std::invalid_argument("bank update must contain exactly " +
                                std::to_string(control_symbol_count) +
                                " market prices");
  }
  return {request.prices_units().begin(), request.prices_units().end()};
}

SymbolPermissionMask parse_permissions(const pb::PermissionsUpdate& request) {
  const auto& bytes = request.allowed_symbol_mask();
  if (bytes.size() != symbol_permission_mask_bytes) {
    throw std::invalid_argument("permissions mask must contain exactly " +
                                std::to_string(symbol_permission_mask_bytes) +
                                " bytes");
  }
  SymbolPermissionMask mask{};
  for (std::size_t i = 0; i < mask.size(); ++i) {
    mask[i] = static_cast<std::uint8_t>(bytes[i]);
  }
  const auto unused_bits = mask.size() * 8U - total_symbol_count;
  if (unused_bits != 0U) {
    mask.back() = static_cast<std::uint8_t>(mask.back() & (0xFFU >> unused_bits));
  }
  return mask;
}

DelimitedMessage parse_transmit_message(const pb::TransmitMessage& request) {
  const auto& payload = request.payload();
  if (payload.empty()) {
    throw std::invalid_argument("transmit message payload must not be empty");
  }
  const auto first = static_cast<std::uint8_t>(payload.front());
  if (first != 0U && first != 1U) {
    throw std::invalid_argument("transmit message must start with bank delimiter 0 or 1");
  }

  DelimitedMessage message;
  message.bytes.reserve(payload.size());
  for (const auto ch : payload) {
    message.bytes.push_back(static_cast<std::uint8_t>(ch));
  }
  for (std::size_t i = 1; i < message.bytes.size(); ++i) {
    if (message.bytes[i] == 0U || message.bytes[i] == 1U) {
      throw std::invalid_argument("transmit message body bytes must be in [2, 255]");
    }
  }
  return message;
}

void fill_bank_snapshot(std::uint8_t bank,
                        const PriceBank& prices,
                        std::uint64_t generation,
                        pb::BankSnapshot* response) {
  response->set_bank(bank);
  response->set_generation(generation);
  response->clear_prices_units();
  for (const auto price : prices) {
    response->add_prices_units(price);
  }
}

void fill_bank_update(std::uint8_t bank,
                      const PriceBank& prices,
                      std::uint64_t generation,
                      pb::BankUpdate* update) {
  update->set_bank(bank);
  update->set_generation(generation);
  update->clear_prices_units();
  for (const auto price : prices) {
    update->add_prices_units(price);
  }
}

std::uint64_t unix_micros_now() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::microseconds>(now).count());
}

std::uint64_t unix_nanos_now() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

grpc::Status invalid_argument_status(const std::exception& exception) {
  return {grpc::StatusCode::INVALID_ARGUMENT, exception.what()};
}

class ReceiverControlService final : public pb::ReceiverControl::Service {
public:
  explicit ReceiverControlService(std::shared_ptr<ReceiverControlState> control)
      : control_(std::move(control)) {}

  grpc::Status UpdateEncryptionKey(grpc::ServerContext*,
                                   const pb::EncryptionKeyUpdate* request,
                                   pb::ControlAck* response) override {
    try {
      const auto key = parse_key(request->aes128_key());
      const auto generation = control_->update_encryption_key(key);
      response->set_ok(true);
      response->set_message("key updated");
      response->set_generation(generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status Restart(grpc::ServerContext*,
                       const pb::RestartRequest* request,
                       pb::ControlAck* response) override {
    try {
      auto config = parse_restart_request(*request);
      const auto active = control_->request_restart(std::move(config));
      response->set_ok(true);
      response->set_message("receiver restart scheduled");
      response->set_generation(active.generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status UpdateBank(grpc::ServerContext*,
                          const pb::BankUpdate* request,
                          pb::ControlAck* response) override {
    try {
      const auto bank = parse_bank_value(request->bank(), "bank update");
      const auto prices = parse_bank_prices(*request);
      const auto generation = control_->update_bank(bank, prices);
      response->set_ok(true);
      response->set_message("bank updated");
      response->set_generation(generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status GetBank(grpc::ServerContext*,
                       const pb::BankSelect* request,
                       pb::BankSnapshot* response) override {
    try {
      const auto bank = parse_bank_value(request->bank(), "get bank");
      const auto prices = control_->bank_prices_units(bank);
      if (!prices.has_value()) {
        return {grpc::StatusCode::FAILED_PRECONDITION, "receiver bank cache is undefined"};
      }
      fill_bank_snapshot(bank, *prices, control_->bank_generation(bank), response);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status Permissions(grpc::ServerContext*,
                           const pb::PermissionsUpdate* request,
                           pb::ControlAck* response) override {
    try {
      const auto mask = parse_permissions(*request);
      const auto generation = control_->update_permissions(mask);
      response->set_ok(true);
      response->set_message("permissions updated");
      response->set_generation(generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

private:
  std::shared_ptr<ReceiverControlState> control_;
};

class TransmitterControlService final : public pb::TransmitterControl::Service {
public:
  TransmitterControlService(std::shared_ptr<TransmitterControlState> control,
                            std::shared_ptr<TransmitMessageQueue> transmit_queue,
                            std::shared_ptr<SpscRingBuffer<BidMessageLogRecord>> log_queue,
                            std::shared_ptr<std::mutex> log_queue_mutex,
                            std::function<std::optional<PriceBank>(std::uint8_t)> bank_price_provider,
                            std::array<std::uint64_t, Clients> client_expected_latency_ns,
                            std::shared_ptr<ClientBudgetAccounting> accounting,
                            std::shared_ptr<CanonicalMessageBroadcaster> canonical_messages)
      : control_(std::move(control)),
        transmit_queue_(std::move(transmit_queue)),
        log_queue_(std::move(log_queue)),
        log_queue_mutex_(log_queue_mutex ? std::move(log_queue_mutex) : std::make_shared<std::mutex>()),
        bank_price_provider_(std::move(bank_price_provider)),
        client_expected_latency_ns_(client_expected_latency_ns),
        accounting_(std::move(accounting)),
        canonical_messages_(std::move(canonical_messages)) {
    if (transmit_queue_) transmit_queue_->set_decision_log_mutex(log_queue_mutex_);
  }

  grpc::Status UpdateEncryptionKey(grpc::ServerContext*,
                                   const pb::EncryptionKeyUpdate* request,
                                   pb::ControlAck* response) override {
    try {
      const auto key = parse_key(request->aes128_key());
      const auto generation = control_->update_encryption_key(key);
      response->set_ok(true);
      response->set_message("key updated");
      response->set_generation(generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status Restart(grpc::ServerContext*,
                       const pb::RestartRequest* request,
                       pb::ControlAck* response) override {
    try {
      auto config = parse_transmitter_restart_request(*request);
      const auto active = control_->request_restart(std::move(config));
      response->set_ok(true);
      response->set_message("transmitter restart scheduled");
      response->set_generation(active.generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status UpdateBank(grpc::ServerContext*,
                          const pb::BankUpdate* request,
                          pb::ControlAck* response) override {
    try {
      const auto bank = parse_bank_value(request->bank(), "bank update");
      const auto prices = parse_bank_prices(*request);
      const auto generation = control_->update_bank(bank, prices);
      response->set_ok(true);
      response->set_message("bank updated");
      response->set_generation(generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status GetBank(grpc::ServerContext*,
                       const pb::BankSelect* request,
                       pb::BankSnapshot* response) override {
    try {
      const auto bank = parse_bank_value(request->bank(), "get bank");
      fill_bank_snapshot(bank,
                         control_->bank_prices_units(bank),
                         control_->bank_generation(bank),
                         response);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status UseBank(grpc::ServerContext*,
                       const pb::UseBankRequest* request,
                       pb::ControlAck* response) override {
    try {
      const auto bank = parse_bank_value(request->bank(), "use bank");
      const auto active = control_->use_bank(bank);
      response->set_ok(true);
      response->set_message("active transmit bank updated");
      response->set_generation(active.generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status BankSwitch(grpc::ServerContext*,
                          const pb::BankSwitchRequest*,
                          pb::ControlAck* response) override {
    try {
      const auto current = control_->active_bank();
      const auto next_bank = static_cast<std::uint8_t>(current.bank ^ 1U);
      std::uint64_t target_generation = 0;
      if (bank_price_provider_) {
        const auto prices = bank_price_provider_(next_bank);
        if (!prices.has_value()) {
          return {grpc::StatusCode::FAILED_PRECONDITION, "bank price provider returned no next-bank cache"};
        }
        target_generation = control_->update_bank(next_bank, *prices);
      } else {
        target_generation = control_->bank_generation(next_bank);
      }
      if (target_generation == 0U) {
        return {grpc::StatusCode::FAILED_PRECONDITION, "next bank has no transmitter cache"};
      }

      const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(1500);
      while (!control_->live_receiver_clients_have_bank(next_bank, target_generation) &&
             std::chrono::steady_clock::now() < deadline) {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
      }
      if (!control_->live_receiver_clients_have_bank(next_bank, target_generation)) {
        return {grpc::StatusCode::DEADLINE_EXCEEDED, "not all live receivers received next-bank cache"};
      }

      const auto active = control_->use_bank(next_bank);
      response->set_ok(true);
      response->set_message("active transmit bank switched");
      response->set_generation(active.generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status EnqueueMessage(grpc::ServerContext*,
                              const pb::TransmitMessage* request,
                              pb::ControlAck* response) override {
    if (!transmit_queue_) {
      return {grpc::StatusCode::FAILED_PRECONDITION, "transmitter transmit queue is not configured"};
    }
    try {
      auto message = parse_transmit_message(*request);
      auto payload = message.bytes;
      auto bid_cents = request->bid_cents();
      if (bid_cents == 0U && payload.size() >= 2U && is_market_symbol_byte(payload[1])) {
        bid_cents = 100U;
      }
      if (payload.size() >= 2U && is_client_symbol_byte(payload[1])) {
        const auto client_id = client_symbol_to_id(payload[1]);
        if (!control_->receiver_client_alive(client_id)) {
          return {grpc::StatusCode::FAILED_PRECONDITION, "client receiver heartbeat is stale"};
        }
      }
      if (!log_queue_) {
        if (!transmit_queue_->try_push(std::move(message))) {
          return {grpc::StatusCode::RESOURCE_EXHAUSTED, "transmitter transmit queue is full"};
        }
        response->set_ok(true);
        response->set_message("message enqueued");
        response->set_generation(control_->active_bank().generation);
        return grpc::Status::OK;
      }

      const auto bid_client_id = payload.size() >= 2U && is_client_symbol_byte(payload[1])
          ? client_symbol_to_id(payload[1])
          : static_cast<std::uint8_t>(0U);
      BidMessage bid_message{.payload = payload,
                             .bid_price = bid_cents,
                             .client_id = bid_client_id,
                             .has_client_id = false,
                             .reply_ip = {},
                             .reply_port = 0};
      BidMessageIntakeResult intake_result;
      {
        std::scoped_lock lock(enqueue_intake_mutex_);
        if (log_queue_mutex_) {
          std::scoped_lock log_lock(*log_queue_mutex_);
          intake_result = enqueue_intake_.submit(std::move(bid_message), *transmit_queue_, *log_queue_);
        } else {
          intake_result = enqueue_intake_.submit(std::move(bid_message), *transmit_queue_, *log_queue_);
        }
      }
      if (intake_result.log_backpressure) {
        return {grpc::StatusCode::RESOURCE_EXHAUSTED, "transmitter log queue is full"};
      }
      if (!intake_result.transmitted && !intake_result.queued_for_arbitration) {
        if (intake_result.transmit_backpressure &&
            intake_result.pending_bids == 0U &&
            intake_result.logged_records == 0U) {
          return {grpc::StatusCode::RESOURCE_EXHAUSTED, "transmitter transmit queue is full"};
        }
        response->set_ok(false);
        response->set_message("message rejected by bid arbitration");
        response->set_generation(control_->active_bank().generation);
        return grpc::Status::OK;
      }
      if (intake_result.transmitted) {
        log_enqueued_message(std::move(payload), bid_cents);
      }
      response->set_ok(true);
      response->set_message(intake_result.transmitted ? "message enqueued" : "message queued for arbitration");
      response->set_generation(control_->active_bank().generation);
      return grpc::Status::OK;
    } catch (const std::exception& exception) {
      return invalid_argument_status(exception);
    }
  }

  grpc::Status ReceiverSession(
      grpc::ServerContext* context,
      grpc::ServerReaderWriter<pb::ReceiverSessionServerMessage, pb::ReceiverSessionClientMessage>* stream) override {
    pb::ReceiverSessionClientMessage first;
    if (!stream->Read(&first) || !first.has_hello()) {
      return {grpc::StatusCode::INVALID_ARGUMENT, "receiver session must start with hello"};
    }
    if (first.hello().client_id() >= Clients) {
      return {grpc::StatusCode::INVALID_ARGUMENT, "receiver client_id outside Clients range"};
    }

    const auto client_id = static_cast<std::uint8_t>(first.hello().client_id());
    control_->register_receiver_client(client_id);
    std::array<std::uint64_t, 2> sent_bank_generation{};
    std::uint64_t sent_active_bank_generation = 0;
    std::uint64_t sent_canonical_sequence =
        canonical_messages_ ? canonical_messages_->current_sequence() : 0U;
    std::atomic_bool stream_open = true;

    auto write_heartbeat = [&]() {
      pb::ReceiverSessionServerMessage out;
      out.mutable_heartbeat()->set_unix_micros(unix_micros_now());
      return stream->Write(out);
    };
    auto maybe_write_active_bank = [&]() {
      const auto active = control_->active_bank();
      if (active.generation == sent_active_bank_generation) {
        return true;
      }
      pb::ReceiverSessionServerMessage out;
      out.mutable_active_bank()->set_bank(active.bank);
      if (!stream->Write(out)) {
        return false;
      }
      sent_active_bank_generation = active.generation;
      return true;
    };
    auto maybe_write_bank = [&](std::uint8_t bank, bool force) {
      const auto generation = control_->bank_generation(bank);
      if (generation == 0U || (!force && generation == sent_bank_generation[bank])) {
        return true;
      }
      const auto prices = control_->bank_prices_units(bank);
      pb::ReceiverSessionServerMessage out;
      fill_bank_update(bank, prices, generation, out.mutable_bank_update());
      if (!stream->Write(out)) {
        return false;
      }
      sent_bank_generation[bank] = generation;
      control_->note_receiver_bank_delivered(client_id, bank, generation);
      return true;
    };
    auto collect_canonical_batch = [&]() {
      std::vector<CanonicalMessageRecord> records;
      if (!canonical_messages_) {
        return records;
      }
      records = canonical_messages_->wait_for_messages_after(sent_canonical_sequence,
                                                             128U,
                                                             std::chrono::milliseconds(100));
      if (records.empty() || records.size() >= 128U) {
        return records;
      }

      const auto deadline = std::chrono::steady_clock::now() + std::chrono::milliseconds(100);
      while (records.size() < 128U && std::chrono::steady_clock::now() < deadline) {
        const auto remaining = std::chrono::duration_cast<std::chrono::milliseconds>(
            deadline - std::chrono::steady_clock::now());
        const auto expanded = canonical_messages_->wait_for_messages_after(
            sent_canonical_sequence,
            128U,
            std::max(std::chrono::milliseconds(1), remaining));
        if (expanded.size() <= records.size()) {
          break;
        }
        records = std::move(expanded);
      }
      return records;
    };
    auto maybe_write_canonical_batch = [&]() {
      auto records = collect_canonical_batch();
      if (records.empty()) {
        return true;
      }
      pb::ReceiverSessionServerMessage out;
      auto* batch = out.mutable_canonical_messages();
      batch->set_first_sequence(records.front().sequence);
      batch->set_transmitter_unix_nanos(records.front().transmitter_unix_nanos);
      for (const auto& record : records) {
        batch->add_payload(reinterpret_cast<const char*>(record.payload.data()),
                           record.payload.size());
      }
      if (!stream->Write(out)) {
        return false;
      }
      sent_canonical_sequence = records.back().sequence;
      return true;
    };

    std::thread reader([&] {
      pb::ReceiverSessionClientMessage message;
      while (stream_open.load(std::memory_order_acquire) && stream->Read(&message)) {
        if (message.has_heartbeat()) {
          control_->note_receiver_heartbeat(client_id);
        } else if (message.has_client_message()) {
          log_receiver_client_message(message.client_message());
        } else if (message.has_signal_event()) {
          log_receiver_signal_event(message.signal_event());
        } else if (message.has_hello()) {
          continue;
        }
      }
      stream_open.store(false, std::memory_order_release);
    });

    const auto active = control_->active_bank();
    bool write_ok = maybe_write_bank(active.bank, true) && maybe_write_active_bank() && write_heartbeat();
    auto last_heartbeat = std::chrono::steady_clock::now();
    while (write_ok && stream_open.load(std::memory_order_acquire) && !context->IsCancelled()) {
      const auto current_active = control_->active_bank().bank;
      const auto inactive_bank = static_cast<std::uint8_t>(current_active ^ 1U);
      write_ok = maybe_write_bank(current_active, true) &&
                 maybe_write_bank(inactive_bank, false) &&
                 maybe_write_active_bank();
      if (!write_ok) {
        break;
      }
      const auto now = std::chrono::steady_clock::now();
      if (now - last_heartbeat >= std::chrono::seconds(1)) {
        write_ok = write_heartbeat();
        last_heartbeat = now;
        if (!write_ok) {
          break;
        }
      }
      write_ok = maybe_write_canonical_batch();
    }

    stream_open.store(false, std::memory_order_release);
    context->TryCancel();
    if (reader.joinable()) {
      reader.join();
    }
    return grpc::Status::OK;
  }

private:
  void push_log(BidMessageLogRecord record) {
    if (!log_queue_) {
      return;
    }
    if (record.local_timestamp_ns == 0U) {
      record.local_timestamp_ns = unix_nanos_now();
    }
    if (log_queue_mutex_) {
      std::scoped_lock lock(*log_queue_mutex_);
      (void)log_queue_->try_push(std::move(record));
    } else {
      (void)log_queue_->try_push(std::move(record));
    }
  }

  void log_enqueued_message(std::vector<std::uint8_t> payload, std::uint64_t bid_cents) {
    BidMessageLogRecord record;
    record.event_type = LogEventType::transmitter_enqueue;
    record.local_timestamp_ns = unix_nanos_now();
    record.payload = std::move(payload);
    record.status = BidMessageLogStatus::sent;
    record.bid_price = bid_cents;
    record.winning_bid_price = bid_cents;
    push_log(std::move(record));
  }

  void log_receiver_client_message(const pb::ReceivedClientMessage& message) {
    if (message.client_id() >= Clients) {
      return;
    }
    const auto now = unix_nanos_now();
    const auto receiver_timestamp = message.receiver_unix_nanos();
    const auto observed_latency = now >= receiver_timestamp ? now - receiver_timestamp : 0U;
    const auto payload = message.wire_payload();
    DeliveryAccountingResult accounting_result;
    if (accounting_) {
      const auto payload_bytes = std::span<const std::uint8_t>(
          reinterpret_cast<const std::uint8_t*>(payload.data()),
          payload.size());
      accounting_result = accounting_->acknowledge_delivery(payload_bytes,
                                                            static_cast<std::uint8_t>(message.client_id()),
                                                            receiver_timestamp);
    }
    BidMessageLogRecord record;
    record.event_type = LogEventType::receiver_client_message;
    record.local_timestamp_ns = now;
    record.receiver_timestamp_ns = receiver_timestamp;
    record.payload = std::vector<std::uint8_t>(payload.begin(), payload.end());
    record.status = accounting_result.matched ? BidMessageLogStatus::delivery_matched
                                              : BidMessageLogStatus::delivery_unmatched;
    record.client_id = static_cast<std::uint8_t>(message.client_id());
    record.has_client_id = true;
    record.expected_latency_ns = client_expected_latency_ns_[message.client_id()];
    record.observed_latency_ns = observed_latency;
    record.bid_price = accounting_result.bid_cents;
    record.remaining_budget_cents = accounting_result.remaining_budget_cents;
    record.matched_timestamp_ns = accounting_result.matched_timestamp_ns;
    push_log(std::move(record));
  }

  void log_receiver_signal_event(const pb::ReceiverSignalEvent& event) {
    const auto now = unix_nanos_now();
    const auto receiver_timestamp = event.receiver_unix_nanos();
    const auto observed_latency = now >= receiver_timestamp ? now - receiver_timestamp : 0U;
    BidMessageLogRecord record;
    record.event_type = LogEventType::receiver_signal;
    record.local_timestamp_ns = now;
    record.receiver_timestamp_ns = receiver_timestamp;
    record.observed_latency_ns = observed_latency;
    record.event_name = event.event_type();
    record.detail = event.detail();
    record.metric = event.metric();
    record.count = event.count();
    push_log(std::move(record));
  }

  std::shared_ptr<TransmitterControlState> control_;
  std::shared_ptr<TransmitMessageQueue> transmit_queue_;
  std::shared_ptr<SpscRingBuffer<BidMessageLogRecord>> log_queue_;
  std::shared_ptr<std::mutex> log_queue_mutex_;
  std::function<std::optional<PriceBank>(std::uint8_t)> bank_price_provider_;
  std::array<std::uint64_t, Clients> client_expected_latency_ns_ = {};
  std::shared_ptr<ClientBudgetAccounting> accounting_;
  std::shared_ptr<CanonicalMessageBroadcaster> canonical_messages_;
  BidMessageTransmitIntake enqueue_intake_;
  std::mutex enqueue_intake_mutex_;
};

std::string host_from_listen_address(const std::string& listen_address) {
  const auto colon = listen_address.rfind(':');
  if (colon == std::string::npos || colon == 0U) {
    return "127.0.0.1";
  }
  return listen_address.substr(0, colon);
}

} // namespace

CanonicalMessageBroadcaster::CanonicalMessageBroadcaster(std::size_t retained_messages)
    : retained_messages_(retained_messages) {
  if (retained_messages_ == 0U) {
    throw std::invalid_argument("canonical broadcaster retained_messages must be positive");
  }
}

void CanonicalMessageBroadcaster::on_delimited_message(const DelimitedMessage& message) {
  CanonicalMessageRecord record;
  record.transmitter_unix_nanos = unix_nanos_now();
  record.payload = message.bytes;
  {
    std::scoped_lock lock(mutex_);
    record.sequence = next_sequence_++;
    messages_.push_back(std::move(record));
    while (messages_.size() > retained_messages_) {
      messages_.pop_front();
    }
  }
  cv_.notify_all();
}

std::uint64_t CanonicalMessageBroadcaster::current_sequence() const {
  std::scoped_lock lock(mutex_);
  return next_sequence_ - 1U;
}

std::vector<CanonicalMessageRecord> CanonicalMessageBroadcaster::messages_after(
    std::uint64_t last_sequence,
    std::size_t max_messages) const {
  std::vector<CanonicalMessageRecord> out;
  if (max_messages == 0U) {
    return out;
  }
  std::scoped_lock lock(mutex_);
  for (const auto& message : messages_) {
    if (message.sequence <= last_sequence) {
      continue;
    }
    out.push_back(message);
    if (out.size() == max_messages) {
      break;
    }
  }
  return out;
}

std::vector<CanonicalMessageRecord> CanonicalMessageBroadcaster::wait_for_messages_after(
    std::uint64_t last_sequence,
    std::size_t max_messages,
    std::chrono::milliseconds timeout) const {
  if (max_messages == 0U) {
    return {};
  }

  std::unique_lock lock(mutex_);
  const auto has_new_message = [&] {
    return !messages_.empty() && messages_.back().sequence > last_sequence;
  };
  if (!has_new_message()) {
    cv_.wait_for(lock, timeout, has_new_message);
  }

  std::vector<CanonicalMessageRecord> out;
  for (const auto& message : messages_) {
    if (message.sequence <= last_sequence) {
      continue;
    }
    out.push_back(message);
    if (out.size() == max_messages) {
      break;
    }
  }
  return out;
}

ReceiverControlState::ReceiverControlState()
    : permissions_(allow_all_symbol_permissions()) {}

ReceiverControlState::ReceiverControlState(RealtimePipelineConfig initial_pipeline)
    : permissions_(allow_all_symbol_permissions()) {
  active_receiver_.pipeline = std::move(initial_pipeline);
  aes_key_ = active_receiver_.pipeline.aes_key;
  pending_restart_ = active_receiver_;
  has_pending_restart_.store(true, std::memory_order_release);
}

ReceiverControlSnapshot ReceiverControlState::snapshot() const {
  std::scoped_lock lock(mutex_);
  return {.aes_key = aes_key_,
          .key_generation = key_generation_,
          .active_receiver = active_receiver_,
          .restart_generation = restart_generation_,
          .prices = prices_,
          .bank_generation = bank_generation_,
          .permissions = permissions_,
          .permissions_generation = permissions_generation_,
          .active_market_bank = active_market_bank_,
          .market_bank_deactivation_generation = market_bank_deactivation_generation_};
}

Aes128Key ReceiverControlState::aes_key() const {
  std::scoped_lock lock(mutex_);
  return aes_key_;
}

std::uint64_t ReceiverControlState::key_generation() const {
  std::scoped_lock lock(mutex_);
  return key_generation_;
}

ReceiverRestartConfig ReceiverControlState::active_receiver_config() const {
  std::scoped_lock lock(mutex_);
  return active_receiver_;
}

std::optional<ReceiverRestartConfig> ReceiverControlState::take_pending_restart() {
  // Lock-free fast path: no pending restart, no mutex acquisition. The DSP
  // thread calls this every chunk; in steady state it stays lock-free.
  if (!has_pending_restart_.load(std::memory_order_acquire)) {
    return std::nullopt;
  }
  std::scoped_lock lock(mutex_);
  auto restart = std::move(pending_restart_);
  pending_restart_.reset();
  has_pending_restart_.store(false, std::memory_order_release);
  return restart;
}

std::uint64_t ReceiverControlState::price_units(std::uint8_t bank, std::uint8_t symbol_byte) const {
  validate_bank(bank);
  validate_price_symbol(symbol_byte);
  std::scoped_lock lock(mutex_);
  if (!prices_[bank].has_value()) {
    throw std::runtime_error("receiver bank cache is undefined");
  }
  return (*prices_[bank])[market_symbol_to_index(symbol_byte)];
}

std::optional<PriceBank> ReceiverControlState::bank_prices_units(std::uint8_t bank) const {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  return prices_[bank];
}

bool ReceiverControlState::has_bank(std::uint8_t bank) const {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  return prices_[bank].has_value();
}

std::uint64_t ReceiverControlState::bank_generation(std::uint8_t bank) const {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  return bank_generation_[bank];
}

SymbolPermissionMask ReceiverControlState::permissions() const {
  std::scoped_lock lock(mutex_);
  return permissions_;
}

std::uint64_t ReceiverControlState::permissions_generation() const {
  std::scoped_lock lock(mutex_);
  return permissions_generation_;
}

bool ReceiverControlState::symbol_allowed(std::uint8_t symbol_byte) const {
  if (!is_symbol_byte(symbol_byte)) {
    return false;
  }
  std::scoped_lock lock(mutex_);
  return symbol_allowed_by_mask(permissions_, symbol_byte);
}

bool ReceiverControlState::accept_received_symbol(std::uint8_t bank, std::uint8_t symbol_byte) {
  validate_bank(bank);
  if (is_client_symbol_byte(symbol_byte)) {
    return true;
  }
  if (!is_market_symbol_byte(symbol_byte)) {
    return false;
  }

  std::scoped_lock lock(mutex_);
  if (!prices_[bank].has_value()) {
    return false;
  }
  const auto target_generation = bank_generation_[bank];
  if (!active_market_bank_.has_value()) {
    if (target_generation == 0U) {
      return false;
    }
    active_market_bank_ = bank;
    return true;
  }

  const auto active_bank = *active_market_bank_;
  if (bank == active_bank) {
    return true;
  }

  if (target_generation <= market_bank_deactivation_generation_[bank]) {
    return false;
  }

  market_bank_deactivation_generation_[active_bank] = bank_generation_[active_bank];
  active_market_bank_ = bank;
  return true;
}

std::uint64_t ReceiverControlState::update_encryption_key(Aes128Key key) {
  std::scoped_lock lock(mutex_);
  aes_key_ = key;
  active_receiver_.pipeline.aes_key = key;
  return ++key_generation_;
}

ReceiverRestartConfig ReceiverControlState::request_restart(ReceiverRestartConfig config) {
  validate(config.pipeline.rf);
  validate(config.pipeline.convolutional);
  if (config.pipeline.sync_timestamp.enabled) {
    const auto skew = config.pipeline.sync_timestamp.max_clock_skew_seconds;
    if (skew <= 0.0 || !std::isfinite(skew)) {
      throw std::invalid_argument("sync timestamp skew must be positive when enabled");
    }
  }

  std::scoped_lock lock(mutex_);
  config.pipeline.aes_key = aes_key_;
  config.generation = ++restart_generation_;
  active_receiver_ = config;
  pending_restart_ = config;
  has_pending_restart_.store(true, std::memory_order_release);
  prices_[0].reset();
  prices_[1].reset();
  active_market_bank_.reset();
  market_bank_deactivation_generation_ = {};
  return config;
}

std::uint64_t ReceiverControlState::update_bank(std::uint8_t bank, std::span<const std::uint64_t> prices) {
  validate_bank(bank);
  if (prices.size() != control_symbol_count) {
    throw std::invalid_argument("bank update must contain exactly " +
                                std::to_string(control_symbol_count) +
                                " market prices");
  }

  std::scoped_lock lock(mutex_);
  PriceBank bank_prices{};
  std::copy(prices.begin(), prices.end(), bank_prices.begin());
  prices_[bank] = bank_prices;
  return ++bank_generation_[bank];
}

std::uint64_t ReceiverControlState::replace_bank(std::uint8_t bank,
                                                 std::span<const std::uint64_t> prices,
                                                 std::uint64_t generation) {
  validate_bank(bank);
  if (generation == 0U) {
    throw std::invalid_argument("replacement bank generation must be non-zero");
  }
  if (prices.size() != control_symbol_count) {
    throw std::invalid_argument("bank replacement must contain exactly " +
                                std::to_string(control_symbol_count) +
                                " market prices");
  }

  PriceBank bank_prices{};
  std::copy(prices.begin(), prices.end(), bank_prices.begin());
  std::scoped_lock lock(mutex_);
  prices_[bank] = bank_prices;
  bank_generation_[bank] = generation;
  return bank_generation_[bank];
}

void ReceiverControlState::clear_banks() {
  std::scoped_lock lock(mutex_);
  prices_[0].reset();
  prices_[1].reset();
  active_market_bank_.reset();
  market_bank_deactivation_generation_ = {};
}

std::uint64_t ReceiverControlState::update_permissions(std::span<const std::uint8_t> allowed_symbol_mask) {
  if (allowed_symbol_mask.size() != permissions_.size()) {
    throw std::invalid_argument("permissions mask must contain exactly " +
                                std::to_string(permissions_.size()) +
                                " bytes");
  }
  SymbolPermissionMask mask{};
  std::copy(allowed_symbol_mask.begin(), allowed_symbol_mask.end(), mask.begin());
  const auto unused_bits = mask.size() * 8U - total_symbol_count;
  if (unused_bits != 0U) {
    mask.back() = static_cast<std::uint8_t>(mask.back() & (0xFFU >> unused_bits));
  }

  std::scoped_lock lock(mutex_);
  permissions_ = mask;
  return ++permissions_generation_;
}

TransmitterControlState::TransmitterControlState() = default;

TransmitterControlState::TransmitterControlState(RealtimePipelineConfig initial_pipeline) {
  active_transmitter_.pipeline = std::move(initial_pipeline);
  aes_key_ = active_transmitter_.pipeline.aes_key;
  pending_restart_ = active_transmitter_;
  has_pending_restart_.store(true, std::memory_order_release);
  active_bank_packed_.store(pack_active_bank(active_bank_.bank, active_bank_.generation),
                            std::memory_order_release);
}

TransmitterControlSnapshot TransmitterControlState::snapshot() const {
  std::scoped_lock lock(mutex_);
  return {.aes_key = aes_key_,
          .key_generation = key_generation_,
          .active_transmitter = active_transmitter_,
          .restart_generation = restart_generation_,
          .prices = prices_,
          .bank_generation = bank_generation_,
          .active_bank = active_bank_};
}

Aes128Key TransmitterControlState::aes_key() const {
  std::scoped_lock lock(mutex_);
  return aes_key_;
}

std::uint64_t TransmitterControlState::key_generation() const {
  std::scoped_lock lock(mutex_);
  return key_generation_;
}

TransmitterRestartConfig TransmitterControlState::active_transmitter_config() const {
  std::scoped_lock lock(mutex_);
  return active_transmitter_;
}

std::optional<TransmitterRestartConfig> TransmitterControlState::take_pending_restart() {
  // Lock-free fast path on the DSP thread: in steady state the audio thread
  // calls this every chunk and the atomic load is the entire cost.
  if (!has_pending_restart_.load(std::memory_order_acquire)) {
    return std::nullopt;
  }
  std::scoped_lock lock(mutex_);
  auto restart = std::move(pending_restart_);
  pending_restart_.reset();
  has_pending_restart_.store(false, std::memory_order_release);
  return restart;
}

std::uint64_t TransmitterControlState::price_units(std::uint8_t bank, std::uint8_t symbol_byte) const {
  validate_bank(bank);
  validate_price_symbol(symbol_byte);
  std::scoped_lock lock(mutex_);
  return prices_[bank][market_symbol_to_index(symbol_byte)];
}

PriceBank TransmitterControlState::bank_prices_units(std::uint8_t bank) const {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  return prices_[bank];
}

std::uint64_t TransmitterControlState::bank_generation(std::uint8_t bank) const {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  return bank_generation_[bank];
}

ActiveBankState TransmitterControlState::active_bank() const {
  // Lock-free read on the DSP fast path. Writers publish via active_bank_packed_
  // after taking mutex_ to update active_bank_.
  return unpack_active_bank(active_bank_packed_.load(std::memory_order_acquire));
}

bool TransmitterControlState::receiver_client_alive(std::uint8_t client_id,
                                                    std::chrono::milliseconds timeout) const {
  if (client_id >= Clients) {
    throw std::invalid_argument("receiver client id outside Clients range");
  }
  std::scoped_lock lock(mutex_);
  if (!receiver_seen_[client_id]) {
    return false;
  }
  return std::chrono::steady_clock::now() - receiver_last_heartbeat_[client_id] <= timeout;
}

std::vector<std::uint8_t> TransmitterControlState::live_receiver_clients(std::chrono::milliseconds timeout) const {
  std::vector<std::uint8_t> clients;
  const auto now = std::chrono::steady_clock::now();
  std::scoped_lock lock(mutex_);
  for (std::size_t i = 0; i < Clients; ++i) {
    if (receiver_seen_[i] && now - receiver_last_heartbeat_[i] <= timeout) {
      clients.push_back(static_cast<std::uint8_t>(i));
    }
  }
  return clients;
}

std::uint64_t TransmitterControlState::update_encryption_key(Aes128Key key) {
  std::scoped_lock lock(mutex_);
  aes_key_ = key;
  active_transmitter_.pipeline.aes_key = key;
  return ++key_generation_;
}

TransmitterRestartConfig TransmitterControlState::request_restart(TransmitterRestartConfig config) {
  validate(config.pipeline.rf);
  validate(config.pipeline.convolutional);
  if (config.pipeline.sync_timestamp.enabled) {
    const auto skew = config.pipeline.sync_timestamp.max_clock_skew_seconds;
    if (skew <= 0.0 || !std::isfinite(skew)) {
      throw std::invalid_argument("sync timestamp skew must be positive when enabled");
    }
  }

  std::scoped_lock lock(mutex_);
  config.pipeline.aes_key = aes_key_;
  config.generation = ++restart_generation_;
  active_transmitter_ = config;
  pending_restart_ = config;
  has_pending_restart_.store(true, std::memory_order_release);
  return config;
}

std::uint64_t TransmitterControlState::update_bank(std::uint8_t bank, std::span<const std::uint64_t> prices) {
  validate_bank(bank);
  if (prices.size() != control_symbol_count) {
    throw std::invalid_argument("bank update must contain exactly " +
                                std::to_string(control_symbol_count) +
                                " market prices");
  }

  std::scoped_lock lock(mutex_);
  std::copy(prices.begin(), prices.end(), prices_[bank].begin());
  return ++bank_generation_[bank];
}

ActiveBankState TransmitterControlState::use_bank(std::uint8_t bank) {
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  active_bank_.bank = bank;
  ++active_bank_.generation;
  active_bank_packed_.store(pack_active_bank(active_bank_.bank, active_bank_.generation),
                            std::memory_order_release);
  return active_bank_;
}

void TransmitterControlState::register_receiver_client(std::uint8_t client_id) {
  if (client_id >= Clients) {
    throw std::invalid_argument("receiver client id outside Clients range");
  }
  std::scoped_lock lock(mutex_);
  receiver_seen_[client_id] = true;
  receiver_last_heartbeat_[client_id] = std::chrono::steady_clock::now();
}

void TransmitterControlState::note_receiver_heartbeat(std::uint8_t client_id) {
  register_receiver_client(client_id);
}

void TransmitterControlState::note_receiver_bank_delivered(std::uint8_t client_id,
                                                           std::uint8_t bank,
                                                           std::uint64_t generation) {
  if (client_id >= Clients) {
    throw std::invalid_argument("receiver client id outside Clients range");
  }
  validate_bank(bank);
  std::scoped_lock lock(mutex_);
  receiver_delivered_bank_generation_[client_id][bank] =
      std::max(receiver_delivered_bank_generation_[client_id][bank], generation);
}

bool TransmitterControlState::live_receiver_clients_have_bank(std::uint8_t bank,
                                                              std::uint64_t generation,
                                                              std::chrono::milliseconds timeout) const {
  validate_bank(bank);
  const auto now = std::chrono::steady_clock::now();
  std::scoped_lock lock(mutex_);
  for (std::size_t i = 0; i < Clients; ++i) {
    if (!receiver_seen_[i] || now - receiver_last_heartbeat_[i] > timeout) {
      continue;
    }
    if (receiver_delivered_bank_generation_[i][bank] < generation) {
      return false;
    }
  }
  return true;
}

ControlledRealtimeReceiver::ControlledRealtimeReceiver(SpscRingBuffer<DelimitedMessage>& output)
    : ControlledRealtimeReceiver(std::make_shared<ReceiverControlState>(), output) {}

ControlledRealtimeReceiver::ControlledRealtimeReceiver(std::shared_ptr<ReceiverControlState> control,
                                                       SpscRingBuffer<DelimitedMessage>& output)
    : control_(std::move(control)),
      output_(output) {
  if (!control_) {
    throw std::invalid_argument("ControlledRealtimeReceiver requires control state");
  }
  apply_pending_restart();
}

ControlledRealtimeReceiver::ControlledRealtimeReceiver(RealtimePipelineConfig initial_pipeline,
                                                       SpscRingBuffer<DelimitedMessage>& output)
    : ControlledRealtimeReceiver(std::make_shared<ReceiverControlState>(std::move(initial_pipeline)), output) {}

bool ControlledRealtimeReceiver::apply_pending_restart() {
  const auto restart = control_->take_pending_restart();
  if (!restart.has_value()) {
    return false;
  }
  receiver_ = std::make_unique<RealtimeReceiver>(restart->pipeline, output_);
  receiver_->set_decoded_message_observer(observer_);
  return true;
}

void ControlledRealtimeReceiver::set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept {
  observer_ = observer;
  if (receiver_) {
    receiver_->set_decoded_message_observer(observer_);
  }
}

RealtimeReceiveResult ControlledRealtimeReceiver::push_samples(std::span<const Complex> samples) {
  apply_pending_restart();
  if (!receiver_) {
    return {};
  }
  return receiver_->push_samples(samples);
}

RealtimeReceiveResult ControlledRealtimeReceiver::push_audio_block(std::span<const Complex> samples,
                                                                   std::uint64_t first_sample,
                                                                   bool valid) {
  apply_pending_restart();
  if (!receiver_) {
    return {};
  }
  return receiver_->push_audio_block(samples, first_sample, valid);
}

RealtimeReceiveResult ControlledRealtimeReceiver::push_timed_audio_block(std::span<const Complex> samples,
    std::uint64_t first_sample, std::uint64_t arrival_sample,
    std::size_t maximum_lateness_samples, bool valid) {
  apply_pending_restart();
  if (!receiver_) return {};
  return receiver_->push_timed_audio_block(samples, first_sample, arrival_sample,
                                          maximum_lateness_samples, valid);
}

ControlledRealtimeTransmitter::ControlledRealtimeTransmitter(QueueSource<DelimitedMessage>& input)
    : ControlledRealtimeTransmitter(std::make_shared<TransmitterControlState>(), input) {}

ControlledRealtimeTransmitter::ControlledRealtimeTransmitter(std::shared_ptr<TransmitterControlState> control,
                                                             QueueSource<DelimitedMessage>& input)
    : control_(std::move(control)),
      input_(input) {
  if (!control_) {
    throw std::invalid_argument("ControlledRealtimeTransmitter requires control state");
  }
  apply_pending_restart();
}

ControlledRealtimeTransmitter::ControlledRealtimeTransmitter(RealtimePipelineConfig initial_pipeline,
                                                             QueueSource<DelimitedMessage>& input)
    : ControlledRealtimeTransmitter(std::make_shared<TransmitterControlState>(std::move(initial_pipeline)), input) {}

bool ControlledRealtimeTransmitter::apply_pending_restart() {
  const auto restart = control_->take_pending_restart();
  if (!restart.has_value()) {
    return false;
  }
  transmitter_ = std::make_unique<RealtimeTransmitter>(restart->pipeline, input_);
  transmitter_->set_consumed_message_observer(observer_);
  observed_bank_generation_ = static_cast<std::uint64_t>(-1);
  apply_active_bank();
  return true;
}

bool ControlledRealtimeTransmitter::apply_active_bank() {
  if (!transmitter_) {
    return false;
  }
  const auto active = control_->active_bank();
  if (active.generation == observed_bank_generation_) {
    return false;
  }
  transmitter_->set_active_bank(active.bank);
  observed_bank_generation_ = active.generation;
  return true;
}

RealtimeTransmitResult ControlledRealtimeTransmitter::push_samples(std::span<Complex> out) {
  apply_pending_restart();
  if (!transmitter_) {
    return {};
  }
  apply_active_bank();
  return transmitter_->push_samples(out);
}

void ControlledRealtimeTransmitter::set_consumed_message_observer(DelimitedMessageObserver* observer) noexcept {
  observer_ = observer;
  if (transmitter_ != nullptr) {
    transmitter_->set_consumed_message_observer(observer_);
  }
}

class ReceiverControlServer::Impl {
public:
  Impl(std::shared_ptr<ReceiverControlState> control, ReceiverControlServerConfig config)
      : control_(std::move(control)),
        config_(std::move(config)) {
    if (!control_) {
      throw std::invalid_argument("ReceiverControlServer requires control state");
    }
  }

  ~Impl() {
    stop();
  }

  void start() {
    std::scoped_lock lock(mutex_);
    if (server_) {
      return;
    }

    service_ = std::make_unique<ReceiverControlService>(control_);
    grpc::ServerBuilder builder;
    int selected_port = 0;
    builder.AddListeningPort(config_.listen_address, grpc::InsecureServerCredentials(), &selected_port);
    builder.RegisterService(service_.get());
    server_ = builder.BuildAndStart();
    if (!server_) {
      service_.reset();
      throw std::runtime_error("failed to start receiver control gRPC server");
    }
    running_ = true;
    selected_port_ = selected_port;
    const auto host = host_from_listen_address(config_.listen_address);
    bound_address_ = selected_port == 0 ? config_.listen_address : host + ":" + std::to_string(selected_port);
    auto* wait_server = server_.get();
    thread_ = std::thread([wait_server] {
      wait_server->Wait();
    });
  }

  void stop() {
    std::unique_ptr<grpc::Server> server;
    std::thread thread;
    {
      std::scoped_lock lock(mutex_);
      if (!server_) {
        return;
      }
      running_ = false;
      server = std::move(server_);
      thread = std::move(thread_);
    }
    server->Shutdown();
    if (thread.joinable()) {
      thread.join();
    }
    {
      std::scoped_lock lock(mutex_);
      service_.reset();
      selected_port_ = 0;
      bound_address_.clear();
    }
  }

  [[nodiscard]] bool running() const noexcept {
    std::scoped_lock lock(mutex_);
    return running_;
  }

  [[nodiscard]] std::string bound_address() const {
    std::scoped_lock lock(mutex_);
    return bound_address_;
  }

  [[nodiscard]] std::shared_ptr<ReceiverControlState> control_state() const noexcept {
    return control_;
  }

private:
  std::shared_ptr<ReceiverControlState> control_;
  ReceiverControlServerConfig config_;
  mutable std::mutex mutex_;
  std::unique_ptr<ReceiverControlService> service_;
  std::unique_ptr<grpc::Server> server_;
  std::thread thread_;
  bool running_ = false;
  int selected_port_ = 0;
  std::string bound_address_;
};

ReceiverControlServer::ReceiverControlServer(std::shared_ptr<ReceiverControlState> control,
                                             ReceiverControlServerConfig config)
    : impl_(std::make_unique<Impl>(std::move(control), std::move(config))) {}

ReceiverControlServer::~ReceiverControlServer() = default;
ReceiverControlServer::ReceiverControlServer(ReceiverControlServer&&) noexcept = default;
ReceiverControlServer& ReceiverControlServer::operator=(ReceiverControlServer&&) noexcept = default;

void ReceiverControlServer::start() {
  impl_->start();
}

void ReceiverControlServer::stop() {
  impl_->stop();
}

bool ReceiverControlServer::running() const noexcept {
  return impl_->running();
}

std::string ReceiverControlServer::bound_address() const {
  return impl_->bound_address();
}

std::shared_ptr<ReceiverControlState> ReceiverControlServer::control_state() const noexcept {
  return impl_->control_state();
}

class TransmitterControlServer::Impl {
public:
  Impl(std::shared_ptr<TransmitterControlState> control, TransmitterControlServerConfig config)
      : control_(std::move(control)),
        config_(std::move(config)) {
    if (!control_) {
      throw std::invalid_argument("TransmitterControlServer requires control state");
    }
  }

  ~Impl() {
    stop();
  }

  void start() {
    std::scoped_lock lock(mutex_);
    if (server_) {
      return;
    }

    service_ = std::make_unique<TransmitterControlService>(
        control_,
        config_.transmit_queue,
        config_.log_queue,
        config_.log_queue_mutex,
        config_.bank_price_provider,
        config_.client_expected_latency_ns,
        config_.accounting,
        config_.canonical_messages);
    grpc::ServerBuilder builder;
    int selected_port = 0;
    builder.AddListeningPort(config_.listen_address, grpc::InsecureServerCredentials(), &selected_port);
    builder.RegisterService(service_.get());
    server_ = builder.BuildAndStart();
    if (!server_) {
      service_.reset();
      throw std::runtime_error("failed to start transmitter control gRPC server");
    }
    running_ = true;
    selected_port_ = selected_port;
    const auto host = host_from_listen_address(config_.listen_address);
    bound_address_ = selected_port == 0 ? config_.listen_address : host + ":" + std::to_string(selected_port);
    auto* wait_server = server_.get();
    thread_ = std::thread([wait_server] {
      wait_server->Wait();
    });
  }

  void stop() {
    std::unique_ptr<grpc::Server> server;
    std::thread thread;
    {
      std::scoped_lock lock(mutex_);
      if (!server_) {
        return;
      }
      running_ = false;
      server = std::move(server_);
      thread = std::move(thread_);
    }
    server->Shutdown();
    if (thread.joinable()) {
      thread.join();
    }
    {
      std::scoped_lock lock(mutex_);
      service_.reset();
      selected_port_ = 0;
      bound_address_.clear();
    }
  }

  [[nodiscard]] bool running() const noexcept {
    std::scoped_lock lock(mutex_);
    return running_;
  }

  [[nodiscard]] std::string bound_address() const {
    std::scoped_lock lock(mutex_);
    return bound_address_;
  }

  [[nodiscard]] std::shared_ptr<TransmitterControlState> control_state() const noexcept {
    return control_;
  }

private:
  std::shared_ptr<TransmitterControlState> control_;
  TransmitterControlServerConfig config_;
  mutable std::mutex mutex_;
  std::unique_ptr<TransmitterControlService> service_;
  std::unique_ptr<grpc::Server> server_;
  std::thread thread_;
  bool running_ = false;
  int selected_port_ = 0;
  std::string bound_address_;
};

TransmitterControlServer::TransmitterControlServer(std::shared_ptr<TransmitterControlState> control,
                                                   TransmitterControlServerConfig config)
    : impl_(std::make_unique<Impl>(std::move(control), std::move(config))) {}

TransmitterControlServer::~TransmitterControlServer() = default;
TransmitterControlServer::TransmitterControlServer(TransmitterControlServer&&) noexcept = default;
TransmitterControlServer& TransmitterControlServer::operator=(TransmitterControlServer&&) noexcept = default;

void TransmitterControlServer::start() {
  impl_->start();
}

void TransmitterControlServer::stop() {
  impl_->stop();
}

bool TransmitterControlServer::running() const noexcept {
  return impl_->running();
}

std::string TransmitterControlServer::bound_address() const {
  return impl_->bound_address();
}

std::shared_ptr<TransmitterControlState> TransmitterControlServer::control_state() const noexcept {
  return impl_->control_state();
}

} // namespace goblin_cannon
