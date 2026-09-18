#include "goblin_cannon/message_stream.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <chrono>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>
#include <cstdlib>

namespace goblin_cannon {

namespace {

bool is_delimiter(std::uint8_t byte) noexcept {
  return byte == 0U || byte == 1U;
}

constexpr std::size_t message_crc_bytes = 4U;
constexpr std::uint32_t message_crc31_mask = 0x7FFFFFFFU;
constexpr std::uint32_t message_crc_radix = 254U;

double current_epoch_seconds() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return std::chrono::duration<double>(now).count();
}

std::uint64_t current_epoch_nanos() {
  const auto now = std::chrono::system_clock::now().time_since_epoch();
  return static_cast<std::uint64_t>(std::chrono::duration_cast<std::chrono::nanoseconds>(now).count());
}

std::array<std::uint8_t, 8> encode_native_double(double value) {
  static_assert(sizeof(double) == 8U);
  static_assert(std::numeric_limits<double>::is_iec559);
  return std::bit_cast<std::array<std::uint8_t, 8>>(value);
}

double decode_native_double(std::span<const std::uint8_t, 8> bytes) {
  static_assert(sizeof(double) == 8U);
  static_assert(std::numeric_limits<double>::is_iec559);
  std::array<std::uint8_t, 8> storage{};
  std::copy(bytes.begin(), bytes.end(), storage.begin());
  return std::bit_cast<double>(storage);
}

void validate_message(const DelimitedMessage& message) {
  if (message.bytes.size() > maximum_message_bytes) {
    throw std::invalid_argument("message exceeds maximum_message_bytes");
  }
  if (message.bytes.empty()) {
    throw std::invalid_argument("message must include a 0/1 start delimiter");
  }
  if (!is_delimiter(message.bytes.front())) {
    throw std::invalid_argument("message must start with delimiter byte 0 or 1");
  }
  for (std::size_t i = 1; i < message.bytes.size(); ++i) {
    if (is_delimiter(message.bytes[i])) {
      throw std::invalid_argument("message body bytes must be in [2, 255]");
    }
  }
}

void validate_bid_message(const BidMessage& message) {
  validate_message(DelimitedMessage{.bytes = message.payload});
}

std::uint32_t message_crc32_update(std::uint32_t crc, std::span<const std::uint8_t> bytes) {
  crc = ~crc;
  for (const auto byte : bytes) {
    crc ^= byte;
    for (int bit = 0; bit < 8; ++bit) {
      const std::uint32_t mask = 0U - (crc & 1U);
      crc = (crc >> 1U) ^ (0xEDB88320U & mask);
    }
  }
  return ~crc;
}

std::uint32_t message_crc31(std::span<const std::uint8_t> bytes) {
  return message_crc32_update(0, bytes) & message_crc31_mask;
}

std::array<std::uint8_t, message_crc_bytes> encode_crc31_base254(std::uint32_t value) {
  value &= message_crc31_mask;
  std::array<std::uint8_t, message_crc_bytes> out{};
  for (auto& byte : out) {
    byte = static_cast<std::uint8_t>(2U + (value % message_crc_radix));
    value /= message_crc_radix;
  }
  return out;
}

std::optional<std::uint32_t> decode_crc31_base254(std::span<const std::uint8_t, message_crc_bytes> bytes) {
  std::uint64_t value = 0;
  std::uint64_t multiplier = 1;
  for (const auto byte : bytes) {
    if (byte < 2U) {
      return std::nullopt;
    }
    value += static_cast<std::uint64_t>(byte - 2U) * multiplier;
    multiplier *= message_crc_radix;
  }
  if (value > message_crc31_mask) {
    return std::nullopt;
  }
  return static_cast<std::uint32_t>(value);
}

bool message_carries_crc(std::span<const std::uint8_t> message) noexcept {
  return message.size() > 1U;
}

void append_message_crc(std::vector<std::uint8_t>& message) {
  if (!message_carries_crc(message)) {
    return;
  }
  const auto encoded = encode_crc31_base254(message_crc31(message));
  message.insert(message.end(), encoded.begin(), encoded.end());
}

std::optional<std::vector<std::uint8_t>> verify_and_strip_message_crc(std::vector<std::uint8_t> message) {
  if (!message_carries_crc(message)) {
    return std::nullopt;
  }
  if (message.size() <= message_crc_bytes) {
    return std::nullopt;
  }
  const auto body_size = message.size() - message_crc_bytes;
  const auto observed = decode_crc31_base254(
      std::span<const std::uint8_t, message_crc_bytes>(message.data() + body_size, message_crc_bytes));
  if (!observed.has_value()) {
    return std::nullopt;
  }
  const auto expected = message_crc31(std::span<const std::uint8_t>(message.data(), body_size));
  if (*observed != expected) {
    return std::nullopt;
  }
  message.resize(body_size);
  return message;
}

bool bid_score_better(const BidMessage& candidate, const BidMessage& incumbent, bool compact) noexcept {
  const auto candidate_score = static_cast<long double>(candidate.bid_price) /
                               static_cast<long double>(authenticated_message_wire_bytes(candidate.payload.size(), compact));
  const auto incumbent_score = static_cast<long double>(incumbent.bid_price) /
                               static_cast<long double>(authenticated_message_wire_bytes(incumbent.payload.size(), compact));
  if (candidate_score != incumbent_score) {
    return candidate_score > incumbent_score;
  }
  return candidate.bid_price > incumbent.bid_price;
}

BidMessageLogRecord make_bid_log(const BidMessage& message,
                                 BidMessageLogStatus status,
                                 std::uint64_t winning_bid_price) {
  BidMessageLogRecord record;
  record.event_type = LogEventType::udp_decision;
  record.local_timestamp_ns = current_epoch_nanos();
  record.payload = message.payload;
  record.status = status;
  record.bid_price = message.bid_price;
  record.winning_bid_price = winning_bid_price;
  record.client_id = message.client_id;
  record.has_client_id = message.has_client_id;
  record.reply_ip = message.reply_ip;
  record.reply_port = message.reply_port;
  return record;
}

BidMessageLogRecord make_budget_exhausted_log(const BidMessage& message) {
  auto record = make_bid_log(message, BidMessageLogStatus::budget_exhausted, 0U);
  record.detail = "insufficient_budget";
  return record;
}

bool message_needs_accounting(const BidMessage& message) noexcept {
  return message.has_client_id;
}

bool can_afford_bid(const BidMessage& message, const BidBudgetAccountant* accountant) {
  return !message_needs_accounting(message) || accountant == nullptr || accountant->can_afford_bid(message);
}

std::optional<BidMessageLogRecord> reserve_sent_bid(BidMessageLogRecord sent_log,
                                                    const BidMessage& message,
                                                    BidBudgetAccountant* accountant) {
  if (!message_needs_accounting(message) || accountant == nullptr) {
    return sent_log;
  }
  const auto reserve = accountant->reserve_sent_bid(message, sent_log.local_timestamp_ns);
  if (!reserve.accepted) {
    auto rejected = make_budget_exhausted_log(message);
    rejected.remaining_budget_cents = reserve.remaining_budget_cents;
    return rejected;
  }
  sent_log.remaining_budget_cents = reserve.remaining_budget_cents;
  return sent_log;
}

void validate_realtime_config(const RealtimePipelineConfig& config) {
  validate(config.rf);
  validate(config.convolutional);
  validate(config.coding);
  if (config.sync_timestamp.enabled &&
      (!std::isfinite(config.sync_timestamp.max_clock_skew_seconds) ||
       config.sync_timestamp.max_clock_skew_seconds <= 0.0)) {
    throw std::invalid_argument("sync timestamp max_clock_skew_seconds must be positive");
  }
}

} // namespace

namespace {
constexpr std::size_t authenticated_header_bytes = 25;
void append_integer(std::vector<std::uint8_t>& bytes, std::uint64_t value, unsigned width) {
  for (unsigned i = width; i > 0; --i) bytes.push_back(static_cast<std::uint8_t>(value >> ((i - 1) * 8)));
}
std::uint64_t read_integer(std::span<const std::uint8_t> bytes) {
  std::uint64_t value = 0;
  for (auto b : bytes) value = (value << 8) | b;
  return value;
}
// Ordinary COBS framing reserves only zero. All header and ciphertext bytes,
// including 0/1, are representable without changing the authenticated record.
std::vector<std::uint8_t> cobs_encode(std::span<const std::uint8_t> bytes) {
  std::vector<std::uint8_t> out{0, 0};
  out.reserve(bytes.size() + bytes.size() / 254 + 3);
  std::size_t code_at = 1;
  std::uint8_t code = 1;
  for (auto byte : bytes) {
    if (byte == 0) {
      out[code_at] = code; code_at = out.size(); out.push_back(0); code = 1;
    } else {
      out.push_back(byte);
      if (++code == 255) { out[code_at] = code; code_at = out.size(); out.push_back(0); code = 1; }
    }
  }
  out[code_at] = code;
  return out;
}
bool cobs_decode(std::span<const std::uint8_t> in, std::vector<std::uint8_t>& out) {
  out.clear();
  for (std::size_t at = 0; at < in.size();) {
    const auto code = in[at++];
    if (!code || code - 1U > in.size() - at) return false;
    for (unsigned i = 1; i < code; ++i) {
      if (in[at] == 0) return false;
      out.push_back(in[at++]);
    }
    if (code != 255 && at < in.size()) out.push_back(0);
  }
  return true;
}
}

std::size_t authenticated_message_wire_bytes(std::size_t application_bytes, bool compact) noexcept {
  const auto record = application_bytes + (compact ? 13 : authenticated_header_bytes) + GcmTag{}.size() - 1;
  return record + record / 254 + 2;
}

class AuthenticatedMessageEncoder {
public:
  AuthenticatedMessageEncoder(const Aes256Key& key, std::uint32_t id, std::shared_ptr<TransmitterEpoch> e, bool small)
      : cipher(key), key_id(id), epoch(std::move(e)), compact(small) {
    if (!key_id || !epoch) throw std::invalid_argument("key ID and durable epoch are required");
    epoch->claim();
  }
  std::vector<std::uint8_t> seal(const DelimitedMessage& message, bool sequenced) {
    if (sequence == std::numeric_limits<std::uint32_t>::max()) throw std::overflow_error("AEAD frame sequence exhausted; restart with a fresh epoch");
    ++sequence; // Never zero; a failed encryption burns this nonce too.
    record.clear();
    if (!compact) record.push_back(1);
    record.push_back(message.bytes[0]);
    if (!compact) record.push_back(sequenced ? 1 : 0);
    append_integer(record, key_id, 4);
    if (!compact) append_integer(record, epoch->value(), 8);
    append_integer(record, sequence, 4); append_integer(record, message.sequence.value_or(0), 4);
    if (!compact) append_integer(record, message.bytes.size() - 1, 2);
    ad = record;
    if (compact) {
      // Fixed domain/version, negotiated epoch, sequence interpretation and
      // implicit length are bound without spending radio bytes on them.
      ad.insert(ad.end(), {'G','C','A',2});
      append_integer(ad, epoch->value(), 8); ad.push_back(sequenced ? 1 : 0);
      append_integer(ad, message.bytes.size() - 1, 2);
    }
    ad.insert(ad.end(), context.begin(), context.end());
    GcmTag tag{};
    cipher.seal(message_nonce(epoch->value(), sequence), ad, std::span(message.bytes).subspan(1), encrypted, tag);
    record.insert(record.end(), encrypted.begin(), encrypted.end());
    record.insert(record.end(), tag.begin(), tag.end());
    return cobs_encode(record);
  }
  Aes256Gcm cipher;
  std::uint32_t key_id, sequence = 0;
  std::shared_ptr<TransmitterEpoch> epoch;
  bool compact;
  std::vector<std::uint8_t> context, ad, record, encrypted;
};

class AuthenticatedMessageDecoder {
public:
  AuthenticatedMessageDecoder(const Aes256Key& key, std::uint32_t id, std::uint64_t e, bool small)
      : cipher(key), key_id(id), epoch(e), compact(small) {
    if (!key_id || !epoch) throw std::invalid_argument("receiver requires a key ID and negotiated nonzero transmitter epoch");
  }
  std::optional<DelimitedMessage> open(std::span<const std::uint8_t> wire, bool sequenced) {
    const auto fail = [&]() -> std::optional<DelimitedMessage> { ++failures; return std::nullopt; };
    if (wire.empty() || wire[0] != 0 || !cobs_decode(wire.subspan(1), record) ||
        record.size() < (compact ? 13 : authenticated_header_bytes) + GcmTag{}.size()) return fail();
    const auto header_size = compact ? 13 : authenticated_header_bytes;
    const auto header = std::span(record).first(header_size);
    const auto observed_id = read_integer(header.subspan(compact ? 1 : 3, 4));
    const auto observed_epoch = compact ? epoch : read_integer(header.subspan(7, 8));
    const auto sequence = static_cast<std::uint32_t>(read_integer(header.subspan(compact ? 5 : 15, 4)));
    if (!observed_epoch || !sequence || observed_id != key_id) return fail();
    const auto length = compact ? record.size() - header_size - GcmTag{}.size() : read_integer(header.subspan(23, 2));
    if (length >= maximum_message_bytes || record.size() != header_size + length + GcmTag{}.size()) return fail();
    ad.assign(header.begin(), header.end());
    if (compact) {
      ad.insert(ad.end(), {'G','C','A',2});
      append_integer(ad, epoch, 8); ad.push_back(sequenced ? 1 : 0);
      append_integer(ad, length, 2);
    }
    ad.insert(ad.end(), context.begin(), context.end());
    GcmTag tag{}; std::copy_n(record.end() - tag.size(), tag.size(), tag.begin());
    if (!cipher.open(message_nonce(observed_epoch, sequence), ad,
                     std::span(record).subspan(header_size, length), tag, clear)) return fail();
    // Only authenticated metadata may update replay state. A fresh receiver
    // negotiates a fresh TX epoch over fiber, so old sessions are rejected too.
    if (observed_epoch != epoch || sequence <= latest) { ++replays; return std::nullopt; }
    const auto bank = header[compact ? 0 : 1];
    if ((!compact && (header[0] != 1 || header[2] != (sequenced ? 1 : 0))) || bank > 1 ||
        std::any_of(clear.begin(), clear.end(), [](auto b) { return b < 2; })) return fail();
    latest = sequence;
    DelimitedMessage message{.bytes = {bank}};
    message.bytes.insert(message.bytes.end(), clear.begin(), clear.end());
    if (sequenced) message.sequence = static_cast<std::uint32_t>(read_integer(header.subspan(compact ? 9 : 19, 4)));
    return message;
  }
  Aes256Gcm cipher;
  std::uint32_t key_id, latest = 0;
  std::uint64_t epoch, failures = 0, replays = 0;
  bool compact;
  std::vector<std::uint8_t> context, ad, record, clear;
};

MessageStreamFramer::MessageStreamFramer() = default;
MessageStreamFramer::~MessageStreamFramer() = default;
void MessageStreamFramer::authenticate(const Aes256Key& key, std::uint32_t id, std::shared_ptr<TransmitterEpoch> epoch, bool compact) {
  if (authentication_) throw std::logic_error("cannot reinitialize a live message authenticator");
  authentication_ = std::make_unique<AuthenticatedMessageEncoder>(key, id, std::move(epoch), compact);
}
void MessageStreamFramer::set_authentication_context(std::span<const std::uint8_t> context) {
  if (authentication_) authentication_->context.assign(context.begin(), context.end());
}
MessageStreamDeframer::MessageStreamDeframer() = default;
MessageStreamDeframer::~MessageStreamDeframer() = default;
void MessageStreamDeframer::authenticate(const Aes256Key& key, std::uint32_t id, std::uint64_t epoch, bool compact) {
  if (authentication_) throw std::logic_error("cannot reset live replay protection");
  authentication_ = std::make_unique<AuthenticatedMessageDecoder>(key, id, epoch, compact);
}
void MessageStreamDeframer::set_authentication_context(std::span<const std::uint8_t> context) {
  if (authentication_) authentication_->context.assign(context.begin(), context.end());
}
std::uint64_t MessageStreamDeframer::authentication_failures() const noexcept { return authentication_ ? authentication_->failures : 0; }
std::uint64_t MessageStreamDeframer::replay_rejections() const noexcept { return authentication_ ? authentication_->replays : 0; }

RealtimePipelineConfig prepare_transmitter_config(RealtimePipelineConfig config) {
  if (!config.transmitter_epoch) {
    if (config.transmitter_epoch_path.empty()) {
      if (const auto* path = std::getenv("GOBLIN_CANNON_EPOCH_STATE")) config.transmitter_epoch_path = path;
    }
    config.transmitter_epoch = TransmitterEpoch::reserve(config.transmitter_epoch_path,
        std::max<std::uint64_t>(1, config.rf.expected_schedule_epoch));
  }
  config.rf.expected_schedule_epoch = config.transmitter_epoch->value();
  return config;
}

MessageFrameEncodeResult MessageStreamFramer::next_payload_frame(QueueSource<DelimitedMessage>& input,
                                                                 std::span<std::uint8_t> payload_out) {
  if (payload_out.empty()) {
    throw std::invalid_argument("message payload frame must not be empty");
  }

  MessageFrameEncodeResult result;
  std::size_t offset = 0;
  while (offset < payload_out.size()) {
    if (current_offset_ >= current_.size()) {
      DelimitedMessage next;
      if (!input.try_pop(next)) {
        break;
      }
      validate_message(next);
      current_ = std::move(next.bytes);
      if (active_bank_override_.has_value()) {
        current_.front() = *active_bank_override_;
      }
      if (sequence_numbers_ && current_.size() > 1U && !next.sequence.has_value()) {
        next.sequence = next_sequence_++;
      }
      if (observer_ != nullptr) {
        observer_->on_delimited_message(DelimitedMessage{.bytes = current_, .sequence = next.sequence});
      }
      if (authentication_) {
        current_ = authentication_->seal(DelimitedMessage{.bytes = current_, .sequence = next.sequence}, sequence_numbers_);
      } else if (sequence_numbers_ && current_.size() > 1U) {
        auto sequence = *next.sequence;
        std::array<std::uint8_t, 5> encoded{};
        for (auto& byte : encoded) {
          byte = static_cast<std::uint8_t>(2U + sequence % 254U);
          sequence /= 254U;
        }
        current_.insert(current_.begin() + 2, encoded.begin(), encoded.end());
      }
      if (!authentication_) append_message_crc(current_);
      current_offset_ = 0;
      ++result.consumed_messages;
    }

    const auto n = std::min(payload_out.size() - offset, current_.size() - current_offset_);
    std::copy_n(current_.begin() + static_cast<std::ptrdiff_t>(current_offset_),
                static_cast<std::ptrdiff_t>(n),
                payload_out.begin() + static_cast<std::ptrdiff_t>(offset));
    current_offset_ += n;
    offset += n;

    if (current_offset_ == current_.size()) {
      current_.clear();
      current_offset_ = 0;
    }
  }

  result.payload_bytes = offset;
  result.padding_bytes = payload_out.size() - offset;
  result.input_empty = result.padding_bytes != 0U;
  result.message_continues = current_offset_ != 0U && current_offset_ < current_.size();
  std::fill(payload_out.begin() + static_cast<std::ptrdiff_t>(offset),
            payload_out.end(),
            authentication_ ? 0U : active_bank_override_.value_or(0U));
  return result;
}

void MessageStreamFramer::set_active_bank(std::uint8_t bank) {
  if (!is_delimiter(bank)) {
    throw std::invalid_argument("active bank must be 0 or 1");
  }
  active_bank_override_ = bank;
  if (!current_.empty() && !authentication_) {
    current_.front() = bank;
  }
}

void MessageStreamFramer::clear_active_bank_override() noexcept {
  active_bank_override_.reset();
}

void MessageStreamFramer::reset() {
  current_.clear();
  current_offset_ = 0;
}

TransmitMessageQueue::TransmitMessageQueue(std::size_t capacity, std::shared_ptr<std::mutex> decision_log_mutex)
    : capacity_(capacity), decision_log_mutex_(std::move(decision_log_mutex)) {
  if (capacity == 0) throw std::invalid_argument("transmit queue capacity must be positive");
}

bool TransmitMessageQueue::try_push(DelimitedMessage message) {
  validate_message(message);
  std::scoped_lock lock(mutex_);
  if (fifo_.size() == capacity_) return false;
  fifo_.push_back(std::move(message));
  return true;
}

std::size_t TransmitMessageQueue::size_approx() const {
  std::scoped_lock lock(mutex_);
  return fifo_.size() + (best_ ? 1U : 0U);
}

bool TransmitMessageQueue::full() const {
  std::scoped_lock lock(mutex_);
  return fifo_.size() == capacity_;
}

std::size_t TransmitMessageQueue::pending_bids() const {
  std::scoped_lock lock(mutex_);
  return best_ ? 1U : 0U;
}

void TransmitMessageQueue::clear_pending_bid() {
  std::scoped_lock lock(mutex_);
  best_.reset(); // Not yet sent or charged.
}

BidMessageIntakeResult TransmitMessageQueue::offer(BidMessage message,
    SpscRingBuffer<BidMessageLogRecord>& logs, BidMessageLogObserver* observer,
    BidBudgetAccountant* accountant) {
  validate_bid_message(message);
  std::scoped_lock lock(mutex_);
  BidMessageIntakeResult result;
  const auto emit = [&](BidMessageLogRecord record, SpscRingBuffer<BidMessageLogRecord>& destination,
                        BidMessageLogObserver* target) {
    (void)destination.try_push(record);
    if (target) target->on_bid_message_log(record);
    ++result.logged_records;
  };
  if (!can_afford_bid(message, accountant)) {
    if (logs.full()) result.log_backpressure = true;
    else {
      emit(make_budget_exhausted_log(message), logs, observer);
      result.budget_rejected = true;
    }
  } else if (!best_) {
    best_ = Candidate{std::move(message), &logs, observer, accountant};
    result.queued_for_arbitration = true;
  } else {
    const auto& previous = best_->message;
    const bool same_key = !message.has_client_id && !previous.has_client_id &&
        message.payload.size() > 1 && previous.payload.size() > 1 &&
        message.payload[0] == previous.payload[0] && message.payload[1] == previous.payload[1];
    const bool tied = !bid_score_better(message, previous, compact_authentication_) && !bid_score_better(previous, message, compact_authentication_);
    const bool replaces = same_key || tied || bid_score_better(message, previous, compact_authentication_);
    auto& destination = replaces ? *best_->logs : logs;
    if (destination.full()) {
      result.log_backpressure = true;
      // A rejected/retried newer update still makes the old market value
      // obsolete. Log backpressure must not turn it into a later transmission.
      // Neither bid has been charged; the caller can retry the current value.
      if (same_key) best_.reset();
    } else if (replaces) {
      auto rejected = make_bid_log(previous, BidMessageLogStatus::rejected, message.bid_price);
      if (same_key) rejected.detail = "superseded_at_source";
      emit(std::move(rejected), destination, best_->observer);
      best_ = Candidate{std::move(message), &logs, observer, accountant};
      result.queued_for_arbitration = true;
    } else {
      emit(make_bid_log(message, BidMessageLogStatus::rejected, previous.bid_price), logs, observer);
    }
  }
  result.pending_bids = best_ ? 1U : 0U;
  return result;
}

bool TransmitMessageQueue::try_pop(DelimitedMessage& message) {
  // Match the producer's lock order: shared log mutex, then auction mutex.
  std::unique_lock<std::mutex> log_lock;
  if (decision_log_mutex_) log_lock = std::unique_lock<std::mutex>(*decision_log_mutex_);
  std::scoped_lock lock(mutex_);
  if (best_) {
    if (best_->logs->full()) return false;
    auto sent = reserve_sent_bid(make_bid_log(best_->message, BidMessageLogStatus::sent, best_->message.bid_price),
                                 best_->message, best_->accountant);
    (void)best_->logs->try_push(*sent);
    if (best_->observer) best_->observer->on_bid_message_log(*sent);
    if (sent->status != BidMessageLogStatus::budget_exhausted) {
      message = DelimitedMessage{.bytes = std::move(best_->message.payload)};
      best_.reset();
      return true;
    }
    best_.reset();
  }
  if (fifo_.empty()) return false;
  message = std::move(fifo_.front()); fifo_.pop_front();
  return true;
}

BidMessageIntakeResult BidMessageTransmitIntake::submit(BidMessage message,
    TransmitMessageQueue& queue, SpscRingBuffer<BidMessageLogRecord>& logs,
    BidMessageLogObserver* observer, BidBudgetAccountant* accountant) {
  queue_ = &queue;
  return queue.offer(std::move(message), logs, observer, accountant);
}

BidMessageIntakeResult BidMessageTransmitIntake::pump(TransmitMessageQueue& queue,
    SpscRingBuffer<BidMessageLogRecord>&, BidMessageLogObserver*, BidBudgetAccountant*) {
  queue_ = &queue;
  return {.pending_bids = queue.pending_bids()};
}

void BidMessageTransmitIntake::reset() {
  if (const auto queue = queue_.load(std::memory_order_acquire)) queue->clear_pending_bid();
}

bool MessageStreamDeframer::flush_pending(SpscRingBuffer<DelimitedMessage>& output) {
  if (!pending_.has_value()) {
    return true;
  }
  auto message = std::move(*pending_);
  if (!output.try_push(message)) {
    pending_ = std::move(message);
    return false;
  }
  if (observer_ != nullptr) {
    observer_->on_delimited_message(message);
  }
  pending_.reset();
  return true;
}

bool MessageStreamDeframer::push_completed(std::vector<std::uint8_t> message,
                                           SpscRingBuffer<DelimitedMessage>& output,
                                           bool& emitted) {
  emitted = false;
  if (message.size() <= 1U) {
    return true;
  }
  DelimitedMessage completed;
  if (authentication_) {
    const auto failures = authentication_->failures;
    auto verified = authentication_->open(message, sequence_numbers_);
    if (!verified) {
      if (authentication_->failures != failures) report_gap({MessageGapReason::authentication});
      else ++suppressed_messages_;
      return true;
    }
    completed = std::move(*verified);
    if (completed.bytes.size() <= 1) return true;
  } else {
    auto verified = verify_and_strip_message_crc(std::move(message));
    if (!verified) { report_gap({MessageGapReason::checksum}); return true; }
    completed.bytes = std::move(*verified);
  }
  if (sequence_numbers_ && !authentication_) {
    if (completed.bytes.size() < 7U) {
      report_gap({MessageGapReason::malformed});
      return true;
    }
    std::uint64_t sequence = 0;
    for (std::size_t i = 7; i > 2; --i) sequence = sequence * 254U + completed.bytes[i - 1] - 2U;
    if (sequence > std::numeric_limits<std::uint32_t>::max()) {
      report_gap({MessageGapReason::malformed});
      return true;
    }
    completed.sequence = static_cast<std::uint32_t>(sequence);
    completed.bytes.erase(completed.bytes.begin() + 2, completed.bytes.begin() + 7);
  }
  if (sequence_numbers_) {
    const auto key = completed.bytes[0] * 254U + completed.bytes[1] - 2U;
    auto& latest = latest_sequence_[key];
    const auto serial = *completed.sequence;
    const auto distance = serial - latest.value_or(serial);
    // Serial arithmetic: duplicates, older frames, and the ambiguous half of
    // the sequence space are rejected. Ordinary uint32 wrap advances normally.
    if (latest && (distance == 0 || distance >= 0x80000000U)) {
      ++suppressed_messages_;
      return true;
    }
    latest = serial;
  }
  if (output.try_push(completed)) {
    if (observer_ != nullptr) {
      observer_->on_delimited_message(completed);
    }
    emitted = true;
    return true;
  }
  pending_ = std::move(completed);
  return false;
}

MessageFrameDecodeResult MessageStreamDeframer::push_payload_frame(std::span<const std::uint8_t> payload,
                                                                   SpscRingBuffer<DelimitedMessage>& output) {
  std::vector<Token> tokens;
  tokens.reserve(payload.size());
  for (const auto byte : payload) {
    tokens.push_back({.value = byte, .certain = true, .confidence = 1.0F});
  }
  return push_payload_tokens(tokens, output);
}

MessageFrameDecodeResult MessageStreamDeframer::push_payload_tokens(std::span<const Token> payload,
                                                                    SpscRingBuffer<DelimitedMessage>& output) {
  if (payload.empty()) {
    throw std::invalid_argument("message payload frame must not be empty");
  }

  MessageFrameDecodeResult result;
  const bool had_pending = pending_.has_value();
  if (!flush_pending(output)) {
    result.output_backpressure = true;
    result.waiting_for_next_delimiter = current_.size() > 1U;
    return result;
  }
  result.produced_messages += had_pending ? 1U : 0U;

  for (std::size_t i = 0; i < payload.size(); ++i) {
    const auto token = payload[i];
    if (!token.certain || token.confidence <= 0.0F) {
      if (!require_delimiter_) report_gap({MessageGapReason::fec_uncertain});
      current_.clear();
      require_delimiter_ = true;
      ++result.consumed_bytes;
      continue;
    }

    const auto byte = token.value;
    if (authentication_ ? byte == 0 : is_delimiter(byte)) {
      auto completed = std::move(current_);
      current_.clear();
      current_.push_back(byte);
      require_delimiter_ = false;
      ++result.consumed_bytes;
      bool emitted = false;
      if (!push_completed(std::move(completed), output, emitted)) {
        result.output_backpressure = true;
        return result;
      }
      if (emitted) {
        ++result.produced_messages;
      }
      continue;
    }

    if (!require_delimiter_ && !current_.empty()) {
      current_.push_back(byte);
      const auto maximum = authentication_ ? authenticated_message_wire_bytes(maximum_message_bytes, authentication_->compact) : maximum_message_bytes + message_crc_bytes + (sequence_numbers_ ? 5U : 0U);
      if (current_.size() > maximum) {
        report_gap({MessageGapReason::oversized});
        current_.clear();
        require_delimiter_ = true;
      }
    }
    ++result.consumed_bytes;
  }

  result.waiting_for_next_delimiter = current_.size() > 1U;
  return result;
}

void MessageStreamDeframer::report_gap(MessageGap gap) {
  ++gap_count_;
  if (observer_) observer_->on_message_gap(gap);
}

void MessageStreamDeframer::reset() {
  current_.clear();
  pending_.reset();
  require_delimiter_ = true;
}

RealtimeTransmitter::RealtimeTransmitter(RealtimePipelineConfig config, QueueSource<DelimitedMessage>& input)
    : config_(prepare_transmitter_config(std::move(config))),
      input_(input),
      coding_(config_.convolutional, config_.coding),
      rf_(config_.rf),
      constellation_(config_.rf.modem.modulation, config_.rf.modem.constellation_profile) {
  validate_realtime_config(config_);
  framer_.authenticate(config_.aes_key, config_.key_id, config_.transmitter_epoch, config_.compact_message_header);
  framer_.set_sequence_numbers(config_.sequence_numbers);
  if (auto* auction = dynamic_cast<TransmitMessageQueue*>(&input_)) {
    auction->set_sequence_numbers(config_.sequence_numbers);
    auction->set_compact_authentication(config_.compact_message_header);
  }
  if (config_.sync_timestamp.enabled) {
    sync_timestamp_offset_ = 0;
  }
  rf_.start_epoch(config_.frame_counter_start);
}

void RealtimeTransmitter::ensure_symbol_block(RealtimeTransmitResult& result) {
  if (symbol_offset_ < symbols_.size()) {
    return;
  }

  symbols_.clear();
  symbol_offset_ = 0;
  do {
    std::array<std::uint8_t, 1> byte{};
    if (sync_timestamp_offset_ < sync_timestamp_bytes_.size()) {
      if (!sync_timestamp_initialized_) {
        sync_timestamp_bytes_ = encode_native_double(current_epoch_seconds());
        framer_.set_authentication_context(sync_timestamp_bytes_);
        sync_timestamp_initialized_ = true;
      }
      byte[0] = sync_timestamp_bytes_[sync_timestamp_offset_++];
    } else {
      const auto framed = framer_.next_payload_frame(input_, byte);
      result.consumed_messages += framed.consumed_messages;
    }
    ++result.emitted_bytes;

    // Append coded bits straight into pending_bits_ — no intermediate vectors.
    const auto before = pending_bits_.size();
    coding_.push_bytes_append(byte, pending_bits_);
    result.emitted_coded_bits += pending_bits_.size() - before;

    // Pack bits into QAM symbols using a head index instead of erase()ing the
    // front, then amortize compaction when over half the buffer is consumed.
    const auto qam_bits = constellation_.bits_per_symbol();
    while (pending_bits_.size() - pending_bits_head_ >= qam_bits) {
      const auto symbol = constellation_.bits_to_symbol(
          std::span<const std::uint8_t>(pending_bits_).subspan(pending_bits_head_, qam_bits));
      symbols_.push_back(symbol);
      pending_bits_head_ += qam_bits;
    }
    if (pending_bits_head_ > 0U && pending_bits_head_ * 2U >= pending_bits_.size()) {
      pending_bits_.erase(pending_bits_.begin(),
                          pending_bits_.begin() + static_cast<std::ptrdiff_t>(pending_bits_head_));
      pending_bits_head_ = 0U;
    }
  } while (symbols_.empty());
}

RealtimeTransmitResult RealtimeTransmitter::push_samples(std::span<Complex> out) {
  RealtimeTransmitResult result;
  while (result.produced_samples < out.size()) {
    if (symbol_offset_ == symbols_.size()) {
      // Emit acquisition/training and ready pilot audio before claiming a new
      // auction winner. Otherwise the first message becomes immutable for the
      // entire epoch startup even though none of its data is on the wire.
      const auto prefix = rf_.push_symbols({}, out.subspan(result.produced_samples));
      result.produced_samples += prefix.produced_samples;
      if (result.produced_samples == out.size()) break;
    }
    ensure_symbol_block(result);
    const auto symbols = std::span<const std::uint32_t>(symbols_).subspan(symbol_offset_);
    const auto pushed = rf_.push_symbols(symbols, out.subspan(result.produced_samples));
    result.produced_samples += pushed.produced_samples;
    symbol_offset_ += pushed.consumed_symbols;
    if (symbol_offset_ == symbols_.size()) {
      symbols_.clear();
      symbol_offset_ = 0;
    }
    if (pushed.produced_samples == 0U && pushed.consumed_symbols == 0U) {
      break;
    }
  }
  return result;
}

void RealtimeTransmitter::set_active_bank(std::uint8_t bank) {
  framer_.set_active_bank(bank);
}

void RealtimeTransmitter::clear_active_bank_override() noexcept {
  framer_.clear_active_bank_override();
}

std::optional<std::uint8_t> RealtimeTransmitter::active_bank_override() const noexcept {
  return framer_.active_bank_override();
}

void RealtimeTransmitter::set_consumed_message_observer(DelimitedMessageObserver* observer) noexcept {
  framer_.set_consumed_message_observer(observer);
}

RealtimeReceiver::RealtimeReceiver(RealtimePipelineConfig config, SpscRingBuffer<DelimitedMessage>& output)
    : config_(std::move(config)),
      output_(output),
      coding_(config_.convolutional, config_.coding),
      rf_(config_.rf),
      constellation_(config_.rf.modem.modulation, config_.rf.modem.constellation_profile) {
  validate_realtime_config(config_);
  deframer_.authenticate(config_.aes_key, config_.key_id, config_.rf.expected_schedule_epoch, config_.compact_message_header);
  deframer_.set_sequence_numbers(config_.sequence_numbers);
  reset_coded_stream();
}

void RealtimeReceiver::reset_coded_stream() {
  deframer_.reset();
  coding_.reset();
  sync_timestamp_bytes_ = {};
  sync_timestamp_offset_ = 0;
  sync_timestamp_validated_ = !config_.sync_timestamp.enabled;
  stream_aborted_ = false;
  coded_bit_position_ = 0;
  recovery_skip_bits_ = 0;
  coded_gap_ = false;
}

void RealtimeReceiver::reject_stream(RealtimeReceiveResult& result) {
  result.replay_rejected = true;
  stream_aborted_ = true;
  deframer_.reset();
  coding_.reset();
  sync_timestamp_bytes_ = {};
  sync_timestamp_offset_ = 0;
  sync_timestamp_validated_ = false;

  rf_.reset();
}

bool RealtimeReceiver::accept_sync_timestamp_byte(const Token& token, RealtimeReceiveResult& result) {
  if (!token.certain || token.confidence <= 0.0F) {
    reject_stream(result);
    return false;
  }

  sync_timestamp_bytes_[sync_timestamp_offset_++] = token.value;
  if (sync_timestamp_offset_ < sync_timestamp_bytes_.size()) {
    return true;
  }

  const auto timestamp = decode_native_double(std::span<const std::uint8_t, 8>(sync_timestamp_bytes_));
  result.sync_timestamp_seconds = timestamp;
  if (!std::isfinite(timestamp) ||
      std::abs(current_epoch_seconds() - timestamp) > config_.sync_timestamp.max_clock_skew_seconds) {
    reject_stream(result);
    return false;
  }

  sync_timestamp_validated_ = true;
  deframer_.set_authentication_context(sync_timestamp_bytes_);
  result.timestamp_valid = true;
  return true;
}

bool RealtimeReceiver::process_decoded_tokens(std::span<const Token> tokens, RealtimeReceiveResult& result) {
  // Eat sync-timestamp bytes from the front of the token stream until the
  // timestamp is validated. After that, pass the remaining span straight to
  // the deframer with no intermediate copy.
  std::size_t start = 0;
  while (start < tokens.size() && !sync_timestamp_validated_) {
    if (!accept_sync_timestamp_byte(tokens[start], result)) {
      return false;
    }
    ++start;
  }
  if (start >= tokens.size()) {
    return true;
  }

  const auto decoded_messages =
      deframer_.push_payload_tokens(tokens.subspan(start), output_);
  result.produced_messages += decoded_messages.produced_messages;
  result.output_backpressure = result.output_backpressure || decoded_messages.output_backpressure;
  return !decoded_messages.output_backpressure;
}

RealtimeReceiveResult RealtimeReceiver::push_samples(std::span<const Complex> samples) {
  RealtimeReceiveResult result;
  const auto gaps_before = deframer_.gap_count();
  const auto auth_before = deframer_.authentication_failures();
  const auto replay_before = deframer_.replay_rejections();
  auto& symbols = symbol_buffer_;
  std::size_t offset = 0;
  while (offset < samples.size()) {
    const auto n = std::min<std::size_t>(samples.size() - offset, 512U);
    const auto decoded = rf_.push_samples(samples.subspan(offset, n), symbols);
    offset += decoded.consumed_samples;
    result.consumed_samples += decoded.consumed_samples;
    result.acquisition_found = result.acquisition_found || decoded.acquisition_found;
    result.header_valid = result.header_valid || decoded.header_valid;
    result.lock_lost = result.lock_lost || decoded.lock_lost;

    if (!config_.rf.recovery_interval_frames && (decoded.header_valid || decoded.lock_lost)) {
      if (decoded.lock_lost) deframer_.report_gap({MessageGapReason::rf_lock_lost});
      reset_coded_stream();
    }

    std::array<std::uint8_t, max_bits_per_symbol> bits{};
    coded_bits_buffer_.clear();
    coded_bits_buffer_.reserve(decoded.produced_symbols * constellation_.bits_per_symbol());
    const auto flush_coded = [&] {
      if (!stream_aborted_ && !coded_bits_buffer_.empty()) {
        message_tokens_buffer_.clear();
        coding_.push_append(coded_bits_buffer_, message_tokens_buffer_);
        result.decoded_bytes += message_tokens_buffer_.size();
        if (!message_tokens_buffer_.empty()) (void)process_decoded_tokens(message_tokens_buffer_, result);
      }
      coded_bits_buffer_.clear();
    };
    for (std::size_t i = 0; i < decoded.produced_symbols; ++i) {
      if (config_.rf.recovery_interval_frames) {
        if (symbols[i].frame_counter < config_.frame_counter_start) continue;
        const auto frame = symbols[i].frame_counter - config_.frame_counter_start;
        const auto width = static_cast<std::uint64_t>(config_.rf.symbols_per_frame) * constellation_.bits_per_symbol();
        if (frame > (std::numeric_limits<std::uint64_t>::max() - width) / width) continue;
        const auto position = frame * width + static_cast<std::uint64_t>(symbols[i].frame_symbol_offset) * constellation_.bits_per_symbol();
        if (position < coded_bit_position_) continue; // an old marker cannot rewind the stream
        if (position != coded_bit_position_ || coded_gap_) {
          flush_coded();
          deframer_.report_gap({MessageGapReason::rf_lock_lost});
          deframer_.reset();
          // A session that has never validated its timestamp must still do so
          // at the start. The timestamp is also bound into every message tag.
          if (!sync_timestamp_validated_ && position != 0) {
            reject_stream(result);
            break;
          }
          recovery_skip_bits_ = coding_.resume_at_wire_bit(position);
          coded_bit_position_ = position;
          coded_gap_ = false;
        }
      }
      constellation_.symbol_to_bits(symbols[i].value,
                                    std::span<std::uint8_t>(bits).first(constellation_.bits_per_symbol()));
      for (std::size_t bit = 0; bit < constellation_.bits_per_symbol(); ++bit) {
        const SoftBit soft = symbols[i].has_soft_bits ? symbols[i].soft_bits[bit] : SoftBit{.value = bits[bit],
                           .certain = symbols[i].certain,
                           .confidence = symbols[i].confidence};
        ++coded_bit_position_;
        if (recovery_skip_bits_) --recovery_skip_bits_;
        else coded_bits_buffer_.push_back(soft);
      }
    }
    if (stream_aborted_) {
      result.replay_rejected = true;
    } else flush_coded();
    if (config_.rf.recovery_interval_frames && decoded.lock_lost) {
      deframer_.report_gap({MessageGapReason::rf_lock_lost});
      deframer_.reset();
      coded_gap_ = true;
    }
    if (result.output_backpressure || result.replay_rejected || decoded.consumed_samples == 0U) {
      break;
    }
  }
  result.gap_events = deframer_.gap_count() - gaps_before;
  result.authentication_failures = deframer_.authentication_failures() - auth_before;
  result.replay_rejections = deframer_.replay_rejections() - replay_before;
  return result;
}

RealtimeReceiveResult RealtimeReceiver::push_audio_block(std::span<const Complex> samples,
                                                         std::uint64_t first_sample, bool valid) {
  const bool discontinuity = !valid || (next_audio_sample_ && first_sample != *next_audio_sample_);
  if (discontinuity) {
    const auto missing = next_audio_sample_ && first_sample > *next_audio_sample_
        ? first_sample - *next_audio_sample_ : samples.size();
    deframer_.report_gap({MessageGapReason::audio_discontinuity, missing});
    rf_.reset();
    if (config_.rf.recovery_interval_frames) {
      deframer_.reset();
      coded_gap_ = true;
    } else reset_coded_stream();
  }
  next_audio_sample_ = first_sample + samples.size();
  auto result = valid ? push_samples(samples) : RealtimeReceiveResult{.consumed_samples = samples.size()};
  result.gap_events += discontinuity ? 1U : 0U;
  result.lock_lost = result.lock_lost || discontinuity;
  return result;
}

RealtimeReceiveResult RealtimeReceiver::push_timed_audio_block(std::span<const Complex> samples,
    std::uint64_t first_sample, std::uint64_t arrival_sample,
    std::size_t maximum_lateness_samples, bool valid) {
  const auto available_sample = first_sample + samples.size();
  const bool late = arrival_sample > available_sample &&
      arrival_sample - available_sample > maximum_lateness_samples;
  return push_audio_block(samples, first_sample, valid && !late);
}

void RealtimeReceiver::set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept {
  deframer_.set_observer(observer);
}

} // namespace goblin_cannon
