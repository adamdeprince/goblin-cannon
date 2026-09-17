// Simulated channel PSK regressions: assert / quick; explicit seed below.
#include "goblin_cannon/message_stream.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "differential_psk.hpp"
#include "channel_simulator.hpp"

#include <array>
#include <iostream>
#include <random>
#include <stdexcept>

using namespace goblin_cannon;
namespace {
constexpr std::uint32_t seed = 0x71A004;
void require(bool value, const char* reason) { if (!value) throw std::runtime_error(reason); }

RfStreamConfig config(Modulation mode, DifferentialMapping mapping, Modulation header, int bandwidth) {
  RfStreamConfig c;
  c.modem.modulation=mode; c.modem.bandwidth_hz=bandwidth;
  c.header_modulation=header; c.differential_mapping=mapping;
  c.acquisition_sequence=make_default_qpsk_sequence(64,seed);
  c.equalizer_training_sequence=make_default_qpsk_sequence(128,seed+1);
  c.pilot_sequence={0,(1U<<bits_per_symbol(mode))-1};
  c.symbols_per_frame=32; c.pilot_interval_symbols=32;
  c.carrier_correction=false; c.recursive_equalization=true;
  c.compact_header=true; c.recovery_interval_frames=4;
  c.fractionally_spaced_equalization=true; c.equalizer_reselect_interval=128;
  c.acquisition_confidence_threshold=.25F;
  return c;
}

void mapping_vectors() {
  const std::array<std::uint32_t,4> symbols{0,1,2,3};
  for(const auto mapping:{DifferentialMapping::dbpsk,DifferentialMapping::dqpsk,DifferentialMapping::pi4_dqpsk}) {
    const auto mode=mapping==DifferentialMapping::dbpsk?Modulation::bpsk:Modulation::qpsk;
    const auto c=config(mode,mapping,Modulation::bpsk,24000);
    detail::DifferentialPsk tx(c),rx(c);
    Constellation wire(detail::differential_wire_config(c).modulation);
    const std::array<std::uint32_t,4> expected=mapping==DifferentialMapping::dbpsk?
        std::array<std::uint32_t,4>{0,1,0,0}:mapping==DifferentialMapping::dqpsk?
        std::array<std::uint32_t,4>{0,1,0,2}:std::array<std::uint32_t,4>{1,4,3,0};
    for(std::size_t i=0;i<symbols.size();++i) {
      const auto value=mode==Modulation::bpsk?std::array<std::uint32_t,4>{0,1,1,0}[i]:symbols[i];
      const auto encoded=tx.encode(value);
      const auto phases=mode==Modulation::bpsk?2.0F:mapping==DifferentialMapping::dqpsk?4.0F:8.0F;
      const auto expected_point=std::polar(1.0F,6.283185307179586F*expected[i]/phases);
      require(std::abs(wire.map_symbol(encoded)-expected_point)<1e-6F,"differential phase mapping differs from known vector");
      require(rx.decode(wire.map_symbol(encoded)).symbol==value,"differential known vector did not decode");
    }
    // Continuous phase drift and an arbitrary common rotation must cancel in
    // adjacent-symbol detection. No estimated frequency is fed to this mapper.
    std::mt19937 random(seed);
    tx.reset();rx.reset();
    auto rotation=std::polar(1.0F,1.2F);
    rx.observe_pilot(wire.map_symbol(tx.encode_pilot(0))*rotation);
    for(unsigned i=0;i<4096;++i) {
      const auto value=random()&((1U<<bits_per_symbol(mode))-1);
      rotation=std::polar(1.0F,1.2F+static_cast<float>(i+1)*.01F);
      const auto decoded=rx.decode(wire.map_symbol(tx.encode(value))*rotation);
      require(decoded.symbol==value,"differential phasor failed under common rotation/drift");
      if(i%71==0) {
        const auto pilot=random()&((1U<<bits_per_symbol(mode))-1);
        const auto point=wire.map_symbol(tx.encode_pilot(pilot));
        require(std::abs(point-Constellation(mode).map_symbol(pilot))<1e-6F,"differential pilot changed absolute phase");
        rx.observe_pilot(point*rotation);
      }
    }
  }
  const Constellation bpsk(Modulation::bpsk);
  require(bpsk.bits_per_symbol()==1 && bpsk.map_symbol(0)==Complex(1,0) &&
      bpsk.map_symbol(1)==Complex(-1,0),"BPSK points or energy differ");
  require(bpsk.decide({0,0}).confidence==0,"zero signal produced confident BPSK");
}

std::vector<Complex> encode(const RfStreamConfig& c, const std::vector<std::uint32_t>& payload, std::size_t chunk) {
  RfStreamEncoder tx(c);tx.start_epoch(7000);
  std::vector<Complex> audio,buffer(chunk);std::size_t at=0;
  while(tx.active()) {
    const auto r=at<payload.size()?tx.push_symbols(std::span(payload).subspan(at),buffer):tx.drain(buffer);
    at+=r.consumed_symbols;
    audio.insert(audio.end(),buffer.begin(),buffer.begin()+r.produced_samples);
  }
  require(at==payload.size(),"PSK transmitter truncated input");
  return audio;
}

void stream(const RfStreamConfig& c) {
  std::mt19937 random(seed);std::vector<std::uint32_t> payload(640);
  for(auto& s:payload)s=random()&((1U<<bits_per_symbol(c.modem.modulation))-1);
  auto audio=encode(c,payload,257);
  require(audio==encode(c,payload,1),"PSK waveform depends on TX chunk size");
  audio.insert(audio.end(),48,Complex{});
  for(const auto chunk:{1U,127U}) {
    RfStreamReceiver rx(c);std::array<RfStreamSymbol,1024> output{};std::size_t seen=0,headers=0;
    for(std::size_t at=0;at<audio.size();at+=chunk) {
      const auto r=rx.push_samples(std::span(audio).subspan(at,std::min<std::size_t>(chunk,audio.size()-at)),output);
      require(!r.lock_lost,"PSK lost lock in a null simulated channel");headers+=r.header_valid;
      for(std::size_t i=0;i<r.produced_symbols;++i) {
        const auto index=(output[i].frame_counter-7000)*c.symbols_per_frame+output[i].frame_symbol_offset;
        if(index>=payload.size())continue;
        require(index==seen && output[i].value==payload[index],"PSK data or frame position differs");++seen;
      }
    }
    require(seen==payload.size() && headers>=5,"PSK markers failed to preserve a complete stream");
  }
  if(c.differential_mapping!=DifferentialMapping::none) {
    auto wrong=c;wrong.differential_mapping=DifferentialMapping::none;
    RfStreamReceiver rx(wrong);std::array<RfStreamSymbol,1024> output{};
    for(std::size_t at=0;at<audio.size();at+=127) {
      const auto r=rx.push_samples(std::span(audio).subspan(at,std::min<std::size_t>(127,audio.size()-at)),output);
      require(!r.header_valid && r.produced_symbols==0,"mismatched differential configuration validated");
    }
  }
}

void messages(const RfStreamConfig& rf) {
  RealtimePipelineConfig c;c.rf=rf;c.sync_timestamp.enabled=false;
  // Match the production campaign's marker spacing. The RF-only regression
  // above separately stresses the much shorter four-frame segments.
  c.rf.symbols_per_frame=64;c.rf.recovery_interval_frames=16;
  constexpr std::size_t message_period=9600;
  SpscRingBuffer<DelimitedMessage> input(256),output(256);
  RealtimeTransmitter tx(c,input);RealtimeReceiver rx(c,output);
  test::Impairments impairment;impairment.dropout_start_s=.4;impairment.dropout_duration_s=.2;
  test::SimulatedChannel channel(48000,derived_symbol_rate_hz(rf.modem)/48000,impairment,seed);
  std::array<Complex,48> audio{};std::vector<Complex> received;
  std::int64_t last=-1;std::size_t recovered=0;
  for(std::size_t at=0;at<96000;at+=48) {
    if(at%message_period==0)require(input.try_push(encode_bank_symbol_integer(0,2,at/message_period)),"PSK fixture queue full");
    (void)tx.push_samples(audio);channel.process(audio,received);
    (void)rx.push_audio_block(received,at);
    DelimitedMessage message;
    while(output.try_pop(message)) {
      const auto decoded=decode_bank_symbol_integer(message);
      require(decoded && decoded->symbol==2 && decoded->value>last && decoded->value<=static_cast<std::int64_t>(at/message_period),
          "PSK production pipeline delivered corrupt or reordered data");
      last=decoded->value;recovered+=last>=5;
    }
  }
  require(recovered>0,"PSK production pipeline did not recover after dropout");
}
}

int main() {
  std::cout<<"simulated channel PSK regressions; kind=assert tier=quick seed="<<seed<<'\n';
  try {
    mapping_vectors();
    for(const auto bandwidth:{10000,24000})for(const auto header:{Modulation::qpsk,Modulation::bpsk})
      for(const auto mode:{Modulation::bpsk,Modulation::qpsk,Modulation::psk8})
        for(const auto mapping:{DifferentialMapping::none,DifferentialMapping::dbpsk,DifferentialMapping::dqpsk,DifferentialMapping::pi4_dqpsk}) {
          if(mapping==DifferentialMapping::dbpsk && mode!=Modulation::bpsk)continue;
          if((mapping==DifferentialMapping::dqpsk || mapping==DifferentialMapping::pi4_dqpsk) && mode!=Modulation::qpsk)continue;
          const auto c=config(mode,mapping,header,bandwidth);
          std::cout<<"mode="<<to_string(mode)<<" differential="<<static_cast<int>(mapping)<<" header="<<to_string(header)<<" bw="<<bandwidth<<std::endl;
          stream(c);messages(c);
        }
  } catch(const std::exception& e){std::cerr<<e.what()<<'\n';return 1;}
}
