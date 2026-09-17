// Simulated channel AEAD regressions: assert / quick; seed 0x71A001.
#include "aead_audit.hpp"
#include "goblin_cannon/control_server.hpp"
#include <fstream>
#include <iostream>
#include <thread>

using namespace goblin_cannon;
using test::aead_require;
namespace {
std::vector<std::uint8_t> hex(std::string_view text) {
  std::vector<std::uint8_t> out;
  for (std::size_t i=0;i<text.size();i+=2) out.push_back(std::stoul(std::string(text.substr(i,2)),nullptr,16));
  return out;
}
void known_answer() {
  // NIST GCM zero-key/IV AES-256 vector, also in OpenSSL's EVP test data.
  // A zero IV is ONLY used for this published primitive test vector.
  Aes256Gcm cipher(Aes256Key{});GcmTag tag{};std::vector<std::uint8_t> encrypted,plain;
  const std::array<std::uint8_t,16> zeros{};
  cipher.seal(GcmNonce{}, {}, zeros, encrypted, tag);
  aead_require(encrypted==hex("cea7403d4d606b6e074ec5d3baf39d18"),"GCM known ciphertext");
  aead_require(std::vector(tag.begin(),tag.end())==hex("d0d1c8a799996bf0265b98b5d48ab919"),"GCM known tag");
  aead_require(cipher.open(GcmNonce{}, {}, encrypted,tag,plain) && plain==std::vector(16,std::uint8_t{0}),"GCM known decrypt");
  tag[0]^=1;plain.assign(10,42);
  aead_require(!cipher.open(GcmNonce{}, {}, encrypted,tag,plain) && plain.empty(),"unverified plaintext escaped");
  // Reuse the contexts after both success and failed finalization, with AD.
  for (unsigned i=1;i<=128;++i) {
    const auto nonce=message_nonce(17,i);const auto ad=hex("0102030405");
    std::vector<std::uint8_t> data(i,static_cast<std::uint8_t>(i));
    cipher.seal(nonce,ad,data,encrypted,tag);
    aead_require(cipher.open(nonce,ad,encrypted,tag,plain) && plain==data,"reused GCM context changed key/IV");
    aead_require(!cipher.open(nonce,hex("0102030404"),encrypted,tag,plain) && plain.empty(),"GCM did not authenticate AD");
  }
}
void epoch_storage() {
  test::EpochFixture state;
  auto first=TransmitterEpoch::reserve(state.path);first->claim();
  bool failed=false;try {first->claim();}catch(const std::logic_error&){failed=true;}
  aead_require(failed,"configuration copy reused an epoch");
  std::array<std::uint64_t,16> epochs{};std::vector<std::thread> threads;
  for (auto& value:epochs)threads.emplace_back([&value,&state]{value=TransmitterEpoch::reserve(state.path)->value();});
  for (auto& thread:threads)thread.join();
  aead_require(std::set(epochs.begin(),epochs.end()).size()==16 && *std::min_element(epochs.begin(),epochs.end())==2,"concurrent reservations collided");
  failed=false;try {initialize_transmitter_epoch_store(state.path);}catch(const std::exception&){failed=true;}
  aead_require(failed,"journal reinitialization succeeded");
  failed=false;try {(void)TransmitterEpoch::reserve(state.path+".missing");}catch(const std::exception&){failed=true;}
  aead_require(failed,"missing state silently reset counter");
  {std::ofstream file(state.path,std::ios::app|std::ios::binary);file.put('x');}
  failed=false;try {(void)TransmitterEpoch::reserve(state.path);}catch(const std::exception&){failed=true;}
  aead_require(failed,"torn journal silently reset counter");
  failed=false;try {(void)message_nonce(0,1);}catch(const std::invalid_argument&){failed=true;}
  aead_require(failed,"zero epoch accepted");
  failed=false;try {(void)message_nonce(1,0);}catch(const std::invalid_argument&){failed=true;}
  aead_require(failed,"zero sequence accepted");
}
void bounds_and_context() {
  test::EpochFixture state;Aes256Key key{};
  MessageStreamFramer tx;tx.set_sequence_numbers(true);tx.authenticate(key,1,TransmitterEpoch::reserve(state.path));
  MessageStreamDeframer rx;rx.set_sequence_numbers(true);rx.authenticate(key,1,1);
  const std::array<std::uint8_t,8> timestamp{42};tx.set_authentication_context(timestamp);rx.set_authentication_context(timestamp);
  SpscRingBuffer<DelimitedMessage> input(4),output(4);
  DelimitedMessage largest{.bytes=std::vector<std::uint8_t>(maximum_message_bytes,255)};largest.bytes[0]=1;
  (void)input.try_push(largest);(void)input.try_push(DelimitedMessage{.bytes={0,2}});
  std::vector<std::uint8_t> wire(authenticated_message_wire_bytes(maximum_message_bytes)+100);
  (void)tx.next_payload_frame(input,wire);
  for (std::size_t at=0;at<wire.size();at+=17) (void)rx.push_payload_frame(std::span(wire).subspan(at,std::min<std::size_t>(17,wire.size()-at)),output);
  DelimitedMessage got;
  aead_require(output.try_pop(got) && got.bytes==largest.bytes,"maximum AEAD message lost");
  aead_require(output.try_pop(got) && got.bytes==std::vector<std::uint8_t>{0,2} && output.empty(),"minimum AEAD message lost");
  MessageStreamDeframer changed;changed.set_sequence_numbers(true);changed.authenticate(key,1,1);
  (void)changed.push_payload_frame(wire,output);
  aead_require(output.empty() && changed.authentication_failures()==2,"unauthenticated timestamp accepted");
}
}
int main() {
  try {
    known_answer();epoch_storage();bounds_and_context();
    const auto audit=test::audit_aead(0x71A001);
    aead_require(audit.nonces==16 && audit.reused_nonces==0,"nonce reuse after process restart");
    aead_require(audit.authentication_failures==audit.tamper_attempts && !audit.unverified_deliveries,"tamper reached sink or lacked counter");
    aead_require(audit.valid_deliveries==16 && audit.replay_rejections==16,"replay/session boundary failed");
    std::cout<<"simulated channel: AES-256-GCM assert/quick seed=7446529; restart, AD, tag, replay, bounds and persistence pass\n";
  } catch(const std::exception& e) {std::cerr<<e.what()<<'\n';return 1;}
}
