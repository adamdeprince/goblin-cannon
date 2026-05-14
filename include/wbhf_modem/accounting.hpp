#pragma once

#include "wbhf_modem/message_stream.hpp"
#include "wbhf_modem/symbols.hpp"

#include <array>
#include <cstdint>
#include <filesystem>
#include <map>
#include <mutex>
#include <optional>
#include <span>
#include <vector>

namespace wbhf_modem {

using ClientBudgetsCents = std::array<std::uint64_t, Clients>;
using ClientExpectedLatenciesNs = std::array<std::uint64_t, Clients>;

struct DeliveryAccountingResult {
  bool matched = false;
  std::uint8_t client_id = 0;
  std::uint64_t bid_cents = 0;
  std::uint64_t matched_timestamp_ns = 0;
  std::uint64_t remaining_budget_cents = 0;
};

class ClientBudgetAccounting final : public BidBudgetAccountant {
public:
  ClientBudgetAccounting(ClientBudgetsCents initial_budgets,
                         ClientExpectedLatenciesNs expected_latencies);

  [[nodiscard]] bool can_afford_bid(const BidMessage& message) const override;
  [[nodiscard]] BidBudgetReserveResult reserve_sent_bid(const BidMessage& message,
                                                        std::uint64_t sent_timestamp_ns) override;

  [[nodiscard]] DeliveryAccountingResult acknowledge_delivery(std::span<const std::uint8_t> wire_payload,
                                                              std::uint8_t client_id,
                                                              std::uint64_t receiver_timestamp_ns);
  [[nodiscard]] std::vector<BidMessageLogRecord> expire(std::uint64_t now_ns,
                                                        std::uint64_t max_age_ns = 1'000'000'000ULL);
  void replay_jsonl_log(const std::filesystem::path& log_file);

  [[nodiscard]] std::uint64_t remaining_budget_cents(std::uint8_t client_id) const;
  [[nodiscard]] std::size_t outstanding_count() const;

private:
  struct OutstandingBid {
    std::uint8_t client_id = 0;
    std::uint64_t bid_cents = 0;
  };

  void apply_sent(std::span<const std::uint8_t> payload,
                  std::uint8_t client_id,
                  std::uint64_t bid_cents,
                  std::uint64_t timestamp_ns);
  void apply_remove(std::span<const std::uint8_t> payload,
                    std::uint64_t matched_timestamp_ns,
                    bool refund);

  mutable std::mutex mutex_;
  ClientBudgetsCents remaining_ = {};
  ClientExpectedLatenciesNs expected_latencies_ = {};
  std::map<std::vector<std::uint8_t>, std::map<std::uint64_t, OutstandingBid>> outstanding_;
};

[[nodiscard]] ClientBudgetsCents load_client_budgets_cents_config(
    const std::filesystem::path& path,
    std::uint64_t default_budget_cents = 0);

} // namespace wbhf_modem
