#include "wbhf_modem/message_stream.hpp"

#include <algorithm>
#include <array>
#include <bit>
#include <chrono>
#include <cmath>
#include <limits>
#include <stdexcept>
#include <utility>

namespace wbhf_modem {

namespace {

bool is_delimiter(std::uint8_t byte) noexcept {
  return byte == 0U || byte == 1U;
}

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

bool bid_score_better(const BidMessage& candidate, const BidMessage& incumbent) noexcept {
  const auto candidate_score = static_cast<long double>(candidate.bid_price) /
                               static_cast<long double>(candidate.payload.size());
  const auto incumbent_score = static_cast<long double>(incumbent.bid_price) /
                               static_cast<long double>(incumbent.payload.size());
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

void validate_realtime_config(const RealtimePipelineConfig& config) {
  validate(config.rf);
  validate(config.convolutional);
  if (config.sync_timestamp.enabled &&
      (!std::isfinite(config.sync_timestamp.max_clock_skew_seconds) ||
       config.sync_timestamp.max_clock_skew_seconds <= 0.0)) {
    throw std::invalid_argument("sync timestamp max_clock_skew_seconds must be positive");
  }
}

} // namespace

MessageFrameEncodeResult MessageStreamFramer::next_payload_frame(SpscRingBuffer<DelimitedMessage>& input,
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
            active_bank_override_.value_or(0U));
  return result;
}

void MessageStreamFramer::set_active_bank(std::uint8_t bank) {
  if (!is_delimiter(bank)) {
    throw std::invalid_argument("active bank must be 0 or 1");
  }
  active_bank_override_ = bank;
  if (!current_.empty()) {
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

BidMessageIntakeResult BidMessageTransmitIntake::submit(BidMessage message,
                                                        SpscRingBuffer<DelimitedMessage>& transmit_queue,
                                                        SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                                        BidMessageLogObserver* observer) {
  validate_bid_message(message);

  auto result = pump(transmit_queue, log_queue, observer);
  if (result.log_backpressure) {
    result.pending_bids = pending_bids();
    return result;
  }

  if (!pending_best_.has_value() && transmit_queue.empty()) {
    if (!log_has_capacity(log_queue, 1U)) {
      result.log_backpressure = true;
      result.pending_bids = pending_bids();
      return result;
    }
    if (!transmit_queue.try_push(DelimitedMessage{.bytes = message.payload})) {
      result.transmit_backpressure = true;
      result.pending_bids = pending_bids();
      return result;
    }
    emit_log(make_bid_log(message, BidMessageLogStatus::sent, message.bid_price), log_queue, observer);
    result.transmitted = true;
    result.logged_records += 1U;
    result.pending_bids = pending_bids();
    return result;
  }

  if (!pending_best_.has_value()) {
    pending_best_ = std::move(message);
    result.queued_for_arbitration = true;
    result.pending_bids = pending_bids();
    return result;
  }

  if (bid_score_better(message, *pending_best_)) {
    if (!log_has_capacity(log_queue, 1U)) {
      result.log_backpressure = true;
      result.pending_bids = pending_bids();
      return result;
    }
    emit_log(make_bid_log(*pending_best_, BidMessageLogStatus::rejected, message.bid_price), log_queue, observer);
    pending_best_ = std::move(message);
    result.queued_for_arbitration = true;
    result.logged_records += 1U;
  } else {
    if (!log_has_capacity(log_queue, 1U)) {
      result.log_backpressure = true;
      result.pending_bids = pending_bids();
      return result;
    }
    emit_log(make_bid_log(message, BidMessageLogStatus::rejected, pending_best_->bid_price), log_queue, observer);
    result.logged_records += 1U;
  }
  result.pending_bids = pending_bids();
  return result;
}

BidMessageIntakeResult BidMessageTransmitIntake::pump(SpscRingBuffer<DelimitedMessage>& transmit_queue,
                                                      SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                                      BidMessageLogObserver* observer) {
  BidMessageIntakeResult result;
  if (!pending_best_.has_value()) {
    return result;
  }
  if (!transmit_queue.empty()) {
    result.transmit_backpressure = true;
    result.pending_bids = pending_bids();
    return result;
  }
  if (!log_has_capacity(log_queue, 1U)) {
    result.log_backpressure = true;
    result.pending_bids = pending_bids();
    return result;
  }

  auto winner = std::move(*pending_best_);
  if (!transmit_queue.try_push(DelimitedMessage{.bytes = winner.payload})) {
    pending_best_ = std::move(winner);
    result.transmit_backpressure = true;
    result.pending_bids = pending_bids();
    return result;
  }
  emit_log(make_bid_log(winner, BidMessageLogStatus::sent, winner.bid_price), log_queue, observer);
  pending_best_.reset();
  result.transmitted = true;
  result.logged_records = 1U;
  result.pending_bids = 0U;
  return result;
}

bool BidMessageTransmitIntake::log_has_capacity(const SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                                std::size_t records) const noexcept {
  return log_queue.capacity() - log_queue.size_approx() >= records;
}

void BidMessageTransmitIntake::emit_log(BidMessageLogRecord record,
                                        SpscRingBuffer<BidMessageLogRecord>& log_queue,
                                        BidMessageLogObserver* observer) {
  (void)log_queue.try_push(record);
  if (observer != nullptr) {
    observer->on_bid_message_log(record);
  }
}

void BidMessageTransmitIntake::reset() {
  pending_best_.reset();
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
                                           SpscRingBuffer<DelimitedMessage>& output) {
  if (message.size() <= 1U) {
    return true;
  }
  DelimitedMessage completed{.bytes = std::move(message)};
  if (output.try_push(completed)) {
    if (observer_ != nullptr) {
      observer_->on_delimited_message(completed);
    }
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
  if (!flush_pending(output)) {
    result.output_backpressure = true;
    result.waiting_for_next_delimiter = current_.size() > 1U;
    return result;
  }

  for (std::size_t i = 0; i < payload.size(); ++i) {
    const auto token = payload[i];
    if (!token.certain || token.confidence <= 0.0F) {
      current_.clear();
      require_delimiter_ = true;
      ++result.consumed_bytes;
      continue;
    }

    const auto byte = token.value;
    if (is_delimiter(byte)) {
      auto completed = std::move(current_);
      const bool should_emit = completed.size() > 1U;
      current_.clear();
      current_.push_back(byte);
      require_delimiter_ = false;
      ++result.consumed_bytes;
      if (!push_completed(std::move(completed), output)) {
        result.output_backpressure = true;
        return result;
      }
      if (should_emit) {
        ++result.produced_messages;
      }
      continue;
    }

    if (!require_delimiter_ && !current_.empty()) {
      current_.push_back(byte);
    }
    ++result.consumed_bytes;
  }

  result.waiting_for_next_delimiter = current_.size() > 1U;
  return result;
}

void MessageStreamDeframer::reset() {
  current_.clear();
  pending_.reset();
  require_delimiter_ = true;
}

RealtimeTransmitter::RealtimeTransmitter(RealtimePipelineConfig config, SpscRingBuffer<DelimitedMessage>& input)
    : config_(std::move(config)),
      input_(input),
      convolutional_(config_.convolutional),
      bit_xor_(config_.aes_key, config_.ctr_counter),
      rf_(config_.rf),
      constellation_(config_.rf.modem.modulation, config_.rf.modem.constellation_profile) {
  validate_realtime_config(config_);
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
  std::array<std::uint8_t, 1> byte{};
  if (sync_timestamp_offset_ < sync_timestamp_bytes_.size()) {
    if (!sync_timestamp_initialized_) {
      sync_timestamp_bytes_ = encode_native_double(current_epoch_seconds());
      sync_timestamp_initialized_ = true;
    }
    byte[0] = sync_timestamp_bytes_[sync_timestamp_offset_++];
  } else {
    const auto framed = framer_.next_payload_frame(input_, byte);
    result.consumed_messages += framed.consumed_messages;
  }
  ++result.emitted_bytes;

  auto coded = convolutional_.push_bytes(byte);
  auto scrambled = bit_xor_.xor_bits(coded);
  result.emitted_coded_bits += scrambled.size();
  pending_bits_.insert(pending_bits_.end(), scrambled.begin(), scrambled.end());

  const auto qam_bits = constellation_.bits_per_symbol();
  while (pending_bits_.size() >= qam_bits) {
    const auto symbol = constellation_.bits_to_symbol(std::span<const std::uint8_t>(pending_bits_).first(qam_bits));
    symbols_.push_back(symbol);
    pending_bits_.erase(pending_bits_.begin(), pending_bits_.begin() + static_cast<std::ptrdiff_t>(qam_bits));
  }
}

RealtimeTransmitResult RealtimeTransmitter::push_samples(std::span<Complex> out) {
  RealtimeTransmitResult result;
  while (result.produced_samples < out.size()) {
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

RealtimeReceiver::RealtimeReceiver(RealtimePipelineConfig config, SpscRingBuffer<DelimitedMessage>& output)
    : config_(std::move(config)),
      output_(output),
      viterbi_(config_.convolutional),
      bit_xor_(config_.aes_key, config_.ctr_counter),
      rf_(config_.rf),
      constellation_(config_.rf.modem.modulation, config_.rf.modem.constellation_profile) {
  validate_realtime_config(config_);
  reset_coded_stream();
}

void RealtimeReceiver::reset_coded_stream() {
  deframer_.reset();
  bit_xor_ = Aes128CtrBitXor(config_.aes_key, config_.ctr_counter);
  coded_bits_.clear();
  emitted_bytes_ = 0;
  sync_timestamp_bytes_ = {};
  sync_timestamp_offset_ = 0;
  sync_timestamp_validated_ = !config_.sync_timestamp.enabled;
  stream_aborted_ = false;
}

void RealtimeReceiver::reject_stream(RealtimeReceiveResult& result) {
  result.replay_rejected = true;
  stream_aborted_ = true;
  deframer_.reset();
  coded_bits_.clear();
  emitted_bytes_ = 0;
  sync_timestamp_bytes_ = {};
  sync_timestamp_offset_ = 0;
  sync_timestamp_validated_ = false;
  bit_xor_ = Aes128CtrBitXor(config_.aes_key, config_.ctr_counter);
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
  result.timestamp_valid = true;
  return true;
}

bool RealtimeReceiver::process_decoded_tokens(std::span<const Token> tokens, RealtimeReceiveResult& result) {
  std::vector<Token> message_tokens;
  message_tokens.reserve(tokens.size());

  for (const auto& token : tokens) {
    if (!sync_timestamp_validated_) {
      if (!accept_sync_timestamp_byte(token, result)) {
        return false;
      }
      continue;
    }
    message_tokens.push_back(token);
  }

  if (message_tokens.empty()) {
    return true;
  }

  const auto decoded_messages = deframer_.push_payload_tokens(message_tokens, output_);
  result.produced_messages += decoded_messages.produced_messages;
  result.output_backpressure = result.output_backpressure || decoded_messages.output_backpressure;
  return !decoded_messages.output_backpressure;
}

void RealtimeReceiver::try_decode_bytes(RealtimeReceiveResult& result) {
  if (stream_aborted_) {
    result.replay_rejected = true;
    return;
  }

  std::size_t possible_bytes = emitted_bytes_;
  while (convolutional_coded_bits_for_input_bytes(possible_bytes + 1U, config_.convolutional) <= coded_bits_.size()) {
    ++possible_bytes;
  }
  if (possible_bytes == emitted_bytes_) {
    return;
  }

  const auto needed_bits = convolutional_coded_bits_for_input_bytes(possible_bytes, config_.convolutional);
  const auto decoded = viterbi_.decode_bytes(std::span<const SoftBit>(coded_bits_).first(needed_bits), possible_bytes);
  std::vector<Token> new_bytes;
  new_bytes.reserve(possible_bytes - emitted_bytes_);
  for (std::size_t i = emitted_bytes_; i < decoded.bytes.size(); ++i) {
    new_bytes.push_back(decoded.bytes[i]);
  }
  emitted_bytes_ = possible_bytes;
  result.decoded_bytes += new_bytes.size();
  if (!new_bytes.empty()) {
    (void)process_decoded_tokens(new_bytes, result);
  }
}

RealtimeReceiveResult RealtimeReceiver::push_samples(std::span<const Complex> samples) {
  RealtimeReceiveResult result;
  std::array<RfStreamSymbol, 512> symbols{};
  std::size_t offset = 0;
  while (offset < samples.size()) {
    const auto n = std::min<std::size_t>(samples.size() - offset, 512U);
    const auto decoded = rf_.push_samples(samples.subspan(offset, n), symbols);
    offset += decoded.consumed_samples;
    result.consumed_samples += decoded.consumed_samples;
    result.acquisition_found = result.acquisition_found || decoded.acquisition_found;
    result.header_valid = result.header_valid || decoded.header_valid;
    result.lock_lost = result.lock_lost || decoded.lock_lost;

    if (decoded.header_valid || decoded.lock_lost) {
      reset_coded_stream();
    }

    std::array<std::uint8_t, max_bits_per_symbol> bits{};
    for (std::size_t i = 0; i < decoded.produced_symbols; ++i) {
      constellation_.symbol_to_bits(symbols[i].value,
                                    std::span<std::uint8_t>(bits).first(constellation_.bits_per_symbol()));
      for (std::size_t bit = 0; bit < constellation_.bits_per_symbol(); ++bit) {
        const SoftBit soft{.value = bits[bit],
                           .certain = symbols[i].certain,
                           .confidence = symbols[i].confidence};
        coded_bits_.push_back(bit_xor_.xor_soft_bit(soft));
      }
    }
    try_decode_bytes(result);
    if (result.output_backpressure || result.replay_rejected || decoded.consumed_samples == 0U) {
      break;
    }
  }
  return result;
}

void RealtimeReceiver::set_decoded_message_observer(DelimitedMessageObserver* observer) noexcept {
  deframer_.set_observer(observer);
}

} // namespace wbhf_modem
