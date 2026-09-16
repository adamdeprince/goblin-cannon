// Simulated channel; quick/assert D1, D3, D4 and B4 regressions.
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/control_server.hpp"
#include "goblin_cannon/message_stream.hpp"

#include <array>
#include <iostream>
#include <random>
#include <stdexcept>
#include <thread>

using namespace goblin_cannon;
namespace {
constexpr std::uint32_t seed = 0x71A005;
void require(bool condition, const char* message) {
  if (!condition) throw std::runtime_error(message);
}
struct Audit final : DelimitedMessageObserver {
  void on_delimited_message(const DelimitedMessage&) override {}
  void on_message_gap(const MessageGap& gap) override { gaps.push_back(gap.reason); }
  std::vector<MessageGapReason> gaps;
};
struct Budget final : BidBudgetAccountant {
  bool can_afford_bid(const BidMessage& message) const override { return balance >= message.bid_price; }
  BidBudgetReserveResult reserve_sent_bid(const BidMessage& message, std::uint64_t) override {
    ++calls;
    if (message.bid_price > balance) return {false,balance};
    balance -= message.bid_price; return {true,balance};
  }
  std::uint64_t balance = 100;
  std::size_t calls = 0;
};
std::vector<std::uint8_t> wire(std::span<const DelimitedMessage> messages) {
  SpscRingBuffer<DelimitedMessage> input(messages.size()+1);
  std::size_t size=1;
  for (const auto& message : messages) { require(input.try_push(message),"input full"); size+=message.bytes.size()+9; }
  MessageStreamFramer framer; framer.set_sequence_numbers(true);
  std::vector<std::uint8_t> bytes(size);
  (void)framer.next_payload_frame(input,bytes);
  return bytes;
}
void sequencing() {
  auto message=encode_bank_symbol_integer(0,2,100);
  std::array<DelimitedMessage,4> messages{message,message,message,message};
  for (std::size_t i=0;i<messages.size();++i) messages[i].sequence=std::array<std::uint32_t,4>{100,101,100,99}[i];
  MessageStreamDeframer rx; rx.set_sequence_numbers(true);
  SpscRingBuffer<DelimitedMessage> output(1);
  const auto bytes=wire(messages);
  // One-byte input and a one-message output exercise pending output and ensure
  // two identical prices with different sequence numbers both get delivered.
  std::vector<std::uint32_t> observed;
  for (auto byte : bytes) {
    (void)rx.push_payload_frame(std::span(&byte,1),output);
    DelimitedMessage got;
    while(output.try_pop(got)) {
      require(got.bytes==message.bytes && got.sequence.has_value(),"envelope damaged payload");
      observed.push_back(*got.sequence);
    }
  }
  require(observed==std::vector<std::uint32_t>{100,101},"duplicate/stale filtering confused price with sequence");
  require(rx.suppressed_messages()==2,"missing suppression count");
  rx.reset(); // A fade must not erase deduplication history.
  (void)rx.push_payload_frame(wire(std::span(messages).first(1)),output);
  require(output.empty(),"stream reset allowed an old frame through");

  MessageStreamDeframer wrap; wrap.set_sequence_numbers(true);
  for(std::size_t i=0;i<4;++i) messages[i].sequence=std::array<std::uint32_t,4>{0xfffffffeU,0xffffffffU,0,1}[i];
  SpscRingBuffer<DelimitedMessage> wrapped(4);
  (void)wrap.push_payload_frame(wire(messages),wrapped);
  require(wrapped.size_approx()==4,"sequence wrap lost legitimate messages");
}
void gaps_and_bounds() {
  auto first=encode_bank_symbol_integer(0,2,17),second=encode_bank_symbol_integer(0,3,19);
  first.sequence=0;second.sequence=1;
  const auto bytes=wire(std::array{first,second});
  std::vector<Token> tokens;
  for(auto byte:bytes) tokens.push_back({byte,true,1});
  tokens[3].certain=false;
  MessageStreamDeframer rx;rx.set_sequence_numbers(true);Audit audit;rx.set_observer(&audit);
  SpscRingBuffer<DelimitedMessage> output(4);
  (void)rx.push_payload_tokens(tokens,output);
  DelimitedMessage got;
  require(audit.gaps==std::vector{MessageGapReason::fec_uncertain},"FEC erasure produced no explicit gap");
  require(output.try_pop(got) && got.bytes==second.bytes && output.empty(),"FEC recovery crossed a damaged message");
  std::vector<std::uint8_t> oversized(maximum_message_bytes+20,2);oversized[0]=0;
  (void)rx.push_payload_frame(oversized,output);
  require(audit.gaps.back()==MessageGapReason::oversized && output.empty(),"unbounded partial message accepted");
  DelimitedMessage maximum;maximum.bytes.assign(maximum_message_bytes,2);maximum.bytes[0]=1;
  (void)rx.push_payload_frame(wire(std::span(&maximum,1)),output);
  require(output.try_pop(got) && got.bytes==maximum.bytes,"maximum valid frame did not survive");
}
void auction_accounting() {
  TransmitMessageQueue queue(1);BidMessageTransmitIntake intake;Budget budget;
  SpscRingBuffer<BidMessageLogRecord> logs(1);
  BidMessage bid{.payload=encode_bank_symbol_integer(0,2,1).bytes,.bid_price=30,.client_id=0,.has_client_id=true};
  (void)intake.submit(bid,queue,logs,nullptr,&budget);
  require(budget.calls==0 && logs.empty(),"standing bid charged early");
  require(logs.try_push(BidMessageLogRecord{}),"log fill failed");
  DelimitedMessage got;
  require(!queue.try_pop(got) && budget.calls==0,"log backpressure consumed or charged winner");
  BidMessageLogRecord log;require(logs.try_pop(log),"log drain failed");
  require(queue.try_pop(got) && budget.calls==1 && budget.balance==70,"winner was not charged exactly once");
  require(!queue.try_pop(got) && budget.calls==1,"empty queue billed again");
  require(logs.try_pop(log) && log.status==BidMessageLogStatus::sent,"winning charge not logged");
  (void)intake.submit(bid,queue,logs,nullptr,&budget);
  budget.balance=0; // Another transaction spends the budget before airtime.
  require(!queue.try_pop(got) && queue.empty(),"unaffordable winner transmitted");
  require(logs.try_pop(log) && log.status==BidMessageLogStatus::budget_exhausted,"late budget rejection not reported");
}
void concurrent_auction() {
  auto log_mutex=std::make_shared<std::mutex>();
  TransmitMessageQueue queue(1,log_mutex);BidMessageTransmitIntake intake;
  SpscRingBuffer<BidMessageLogRecord> logs(64);
  std::atomic<bool> done=false;
  std::thread producer([&] {
    std::mt19937 random(seed);
    for(int i=0;i<2000;++i) {
      BidMessage bid{.payload=encode_bank_symbol_integer(0,2,i).bytes,.bid_price=1+random()%100};
      while(true) {
        std::scoped_lock lock(*log_mutex);
        if(!intake.submit(bid,queue,logs).log_backpressure)break;
      }
    }
    done=true;
  });
  std::int64_t latest=-1;
  bool ordered=true;
  do {
    DelimitedMessage got;
    if(queue.try_pop(got)) {
      const auto decoded=decode_bank_symbol_integer(got);
      ordered=ordered && decoded && decoded->value>latest;
      if(decoded)latest=decoded->value;
    }
    BidMessageLogRecord record;while(logs.try_pop(record)) {}
  } while(!done || !queue.empty());
  producer.join();
  require(ordered && latest==1999,"concurrent updates reordered or mutated a claimed payload");
}
void audio_gaps() {
  RealtimePipelineConfig config;
  config.sync_timestamp.enabled=false;config.rf.carrier_correction=false;
  config.rf.acquisition_sequence=make_default_qpsk_sequence(64,seed);
  config.rf.equalizer_training_sequence=make_default_qpsk_sequence(64,seed+1);
  config.rf.pilot_sequence={0,3};
  SpscRingBuffer<DelimitedMessage> output(4);RealtimeReceiver receiver(config,output);
  Audit audit;receiver.set_decoded_message_observer(&audit);
  std::array<Complex,48> samples{};
  require(receiver.push_audio_block(samples,0).gap_events==0,"first audio block was a gap");
  require(receiver.push_audio_block(samples,96).gap_events==1,"missing block not detected");
  require(receiver.push_audio_block(samples,144,false).gap_events==1,"underrun not reported");
  require(receiver.push_audio_block(samples,144).gap_events==1,"repeated block not detected");
  require(audit.gaps.size()==3 && output.empty(),"audio gaps failed downstream delivery contract");
  ControlledRealtimeReceiver controlled(config,output);
  controlled.set_decoded_message_observer(&audit);
  require(controlled.push_audio_block(samples,0).gap_events==0,"controlled first block was a gap");
  require(controlled.push_audio_block(samples,96).gap_events==1,"controlled receiver hid a missing block");
  require(controlled.push_timed_audio_block(samples,144,240,48).gap_events==0,"buffer slack boundary caused a false gap");
  require(controlled.push_timed_audio_block(samples,192,289,48).gap_events==1,"late contiguous block produced no gap");
}
void supersession_under_log_backpressure() {
  TransmitMessageQueue queue(1);BidMessageTransmitIntake intake;
  SpscRingBuffer<BidMessageLogRecord> logs(1);
  BidMessage old{.payload=encode_bank_symbol_integer(0,2,10).bytes,.bid_price=100};
  BidMessage fresh{.payload=encode_bank_symbol_integer(0,2,11).bytes,.bid_price=1};
  (void)intake.submit(old,queue,logs);
  require(logs.try_push(BidMessageLogRecord{}),"failed to fill decision log");
  require(intake.submit(fresh,queue,logs).log_backpressure,"log backpressure was hidden");
  BidMessageLogRecord record;(void)logs.try_pop(record);
  DelimitedMessage got;
  require(!queue.try_pop(got),"obsolete market value survived a blocked newer update");
  (void)intake.submit(fresh,queue,logs);
  require(queue.try_pop(got) && got.bytes==fresh.payload,"retry lost the current market value");
}
}
int main() {
  std::cout<<"simulated channel data-path regressions; seed="<<seed<<'\n';
  try {sequencing();gaps_and_bounds();auction_accounting();concurrent_auction();audio_gaps();supersession_under_log_backpressure();}
  catch(const std::exception& error) {std::cerr<<error.what()<<'\n';return 1;}
}
