// Simulated channel regressions: assert, quick. All data uses the printed seed.
#include "goblin_cannon/message_stream.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "channel_simulator.hpp"

#include <algorithm>
#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

using namespace goblin_cannon;
namespace {
constexpr std::uint32_t seed = 0x71A003;
void require(bool value, const char* reason) { if (!value) throw std::runtime_error(reason); }

RfStreamConfig config(Modulation modulation, double bandwidth, bool fractional) {
  RfStreamConfig c;
  c.modem.modulation=modulation; c.modem.bandwidth_hz=bandwidth;
  c.expected_schedule_epoch=0x1020304050607080ULL;
  c.acquisition_sequence=make_default_qpsk_sequence(64,seed);
  c.equalizer_training_sequence=make_default_qpsk_sequence(128,seed+1);
  c.pilot_sequence={0,(1U<<bits_per_symbol(modulation))-1};
  c.symbols_per_frame=64; c.pilot_interval_symbols=32;
  c.carrier_correction=false; c.recursive_equalization=true;
  c.compact_header=true; c.recovery_interval_frames=8;
  c.fractionally_spaced_equalization=fractional;
  c.equalizer_reselect_interval=128;
  c.acquisition_confidence_threshold=.25F;
  return c;
}

std::vector<Complex> encode(const RfStreamConfig& c, const std::vector<std::uint32_t>& data, std::size_t chunk) {
  RfStreamEncoder tx(c); tx.start_epoch(100);
  std::vector<Complex> audio, buffer(chunk);
  std::size_t cursor=0;
  while(tx.active()) {
    const auto r=cursor<data.size()?tx.push_symbols(std::span(data).subspan(cursor),buffer):tx.drain(buffer);
    cursor+=r.consumed_symbols;
    audio.insert(audio.end(),buffer.begin(),buffer.begin()+r.produced_samples);
  }
  require(cursor==data.size(),"recurring encoder truncated input");
  return audio;
}

void rf_chunks() {
  for(const auto bandwidth:{10000,24000}) for(const auto mode:{Modulation::qpsk,Modulation::qam16,Modulation::qam64})
      for(const bool fractional:{false,true}) {
    const auto c=config(mode,bandwidth,fractional);
    std::mt19937 random(seed);
    std::vector<std::uint32_t> data(2048);
    for(auto& s:data)s=random()&((1U<<bits_per_symbol(mode))-1);
    auto audio=encode(c,data,193);
    require(audio==encode(c,data,1),"recovery audio depends on TX chunk size");
    audio.insert(audio.end(),48,Complex{});
    for(const auto chunk:{1U,37U,512U}) {
      RfStreamReceiver rx(c); std::array<RfStreamSymbol,1024> symbols{};
      std::size_t seen=0,headers=0;
      for(std::size_t at=0;at<audio.size();at+=chunk) {
        const auto r=rx.push_samples(std::span(audio).subspan(at,std::min<std::size_t>(chunk,audio.size()-at)),symbols);
        require(!r.lock_lost,"null channel lost lock across recovery marker"); headers+=r.header_valid;
        for(std::size_t j=0;j<r.produced_symbols;++j) {
          const auto index=(symbols[j].frame_counter-100)*64+symbols[j].frame_symbol_offset;
          if(index>=data.size())continue;
          require(index==seen && symbols[j].value==data[seen],"recurring marker changed data or frame position"); ++seen;
        }
      }
      require(seen==data.size() && headers>=4,"recurring markers truncated a clean stream");
    }
    auto mismatch=c; ++mismatch.expected_schedule_epoch;
    RfStreamReceiver wrong(mismatch); std::array<RfStreamSymbol,1024> symbols{};
    for(std::size_t at=0;at<audio.size();at+=256) {
      const auto r=wrong.push_samples(std::span(audio).subspan(at,std::min<std::size_t>(256,audio.size()-at)),symbols);
      require(!r.header_valid && !r.produced_symbols,"compact header accepted the wrong epoch");
    }
  }
}

void seek_and_resume() {
  std::mt19937 random(seed);
  std::vector<std::uint8_t> source(128);
  for(auto& b:source)b=random();
  Aes128Key key;for(auto& b:key.bytes)b=random();
  Aes128CtrCounter counter{};counter.back()=250;
  for(const auto& fec:{PuncturedConvolutionalCodeConfig::rate_1_2(),PuncturedConvolutionalCodeConfig::rate_2_3(),
                       PuncturedConvolutionalCodeConfig::rate_3_4()}) {
    const auto coded=convolutional_encode_bytes(source,fec);
    const auto encrypted=aes128_ctr_xor_bits(coded,key,counter);
    for(std::size_t offset=1;offset<200;++offset) {
      Aes128CtrBitXor seek(key,counter,offset);
      auto clear=seek.xor_bits(std::span(encrypted).subspan(offset));
      require(std::equal(clear.begin(),clear.end(),coded.begin()+offset),"CTR seek changed the continuous keystream");
      StreamingSoftViterbiDecoder decoder(fec);
      const auto skip=decoder.resume_at_coded_bit(offset);
      std::size_t first_byte=0;
      while(convolutional_coded_bits_for_input_bytes(first_byte,fec)<offset+skip)++first_byte;
      const auto bytes=decoder.push(hard_bits_to_soft(std::span(clear).subspan(skip)));
      require(!bytes.empty(),"Viterbi failed to resume");
      ++first_byte; // K=7: discard the first byte with unknown encoder history.
      for(std::size_t i=0;i<bytes.size();++i)require(bytes[i].value==source[first_byte+i],"punctured recovery lost source-byte alignment");
    }
  }
}

void messages() {
  for(const auto bandwidth:{10000,24000}) for(const auto mode:{Modulation::qpsk,Modulation::qam16,Modulation::qam64})
      for(const auto& fec:{PuncturedConvolutionalCodeConfig::rate_1_2(),PuncturedConvolutionalCodeConfig::rate_2_3(),
                          PuncturedConvolutionalCodeConfig::rate_3_4()}) {
    RealtimePipelineConfig c;c.rf=config(mode,bandwidth,true);c.convolutional=fec;c.frame_counter_start=100;
    c.sync_timestamp.enabled=false;
    SpscRingBuffer<DelimitedMessage> input(256),output(256);
    RealtimeTransmitter tx(c,input);RealtimeReceiver rx(c,output);
    std::array<Complex,48> audio{};
    test::Impairments impairments;
    impairments.dropout_start_s=.3;impairments.dropout_duration_s=.2;
    test::SimulatedChannel channel(48000,derived_symbol_rate_hz(c.rf.modem)/48000,impairments,seed);
    std::vector<Complex> received_audio;
    std::int64_t last=-1;std::size_t gaps=0,recovered=0;
    for(std::size_t sample=0;sample<48000;++sample) {
      if(sample%2400==0)require(input.try_push(encode_bank_symbol_integer(0,2,sample/2400)),"fixture queue full");
      if(sample%48)continue;
      (void)tx.push_samples(audio);
      channel.process(audio,received_audio);
      if(sample==0)continue; // also exercise joining after missing initial audio
      const auto r=rx.push_audio_block(received_audio,sample);gaps+=r.gap_events;
      DelimitedMessage value;
      while(output.try_pop(value)) {
        const auto decoded=decode_bank_symbol_integer(value);
        require(decoded && decoded->symbol==2 && decoded->value>last && decoded->value<=static_cast<std::int64_t>(sample/2400),
                "recovery delivered corrupt, duplicate or reordered data");
        last=decoded->value;
        recovered+=sample>24000 && decoded->value>=10;
      }
    }
    if(!(gaps>0 && recovered>0))throw std::runtime_error("continuous coded message stream did not recover: bw="+
        std::to_string(bandwidth)+" bits="+std::to_string(bits_per_symbol(mode))+" puncture="+
        std::to_string(fec.puncture_pattern.size())+" gaps="+std::to_string(gaps)+" last="+std::to_string(last));
  }
}
}
int main() {
  std::cout<<"simulated channel recovery regressions; kind=assert tier=quick seed="<<seed<<'\n';
  try {seek_and_resume();rf_chunks();messages();}
  catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
