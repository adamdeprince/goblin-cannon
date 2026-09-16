#pragma once

#include "goblin_cannon/convolutional.hpp"
#include "goblin_cannon/crypto.hpp"
#include "goblin_cannon/rf_stream.hpp"
#include "goblin_cannon/ring_buffer.hpp"

#include <cstddef>
#include <cstdint>
#include <optional>
#include <span>
#include <array>
#include <string>
#include <vector>
#include <deque>
#include <memory>
#include <mutex>

namespace goblin_cannon {

struct DelimitedMessage {
  std::vector<std::uint8_t> bytes;
  // Present only in the sequenced message format. The payload remains the
  // original application bytes; sequence metadata is covered by the wire CRC.
  std::optional<std::uint32_t> sequence = std::nullopt;
};

enum class MessageGapReason { fec_uncertain, checksum, oversized, malformed, rf_lock_lost, audio_discontinuity };
struct MessageGap {
  MessageGapReason reason;
  std::uint64_t missing_samples = 0;
};

inline constexpr std::size_t maximum_message_bytes = 65535;

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
  transmitter_framer,
  receiver_client_message,
  receiver_signal,
  iq_transport,
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
  virtual void on_message_gap(const MessageGap&) {}
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

// The winner stays replaceable until the framer takes its first byte. Producers
// never mutate an item published into an SPSC ring. Non-auction input is an
// explicit ordered FIFO; auction input has one bounded standing winner.
class TransmitMessageQueue final : public QueueSource<DelimitedMessage> {
public:
  explicit TransmitMessageQueue(std::size_t capacity, std::shared_ptr<std::mutex> decision_log_mutex = {});
  bool try_push(DelimitedMessage message);
  bool try_pop(DelimitedMessage& message) override;
  [[nodiscard]] std::size_t capacity() const noexcept { return capacity_; }
  [[nodiscard]] std::size_t size_approx() const;
  [[nodiscard]] bool empty() const { return size_approx() == 0; }
  [[nodiscard]] bool full() const;
  [[nodiscard]] std::size_t pending_bids() const;
  void clear_pending_bid();
  void set_sequence_numbers(bool enabled) { std::scoped_lock lock(mutex_); sequence_numbers_ = enabled; }
  // Other writers of decision logs must use the same external mutex. Callers
  // of submit/pump already hold it; the audio consumer acquires it internally.
  void set_decision_log_mutex(std::shared_ptr<std::mutex> mutex) { decision_log_mutex_ = std::move(mutex); }
private:
  friend class BidMessageTransmitIntake;
  BidMessageIntakeResult offer(BidMessage, SpscRingBuffer<BidMessageLogRecord>&,
                              BidMessageLogObserver*, BidBudgetAccountant*);
  struct Candidate {
    BidMessage message;
    SpscRingBuffer<BidMessageLogRecord>* logs;
    BidMessageLogObserver* observer;
    BidBudgetAccountant* accountant;
  };
  const std::size_t capacity_;
  mutable std::mutex mutex_;
  std::shared_ptr<std::mutex> decision_log_mutex_;
  std::deque<DelimitedMessage> fifo_;
  std::optional<Candidate> best_;
  bool sequence_numbers_ = true;
};

class MessageStreamFramer {
public:
  [[nodiscard]] MessageFrameEncodeResult next_payload_frame(
      QueueSource<DelimitedMessage>& input,
      std::span<std::uint8_t> payload_out);

  void set_active_bank(std::uint8_t bank);
  void clear_active_bank_override() noexcept;
  [[nodiscard]] std::optional<std::uint8_t> active_bank_override() const noexcept { return active_bank_override_; }
  void set_consumed_message_observer(DelimitedMessageObserver* observer) noexcept { observer_ = observer; }
  void set_sequence_numbers(bool enabled, std::uint32_t first = 0) noexcept {
    sequence_numbers_ = enabled; next_sequence_ = first;
  }
  void reset();

private:
  std::vector<std::uint8_t> current_;
  std::size_t current_offset_ = 0;
  std::optional<std::uint8_t> active_bank_override_ = std::nullopt;
  DelimitedMessageObserver* observer_ = nullptr;
  bool sequence_numbers_ = false;
  std::uint32_t next_sequence_ = 0;
};

class BidMessageTransmitIntake {
public:
  [[nodiscard]] BidMessageIntakeResult submit(BidMessage message,
                                              TransmitMessageQueue& transmit_queue,
                                              SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                              BidMessageLogObserver* observer = nullptr,
                                              BidBudgetAccountant* accountant = nullptr);
  [[nodiscard]] BidMessageIntakeResult pump(TransmitMessageQueue& transmit_queue,
                                            SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                            BidMessageLogObserver* observer = nullptr,
                                            BidBudgetAccountant* accountant = nullptr);
  [[nodiscard]] std::size_t pending_bids() const {
    const auto queue = queue_.load(std::memory_order_acquire);
    return queue ? queue->pending_bids() : 0U;
  }
  void reset();

private:
  std::atomic<TransmitMessageQueue*> queue_ = nullptr;
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
  void set_sequence_numbers(bool enabled) noexcept { sequence_numbers_ = enabled; }
  void report_gap(MessageGap gap);
  [[nodiscard]] std::uint64_t gap_count() const noexcept { return gap_count_; }
  [[nodiscard]] std::uint64_t suppressed_messages() const noexcept { return suppressed_messages_; }
  // Clears partial data while retaining the sequence high-water marks. A new
  // negotiated session constructs a new deframer to reset sequence history.
  void reset();

private:
  [[nodiscard]] bool flush_pending(SpscRingBuffer<DelimitedMessage>& output);
  [[nodiscard]] bool push_completed(std::vector<std::uint8_t> message,
                                    SpscRingBuffer<DelimitedMessage>& output,
                                    bool& emitted);

  std::vector<std::uint8_t> current_;
  std::optional<DelimitedMessage> pending_;
  DelimitedMessageObserver* observer_ = nullptr;
  bool require_delimiter_ = true;
  bool sequence_numbers_ = false;
  std::array<std::optional<std::uint32_t>, 2U * 254U> latest_sequence_{};
  std::uint64_t gap_count_ = 0;
  std::uint64_t suppressed_messages_ = 0;
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
  // Must match at both ends, negotiated over the fiber control path.
  bool sequence_numbers = true;
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
  std::size_t gap_events = 0;
};

class RealtimeTransmitter {
public:
  RealtimeTransmitter(RealtimePipelineConfig config, QueueSource<DelimitedMessage>& input);

  [[nodiscard]] RealtimeTransmitResult push_samples(std::span<Complex> out);
  [[nodiscard]] const RealtimePipelineConfig& config() const noexcept { return config_; }
  void set_active_bank(std::uint8_t bank);
  void clear_active_bank_override() noexcept;
  [[nodiscard]] std::optional<std::uint8_t> active_bank_override() const noexcept;
  void set_consumed_message_observer(DelimitedMessageObserver* observer) noexcept;

private:
  void ensure_symbol_block(RealtimeTransmitResult& result);

  RealtimePipelineConfig config_;
  QueueSource<DelimitedMessage>& input_;
  MessageStreamFramer framer_;
  PuncturedConvolutionalEncoder convolutional_;
  Aes128CtrBitXor bit_xor_;
  RfStreamEncoder rf_;
  Constellation constellation_;
  std::vector<std::uint8_t> pending_bits_;
  std::size_t pending_bits_head_ = 0;
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
  // Audio drivers supply their monotonic sample position and report underruns.
  // A skipped/repeated block or invalid block emits an explicit gap and resets
  // partial decoding before any samples can be mistaken for message data.
  [[nodiscard]] RealtimeReceiveResult push_audio_block(std::span<const Complex> samples,
                                                       std::uint64_t first_sample, bool valid = true);
  // Arrival and sample positions share the device's sample clock. A block
  // beyond the playout buffer's slack is a gap even with contiguous positions.
  [[nodiscard]] RealtimeReceiveResult push_timed_audio_block(std::span<const Complex> samples,
      std::uint64_t first_sample, std::uint64_t arrival_sample,
      std::size_t maximum_lateness_samples, bool valid = true);
  [[nodiscard]] const RealtimePipelineConfig& config() const noexcept { return config_; }
  void set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept;

private:
  void reset_coded_stream();
  [[nodiscard]] bool process_decoded_tokens(std::span<const Token> tokens, RealtimeReceiveResult& result);
  [[nodiscard]] bool accept_sync_timestamp_byte(const Token& token, RealtimeReceiveResult& result);
  void reject_stream(RealtimeReceiveResult& result);

  RealtimePipelineConfig config_;
  SpscRingBuffer<DelimitedMessage>& output_;
  MessageStreamDeframer deframer_;
  StreamingSoftViterbiDecoder viterbi_;
  Aes128CtrBitXor bit_xor_;
  RfStreamReceiver rf_;
  Constellation constellation_;
  std::array<std::uint8_t, 8> sync_timestamp_bytes_{};
  std::size_t sync_timestamp_offset_ = 0;
  bool sync_timestamp_validated_ = false;
  bool stream_aborted_ = false;
  std::optional<std::uint64_t> next_audio_sample_;
  // Persistent per-chunk buffers reused across push_samples calls.
  std::vector<SoftBit> coded_bits_buffer_;
  std::vector<Token> message_tokens_buffer_;
};

} // namespace goblin_cannon
