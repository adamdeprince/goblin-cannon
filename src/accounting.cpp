#include "wbhf_modem/accounting.hpp"

#include <algorithm>
#include <charconv>
#include <fstream>
#include <limits>
#include <stdexcept>
#include <string>
#include <string_view>

namespace wbhf_modem {

namespace {

std::string trim(std::string_view value) {
  const auto begin = value.find_first_not_of(" \t\r\n");
  if (begin == std::string_view::npos) {
    return {};
  }
  const auto end = value.find_last_not_of(" \t\r\n");
  return std::string(value.substr(begin, end - begin + 1U));
}

std::uint64_t parse_u64(std::string_view value, std::string_view key) {
  const auto text = trim(value);
  std::uint64_t out = 0;
  const auto* first = text.data();
  const auto* last = text.data() + text.size();
  const auto parsed = std::from_chars(first, last, out);
  if (parsed.ec != std::errc{} || parsed.ptr != last) {
    throw std::invalid_argument("invalid integer for " + std::string(key));
  }
  return out;
}

std::uint8_t parse_client_id(std::string_view text, std::string_view key) {
  const auto id = parse_u64(text, key);
  if (id >= Clients) {
    throw std::invalid_argument("client id outside Clients range for " + std::string(key));
  }
  return static_cast<std::uint8_t>(id);
}

std::optional<std::uint64_t> json_u64(std::string_view line, std::string_view key) {
  const auto needle = "\"" + std::string(key) + "\":";
  const auto pos = line.find(needle);
  if (pos == std::string_view::npos) {
    return std::nullopt;
  }
  const auto begin = pos + needle.size();
  auto end = begin;
  while (end < line.size() && line[end] >= '0' && line[end] <= '9') {
    ++end;
  }
  if (end == begin) {
    return std::nullopt;
  }
  return parse_u64(line.substr(begin, end - begin), key);
}

std::optional<std::string> json_string(std::string_view line, std::string_view key) {
  const auto needle = "\"" + std::string(key) + "\":\"";
  const auto pos = line.find(needle);
  if (pos == std::string_view::npos) {
    return std::nullopt;
  }
  std::string out;
  for (auto i = pos + needle.size(); i < line.size(); ++i) {
    const auto ch = line[i];
    if (ch == '"') {
      return out;
    }
    if (ch == '\\' && i + 1U < line.size()) {
      ++i;
      out.push_back(line[i]);
      continue;
    }
    out.push_back(ch);
  }
  return std::nullopt;
}

std::uint8_t hex_digit(char ch) {
  if (ch >= '0' && ch <= '9') {
    return static_cast<std::uint8_t>(ch - '0');
  }
  if (ch >= 'a' && ch <= 'f') {
    return static_cast<std::uint8_t>(10 + ch - 'a');
  }
  if (ch >= 'A' && ch <= 'F') {
    return static_cast<std::uint8_t>(10 + ch - 'A');
  }
  throw std::invalid_argument("invalid hex digit in JSONL payload");
}

std::vector<std::uint8_t> parse_hex(std::string_view text) {
  if ((text.size() % 2U) != 0U) {
    throw std::invalid_argument("hex payload has odd length");
  }
  std::vector<std::uint8_t> out;
  out.reserve(text.size() / 2U);
  for (std::size_t i = 0; i < text.size(); i += 2U) {
    out.push_back(static_cast<std::uint8_t>((hex_digit(text[i]) << 4U) | hex_digit(text[i + 1U])));
  }
  return out;
}

BidMessageLogStatus status_from_string(std::string_view value) {
  if (value == "sent") {
    return BidMessageLogStatus::sent;
  }
  if (value == "rejected") {
    return BidMessageLogStatus::rejected;
  }
  if (value == "budget_exhausted") {
    return BidMessageLogStatus::budget_exhausted;
  }
  if (value == "expired_refunded") {
    return BidMessageLogStatus::expired_refunded;
  }
  if (value == "delivery_matched") {
    return BidMessageLogStatus::delivery_matched;
  }
  if (value == "delivery_unmatched") {
    return BidMessageLogStatus::delivery_unmatched;
  }
  return BidMessageLogStatus::invalid_message_format;
}

} // namespace

ClientBudgetAccounting::ClientBudgetAccounting(ClientBudgetsCents initial_budgets,
                                               ClientExpectedLatenciesNs expected_latencies)
    : remaining_(initial_budgets),
      expected_latencies_(expected_latencies) {}

bool ClientBudgetAccounting::can_afford_bid(const BidMessage& message) const {
  if (!message.has_client_id) {
    return true;
  }
  if (message.client_id >= Clients) {
    return false;
  }
  std::scoped_lock lock(mutex_);
  return remaining_[message.client_id] >= message.bid_price;
}

BidBudgetReserveResult ClientBudgetAccounting::reserve_sent_bid(const BidMessage& message,
                                                                std::uint64_t sent_timestamp_ns) {
  if (!message.has_client_id) {
    return {.accepted = true, .remaining_budget_cents = 0};
  }
  if (message.client_id >= Clients) {
    return {.accepted = false, .remaining_budget_cents = 0};
  }
  std::scoped_lock lock(mutex_);
  if (remaining_[message.client_id] < message.bid_price) {
    return {.accepted = false, .remaining_budget_cents = remaining_[message.client_id]};
  }
  remaining_[message.client_id] -= message.bid_price;
  outstanding_[message.payload][sent_timestamp_ns] =
      OutstandingBid{.client_id = message.client_id, .bid_cents = message.bid_price};
  return {.accepted = true, .remaining_budget_cents = remaining_[message.client_id]};
}

DeliveryAccountingResult ClientBudgetAccounting::acknowledge_delivery(std::span<const std::uint8_t> wire_payload,
                                                                      std::uint8_t client_id,
                                                                      std::uint64_t receiver_timestamp_ns) {
  if (client_id >= Clients) {
    return {};
  }
  const auto expected_sent = receiver_timestamp_ns > expected_latencies_[client_id]
      ? receiver_timestamp_ns - expected_latencies_[client_id]
      : 0U;
  std::vector<std::uint8_t> payload(wire_payload.begin(), wire_payload.end());
  std::scoped_lock lock(mutex_);
  auto outer = outstanding_.find(payload);
  if (outer == outstanding_.end() || outer->second.empty()) {
    return {.matched = false, .client_id = client_id, .remaining_budget_cents = remaining_[client_id]};
  }

  auto best = outer->second.lower_bound(expected_sent);
  auto choose_best = [&](auto lhs, auto rhs) {
    if (lhs == outer->second.end()) {
      return rhs;
    }
    if (rhs == outer->second.end()) {
      return lhs;
    }
    const auto lhs_delta = lhs->first > expected_sent ? lhs->first - expected_sent : expected_sent - lhs->first;
    const auto rhs_delta = rhs->first > expected_sent ? rhs->first - expected_sent : expected_sent - rhs->first;
    return lhs_delta <= rhs_delta ? lhs : rhs;
  };
  if (best != outer->second.begin()) {
    best = choose_best(best, std::prev(best));
  }
  if (best == outer->second.end() || best->second.client_id != client_id) {
    return {.matched = false, .client_id = client_id, .remaining_budget_cents = remaining_[client_id]};
  }

  const auto matched_timestamp = best->first;
  const auto bid = best->second.bid_cents;
  outer->second.erase(best);
  if (outer->second.empty()) {
    outstanding_.erase(outer);
  }
  return {.matched = true,
          .client_id = client_id,
          .bid_cents = bid,
          .matched_timestamp_ns = matched_timestamp,
          .remaining_budget_cents = remaining_[client_id]};
}

std::vector<BidMessageLogRecord> ClientBudgetAccounting::expire(std::uint64_t now_ns, std::uint64_t max_age_ns) {
  std::vector<BidMessageLogRecord> records;
  std::scoped_lock lock(mutex_);
  for (auto outer = outstanding_.begin(); outer != outstanding_.end();) {
    auto& by_time = outer->second;
    for (auto it = by_time.begin(); it != by_time.end();) {
      if (now_ns < it->first || now_ns - it->first <= max_age_ns) {
        break;
      }
      const auto client_id = it->second.client_id;
      const auto bid = it->second.bid_cents;
      remaining_[client_id] += bid;
      BidMessageLogRecord record;
      record.event_type = LogEventType::budget_refund;
      record.local_timestamp_ns = now_ns;
      record.payload = outer->first;
      record.status = BidMessageLogStatus::expired_refunded;
      record.bid_price = bid;
      record.client_id = client_id;
      record.has_client_id = true;
      record.remaining_budget_cents = remaining_[client_id];
      record.matched_timestamp_ns = it->first;
      records.push_back(std::move(record));
      it = by_time.erase(it);
    }
    if (by_time.empty()) {
      outer = outstanding_.erase(outer);
    } else {
      ++outer;
    }
  }
  return records;
}

void ClientBudgetAccounting::apply_sent(std::span<const std::uint8_t> payload,
                                        std::uint8_t client_id,
                                        std::uint64_t bid_cents,
                                        std::uint64_t timestamp_ns) {
  if (client_id >= Clients) {
    return;
  }
  if (remaining_[client_id] >= bid_cents) {
    remaining_[client_id] -= bid_cents;
  } else {
    remaining_[client_id] = 0;
  }
  outstanding_[std::vector<std::uint8_t>(payload.begin(), payload.end())][timestamp_ns] =
      OutstandingBid{.client_id = client_id, .bid_cents = bid_cents};
}

void ClientBudgetAccounting::apply_remove(std::span<const std::uint8_t> payload,
                                          std::uint64_t matched_timestamp_ns,
                                          bool refund) {
  if (matched_timestamp_ns == 0U) {
    return;
  }
  const auto key = std::vector<std::uint8_t>(payload.begin(), payload.end());
  auto outer = outstanding_.find(key);
  if (outer == outstanding_.end()) {
    return;
  }
  auto inner = outer->second.find(matched_timestamp_ns);
  if (inner == outer->second.end()) {
    return;
  }
  if (refund) {
    remaining_[inner->second.client_id] += inner->second.bid_cents;
  }
  outer->second.erase(inner);
  if (outer->second.empty()) {
    outstanding_.erase(outer);
  }
}

void ClientBudgetAccounting::replay_jsonl_log(const std::filesystem::path& log_file) {
  std::ifstream in(log_file);
  if (!in) {
    return;
  }
  std::scoped_lock lock(mutex_);
  std::string line;
  while (std::getline(in, line)) {
    const auto event = json_string(line, "event");
    const auto status_text = json_string(line, "status");
    const auto payload_hex = json_string(line, "payload_hex");
    if (!event.has_value() || !payload_hex.has_value()) {
      continue;
    }
    auto payload = parse_hex(*payload_hex);
    if (*event == "udp_decision") {
      if (!status_text.has_value() || status_from_string(*status_text) != BidMessageLogStatus::sent) {
        continue;
      }
      const auto client = json_u64(line, "client_id");
      const auto bid = json_u64(line, "bid_cents");
      const auto ts = json_u64(line, "ts_ns");
      if (client.has_value() && bid.has_value() && ts.has_value() && *client < Clients) {
        apply_sent(payload, static_cast<std::uint8_t>(*client), *bid, *ts);
      }
    } else if (*event == "receiver_client_message") {
      const auto matched = json_u64(line, "matched_ts_ns");
      if (matched.has_value()) {
        apply_remove(payload, *matched, false);
      }
    } else if (*event == "budget_refund") {
      const auto matched = json_u64(line, "matched_ts_ns");
      if (matched.has_value()) {
        apply_remove(payload, *matched, true);
      }
    }
  }
}

std::uint64_t ClientBudgetAccounting::remaining_budget_cents(std::uint8_t client_id) const {
  if (client_id >= Clients) {
    throw std::invalid_argument("client id outside Clients range");
  }
  std::scoped_lock lock(mutex_);
  return remaining_[client_id];
}

std::size_t ClientBudgetAccounting::outstanding_count() const {
  std::scoped_lock lock(mutex_);
  std::size_t count = 0;
  for (const auto& [_, by_time] : outstanding_) {
    count += by_time.size();
  }
  return count;
}

ClientBudgetsCents load_client_budgets_cents_config(const std::filesystem::path& path,
                                                    std::uint64_t default_budget_cents) {
  std::ifstream in(path);
  if (!in) {
    throw std::runtime_error("failed to open client budget config file");
  }

  ClientBudgetsCents budgets{};
  budgets.fill(default_budget_cents);
  std::string line;
  std::size_t line_number = 0;
  while (std::getline(in, line)) {
    ++line_number;
    const auto comment = line.find('#');
    if (comment != std::string::npos) {
      line.resize(comment);
    }
    const auto equals = line.find('=');
    if (equals == std::string::npos) {
      if (!trim(line).empty()) {
        throw std::invalid_argument("invalid client budget config line " + std::to_string(line_number));
      }
      continue;
    }
    const auto key = trim(std::string_view(line).substr(0, equals));
    const auto value = trim(std::string_view(line).substr(equals + 1U));
    std::uint8_t client_id = 0;
    if (key.starts_with("client.") && key.ends_with(".budget_pennies")) {
      client_id = parse_client_id(std::string_view(key).substr(7U, key.size() - 22U), key);
    } else {
      client_id = parse_client_id(key, key);
    }
    budgets[client_id] = parse_u64(value, key);
  }
  return budgets;
}

} // namespace wbhf_modem
