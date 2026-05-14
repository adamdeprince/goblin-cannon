#pragma once

#include "wbhf_modem/convolutional.hpp"
#include "wbhf_modem/crypto.hpp"
#include "wbhf_modem/rf_stream.hpp"
#include "wbhf_modem/ring_buffer.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <array>
#include <string>
#include <vector>

namespace wbhf_modem {

struct DelimitedMessage {
  std::vector<std::uint8_t> bytes;
};

struct BidMessage {
  std::vector<std::uint8_t> payload;
  std::uint64_t bid_price = 0;
  std::uint8_t client_id = 0;
  bool has_client_id = false;
  std::string reply_ip;
  std::uint16_t reply_port = 0;
};

enum class BidMessageLogStatus {
  sent,
  rejected,
  invalid_message_format,
  unauthorized_source,
  budget_exhausted,
  expired_refunded,
  delivery_matched,
  delivery_unmatched,
};

enum class LogEventType {
  udp_ingress,
  udp_decision,
  transmitter_enqueue,
  receiver_client_message,
  receiver_signal,
  budget_refund,
};

struct BidMessageLogRecord {
  LogEventType event_type = LogEventType::udp_decision;
  std::uint64_t local_timestamp_ns = 0;
  std::uint64_t receiver_timestamp_ns = 0;
  std::vector<std::uint8_t> payload;
  std::vector<std::uint8_t> raw_payload;
  BidMessageLogStatus status = BidMessageLogStatus::sent;
  std::uint64_t bid_price = 0;
  std::uint64_t winning_bid_price = 0;
  std::uint8_t client_id = 0;
  bool has_client_id = false;
  std::string reply_ip;
  std::uint16_t reply_port = 0;
  std::uint64_t expected_latency_ns = 0;
  std::uint64_t observed_latency_ns = 0;
  std::uint64_t remaining_budget_cents = 0;
  std::uint64_t matched_timestamp_ns = 0;
  std::string event_name;
  std::string detail;
  double metric = 0.0;
  std::uint64_t count = 0;
};

struct BidMessageIntakeResult {
  bool transmitted = false;
  bool queued_for_arbitration = false;
  std::size_t pending_bids = 0;
  std::size_t logged_records = 0;
  bool transmit_backpressure = false;
  bool log_backpressure = false;
  bool budget_rejected = false;
};

class DelimitedMessageObserver {
public:
  virtual ~DelimitedMessageObserver() = default;
  virtual void on_delimited_message(const DelimitedMessage& message) = 0;
};

class BidMessageLogObserver {
public:
  virtual ~BidMessageLogObserver() = default;
  virtual void on_bid_message_log(const BidMessageLogRecord& record) = 0;
};

struct BidBudgetReserveResult {
  bool accepted = true;
  std::uint64_t remaining_budget_cents = 0;
};

class BidBudgetAccountant {
public:
  virtual ~BidBudgetAccountant() = default;
  [[nodiscard]] virtual bool can_afford_bid(const BidMessage& message) const = 0;
  [[nodiscard]] virtual BidBudgetReserveResult reserve_sent_bid(const BidMessage& message,
                                                                std::uint64_t sent_timestamp_ns) = 0;
};

struct MessageFrameEncodeResult {
  std::size_t payload_bytes = 0;
  std::size_t padding_bytes = 0;
  std::size_t consumed_messages = 0;
  bool input_empty = false;
  bool message_continues = false;
};

struct MessageFrameDecodeResult {
  std::size_t consumed_bytes = 0;
  std::size_t produced_messages = 0;
  bool output_backpressure = false;
  bool waiting_for_next_delimiter = false;
};

class MessageStreamFramer {
public:
  [[nodiscard]] MessageFrameEncodeResult next_payload_frame(
      SpscRingBuffer<DelimitedMessage>& input,
      std::span<std::uint8_t> payload_out);

  void set_active_bank(std::uint8_t bank);
  void clear_active_bank_override() noexcept;
  [[nodiscard]] std::optional<std::uint8_t> active_bank_override() const noexcept { return active_bank_override_; }
  void reset();

private:
  std::vector<std::uint8_t> current_;
  std::size_t current_offset_ = 0;
  std::optional<std::uint8_t> active_bank_override_ = std::nullopt;
};

class BidMessageTransmitIntake {
public:
  [[nodiscard]] BidMessageIntakeResult submit(BidMessage message,
                                              SpscRingBuffer<DelimitedMessage>& transmit_queue,
                                              SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                              BidMessageLogObserver* observer = nullptr,
                                              BidBudgetAccountant* accountant = nullptr);
  [[nodiscard]] BidMessageIntakeResult pump(SpscRingBuffer<DelimitedMessage>& transmit_queue,
                                            SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                            BidMessageLogObserver* observer = nullptr,
                                            BidBudgetAccountant* accountant = nullptr);
  [[nodiscard]] std::size_t pending_bids() const noexcept { return pending_best_.has_value() ? 1U : 0U; }
  void reset();

private:
  [[nodiscard]] bool log_has_capacity(const SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                      std::size_t records) const noexcept;
  void emit_log(BidMessageLogRecord record,
                SpscRingBuffer<BidMessageLogRecord>& log_queue,
                BidMessageLogObserver* observer);

  std::optional<BidMessage> pending_best_ = std::nullopt;
};

class MessageStreamDeframer {
public:
  [[nodiscard]] MessageFrameDecodeResult push_payload_frame(
      std::span<const std::uint8_t> payload,
      SpscRingBuffer<DelimitedMessage>& output);
  [[nodiscard]] MessageFrameDecodeResult push_payload_tokens(
      std::span<const Token> payload,
      SpscRingBuffer<DelimitedMessage>& output);

  void set_observer(DelimitedMessageObserver* observer) noexcept { observer_ = observer; }
  void reset();

private:
  [[nodiscard]] bool flush_pending(SpscRingBuffer<DelimitedMessage>& output);
  [[nodiscard]] bool push_completed(std::vector<std::uint8_t> message,
                                    SpscRingBuffer<DelimitedMessage>& output);

  std::vector<std::uint8_t> current_;
  std::optional<DelimitedMessage> pending_;
  DelimitedMessageObserver* observer_ = nullptr;
  bool require_delimiter_ = true;
};

struct SyncTimestampConfig {
  bool enabled = true;
  double max_clock_skew_seconds = 0.1;
};

struct RealtimePipelineConfig {
  RfStreamConfig rf = {};
  PuncturedConvolutionalCodeConfig convolutional = PuncturedConvolutionalCodeConfig::rate_1_2();
  Aes128Key aes_key = {};
  Aes128CtrCounter ctr_counter = {};
  SyncTimestampConfig sync_timestamp = {};
  std::uint64_t frame_counter_start = 0;
};

struct RealtimeTransmitResult {
  std::size_t produced_samples = 0;
  std::size_t consumed_messages = 0;
  std::size_t emitted_bytes = 0;
  std::size_t emitted_coded_bits = 0;
};

struct RealtimeReceiveResult {
  std::size_t consumed_samples = 0;
  std::size_t produced_messages = 0;
  std::size_t decoded_bytes = 0;
  bool acquisition_found = false;
  bool header_valid = false;
  bool lock_lost = false;
  bool output_backpressure = false;
  bool timestamp_valid = false;
  bool replay_rejected = false;
  double sync_timestamp_seconds = 0.0;
};

class RealtimeTransmitter {
public:
  RealtimeTransmitter(RealtimePipelineConfig config, SpscRingBuffer<DelimitedMessage>& input);

  [[nodiscard]] RealtimeTransmitResult push_samples(std::span<Complex> out);
  [[nodiscard]] const RealtimePipelineConfig& config() const noexcept { return config_; }
  void set_active_bank(std::uint8_t bank);
  void clear_active_bank_override() noexcept;
  [[nodiscard]] std::optional<std::uint8_t> active_bank_override() const noexcept;

private:
  void ensure_symbol_block(RealtimeTransmitResult& result);

  RealtimePipelineConfig config_;
  SpscRingBuffer<DelimitedMessage>& input_;
  MessageStreamFramer framer_;
  PuncturedConvolutionalEncoder convolutional_;
  Aes128CtrBitXor bit_xor_;
  RfStreamEncoder rf_;
  Constellation constellation_;
  std::vector<std::uint8_t> pending_bits_;
  std::vector<std::uint32_t> symbols_;
  std::size_t symbol_offset_ = 0;
  std::array<std::uint8_t, 8> sync_timestamp_bytes_{};
  std::size_t sync_timestamp_offset_ = 8;
  bool sync_timestamp_initialized_ = false;
};

class RealtimeReceiver {
public:
  RealtimeReceiver(RealtimePipelineConfig config, SpscRingBuffer<DelimitedMessage>& output);

  [[nodiscard]] RealtimeReceiveResult push_samples(std::span<const Complex> samples);
  [[nodiscard]] const RealtimePipelineConfig& config() const noexcept { return config_; }
  void set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept;

private:
  void try_decode_bytes(RealtimeReceiveResult& result);
  void reset_coded_stream();
  [[nodiscard]] bool process_decoded_tokens(std::span<const Token> tokens, RealtimeReceiveResult& result);
  [[nodiscard]] bool accept_sync_timestamp_byte(const Token& token, RealtimeReceiveResult& result);
  void reject_stream(RealtimeReceiveResult& result);

  RealtimePipelineConfig config_;
  SpscRingBuffer<DelimitedMessage>& output_;
  MessageStreamDeframer deframer_;
  SoftViterbiDecoder viterbi_;
  Aes128CtrBitXor bit_xor_;
  RfStreamReceiver rf_;
  Constellation constellation_;
  std::vector<SoftBit> coded_bits_;
  std::size_t emitted_bytes_ = 0;
  std::array<std::uint8_t, 8> sync_timestamp_bytes_{};
  std::size_t sync_timestamp_offset_ = 0;
  bool sync_timestamp_validated_ = false;
  bool stream_aborted_ = false;
};

} // namespace wbhf_modem
