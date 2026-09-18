#pragma once
// Simulated channel D6 audit. Production framer/deframer, explicit seeded
// fixture key, and two separate sender processes sharing a durable journal.
#include "epoch_fixture.hpp"
#include "goblin_cannon/message_stream.hpp"
#include <random>
#include <algorithm>
#include <cerrno>
#include <set>
#include <sys/wait.h>
#include <unistd.h>

namespace goblin_cannon::test {
inline void aead_require(bool condition, const char* why) {
  if (!condition) throw std::runtime_error(why);
}
inline std::vector<std::uint8_t> unstuff(std::span<const std::uint8_t> in) {
  std::vector<std::uint8_t> out;
  for (std::size_t at=0;at<in.size();) {
    const unsigned count=in[at++];
    aead_require(count && count-1<=in.size()-at,"invalid test COBS record");
    for (unsigned i=1;i<count;++i) out.push_back(in[at++]);
    if (count<255 && at<in.size()) out.push_back(0);
  }
  return out;
}
inline std::vector<std::uint8_t> stuff(std::span<const std::uint8_t> in) {
  std::vector<std::uint8_t> out{0,0}; std::size_t code=1; unsigned length=1;
  for (auto b:in) {
    if (!b) {out[code]=length;code=out.size();out.push_back(0);length=1;}
    else {out.push_back(b);if (++length==255) {out[code]=length;code=out.size();out.push_back(0);length=1;}}
  }
  out[code]=length;out.push_back(0);return out;
}
inline std::vector<std::vector<std::uint8_t>> split_records(std::span<const std::uint8_t> wire) {
  std::vector<std::vector<std::uint8_t>> records;
  std::size_t begin=0;
  for (std::size_t i=0;i<wire.size();++i) if (wire[i]==0) {
    if (i>begin+1) records.push_back(unstuff(wire.subspan(begin+1,i-begin-1)));
    begin=i;
  }
  return records;
}
inline std::vector<std::uint8_t> sender_process(const Aes256Key& key, const std::string& path, bool compact=false) {
  int channel[2];aead_require(pipe(channel)==0,"audit pipe");
  const auto pid=fork();aead_require(pid>=0,"audit fork");
  if (!pid) {
    close(channel[0]);
    try {
      SpscRingBuffer<DelimitedMessage> input(8);
      for (unsigned i=0;i<8;++i) (void)input.try_push(DelimitedMessage{.bytes={0,2,static_cast<std::uint8_t>(2+i)}});
      MessageStreamFramer framer;
      framer.set_sequence_numbers(true);
      framer.authenticate(key,71,TransmitterEpoch::reserve(path),compact);
      std::array<std::uint8_t,2048> bytes{};
      const auto result=framer.next_payload_frame(input,bytes);
      const auto size=result.payload_bytes+1;
      if (write(channel[1],bytes.data(),size)!=static_cast<ssize_t>(size)) _exit(2);
      close(channel[1]);_exit(0);
    } catch (...) {_exit(3);}
  }
  close(channel[1]); std::vector<std::uint8_t> bytes;std::array<std::uint8_t,2048> buffer{};
  for (;;) {const auto n=read(channel[0],buffer.data(),buffer.size());if (n==0)break;if(n<0 && errno==EINTR)continue;aead_require(n>0,"audit read");bytes.insert(bytes.end(),buffer.begin(),buffer.begin()+n);}
  close(channel[0]);int status=0;aead_require(waitpid(pid,&status,0)==pid && WIFEXITED(status) && WEXITSTATUS(status)==0,"sender restart failed");
  return bytes;
}
struct AeadAudit {
  unsigned nonces=0, reused_nonces=0, tamper_attempts=0;
  std::uint64_t authentication_failures=0,replay_rejections=0,unverified_deliveries=0;
  std::uint64_t old_epoch_authentication_failures=0;
  unsigned valid_deliveries=0;
};
inline AeadAudit audit_aead(std::uint32_t seed, bool compact=false) {
  EpochFixture state;std::mt19937 random(seed);Aes256Key key;
  for (auto& b:key.bytes)b=static_cast<std::uint8_t>(random());
  const auto first=sender_process(key,state.path,compact),second=sender_process(key,state.path,compact);
  const auto records=split_records(first),restarted=split_records(second);
  aead_require(records.size()==8 && restarted.size()==8,"sender lost records");
  AeadAudit audit;std::set<GcmNonce> nonces;
  for (const auto* group:{&records,&restarted}) for (const auto& record:*group) {
    GcmNonce nonce{};
    if (compact) {
      // These fresh fixture journals reserve epochs 1 and 2 in separate
      // processes. In format 2 the epoch is supplied over fiber, not radio.
      std::uint32_t sequence=0;
      for(unsigned i=5;i<9;++i)sequence=(sequence<<8)|record[i];
      nonce=message_nonce(group==&records?1:2,sequence);
    } else std::copy_n(record.begin()+7,12,nonce.begin());
    ++audit.nonces;audit.reused_nonces+=!nonces.insert(nonce).second;
  }
  MessageStreamDeframer receiver;receiver.set_sequence_numbers(true);receiver.authenticate(key,71,1,compact);
  SpscRingBuffer<DelimitedMessage> output(32);
  // Every authenticated header byte, every ciphertext byte and every tag byte
  // is mutated, including key ID, epoch, frame/app sequence, bank and length.
  for (std::size_t i=0;i<records.front().size();++i) {
    auto corrupted=records.front();corrupted[i]^=static_cast<std::uint8_t>(1U<<(random()%8));
    (void)receiver.push_payload_frame(stuff(corrupted),output);
    ++audit.tamper_attempts;
    audit.unverified_deliveries+=output.size_approx();
  }
  audit.authentication_failures=receiver.authentication_failures();
  (void)receiver.push_payload_frame(first,output);
  audit.valid_deliveries=output.size_approx();DelimitedMessage message;
  while(output.try_pop(message)) {}
  receiver.reset(); // RF reacquisition must retain replay protection.
  (void)receiver.push_payload_frame(first,output);
  audit.unverified_deliveries+=output.size_approx();
  audit.replay_rejections=receiver.replay_rejections();
  MessageStreamDeframer next_session;next_session.set_sequence_numbers(true);next_session.authenticate(key,71,2,compact);
  (void)next_session.push_payload_frame(first,output);
  audit.unverified_deliveries+=output.size_approx();
  audit.replay_rejections+=next_session.replay_rejections();
  audit.old_epoch_authentication_failures=next_session.authentication_failures();
  (void)next_session.push_payload_frame(second,output);
  audit.valid_deliveries+=output.size_approx();
  return audit;
}
}
