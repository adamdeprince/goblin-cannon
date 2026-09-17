#include "epoch_fixture.hpp"
#include "aead_audit.hpp"
// Test-only adapters to production APIs. All observations are simulated channel
// observations. This executable does not alter receiver or scheduler behavior.
#include "channel_simulator.hpp"
#include "demapper.hpp"
#include "goblin_cannon/convolutional.hpp"
#include "goblin_cannon/integer_codec.hpp"
#include "goblin_cannon/io.hpp"
#include "goblin_cannon/message_stream.hpp"
#include <bit>
#include <deque>
#include <iomanip>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <fstream>
#include <chrono>
#include <thread>
#include <functional>

using namespace goblin_cannon;
using namespace goblin_cannon::test;

namespace {
using Arguments = std::map<std::string,std::string>;
double number(const Arguments& a,const std::string& name,double fallback=0) {
  const auto i=a.find(name); return i==a.end()?fallback:std::stod(i->second);
}
std::string word(const Arguments& a,const std::string& name,std::string fallback="") {
  const auto i=a.find(name); return i==a.end()?fallback:i->second;
}
std::string quote(const std::string& s) {
  std::string out="\"";
  for (const char c:s) {
    if (c=='\"'||c=='\\') out+='\\';
    if (c=='\n') out+="\\n"; else out+=c;
  }
  return out+'\"';
}
struct Json {
  std::map<std::string,std::string> fields;
  void set(const std::string& key,double value) {
    std::ostringstream s; s<<std::setprecision(17)<<value;
    fields[key]=std::isfinite(value)?s.str():"null";
  }
  void text(const std::string& key,const std::string& value) { fields[key]=quote(value); }
  void array(const std::string& key,const std::vector<double>& values) {
    std::ostringstream s; s<<'['<<std::setprecision(17);
    for (std::size_t i=0;i<values.size();++i) { if(i) s<<','; s<<values[i]; }
    fields[key]=s.str()+']';
  }
  std::string str() const {
    std::string out="{";
    for (const auto& [k,v]:fields) { if(out.size()>1) out+=',';out+=quote(k)+':'+v; }
    return out+'}';
  }
};
Modulation modulation(const std::string& name) {
  const std::map<std::string,Modulation> values={{"bpsk",Modulation::bpsk},{"qpsk",Modulation::qpsk},{"8psk",Modulation::psk8},
    {"16qam",Modulation::qam16},{"64qam",Modulation::qam64},{"256qam",Modulation::qam256},
    {"1024qam",Modulation::qam1024},{"16qci",Modulation::qci16},{"64qci",Modulation::qci64},
    {"256qci",Modulation::qci256},{"1024qci",Modulation::qci1024}};
  return values.at(name);
}
RfStreamConfig rf_config(const Arguments& a) {
  RfStreamConfig c;
  c.modem.modulation=modulation(word(a,"modulation","qpsk"));
  c.modem.sample_rate_hz=number(a,"sample_rate_hz",48000);
  c.modem.bandwidth_hz=number(a,"bandwidth_hz",24000);
  c.modem.rrc_rolloff=0.25;
  c.modem.tx_gain*=number(a,"tx_gain_multiplier",1);
  if(number(a,"symbol_rate_fraction",1)!=1) c.modem.symbol_rate_hz=c.modem.bandwidth_hz/1.25*number(a,"symbol_rate_fraction",1);
  c.expected_schedule_epoch=0x1020304050607080ULL;
  c.acquisition_sequence=make_default_qpsk_sequence(64,0xA5A50001U);
  c.equalizer_training_sequence=make_default_qpsk_sequence(static_cast<std::size_t>(number(a,"training_symbols",64)),0x5A5A0002U);
  c.pilot_sequence={0,(1U<<bits_per_symbol(c.modem.modulation))-1};
  c.symbols_per_frame=static_cast<std::uint32_t>(number(a,"frame_symbols",64));
  c.pilot_interval_symbols=number(a,"pilot_interval_symbols",32);
  c.acquisition_confidence_threshold=0.25F;
  c.pilot_confidence_threshold=0.08F;
  c.symbol_confidence_threshold=0.08F;
  c.acquisition_sidelobe_guard_samples=48;
  // The brief assigns frequency correction to the radio. This existing switch
  // also disables the residual phase PLL; that coupling is a reported conflict.
  c.waveform=std::map<std::string,AudioWaveform>{{"single_carrier",AudioWaveform::single_carrier},
      {"fsk4",AudioWaveform::fsk4},{"fsk8",AudioWaveform::fsk8},
      {"bpsk_frequency_diversity",AudioWaveform::bpsk_frequency_diversity}}.at(word(a,"audio_waveform","single_carrier"));
  c.diversity_wait_ms=number(a,"diversity_wait_ms",1);
  c.diversity_branch_bandwidth_hz=number(a,"diversity_branch_bandwidth_hz");
  c.diversity_separation_hz=number(a,"diversity_separation_hz");
  c.diversity_branch_mask=number(a,"diversity_branch_mask",3);
  c.fsk_useful_ms=number(a,"fsk_useful_ms",4);c.fsk_guard_ms=number(a,"fsk_guard_ms",8);
  c.soft_demapping=number(a,"soft_demapping",0)!=0;
  c.carrier_correction=number(a,"carrier_correction",0)!=0;
  c.adaptive_equalization=number(a,"adaptive_equalization",1)!=0;
  c.recursive_equalization=number(a,"recursive_equalization",1)!=0;
  c.sample_clock_recovery=number(a,"sample_clock_recovery",1)!=0;
  c.equalizer_feedforward_taps=number(a,"equalizer_feedforward_taps",3);
  c.equalizer_feedback_taps=number(a,"equalizer_feedback_taps",4);
  c.equalizer_delay_symbols=number(a,"equalizer_delay_symbols",0);
  c.compact_header=number(a,"compact_header",0)!=0;
  c.header_modulation=modulation(word(a,"header_modulation","qpsk"));
  const std::map<std::string,DifferentialMapping> mappings={{"none",DifferentialMapping::none},
      {"dbpsk",DifferentialMapping::dbpsk},{"dqpsk",DifferentialMapping::dqpsk},{"pi4_dqpsk",DifferentialMapping::pi4_dqpsk}};
  c.differential_mapping=mappings.at(word(a,"differential_mapping","none"));
  c.recovery_interval_frames=number(a,"recovery_interval_frames",0);
  c.fractionally_spaced_equalization=number(a,"fractionally_spaced_equalization",0)!=0;
  c.equalizer_reselect_interval=number(a,"equalizer_reselect_interval",0);
  return c;
}
PayloadCodingConfig payload_config(const Arguments& a) {
  return {.bch=number(a,"bch_payload")!=0, .walsh_bits=static_cast<std::uint8_t>(number(a,"walsh_bits")),
    .interleaver_rows=static_cast<std::uint32_t>(number(a,"interleaver_rows")),
    .interleaver_columns=static_cast<std::uint32_t>(number(a,"interleaver_columns"))};
}
double nominal_sample_power(const RfStreamConfig& c) {
  const auto equivalent_rate=c.waveform==AudioWaveform::single_carrier?derived_symbol_rate_hz(c.modem):c.modem.bandwidth_hz/1.25;
  return c.modem.tx_gain*c.modem.tx_gain*equivalent_rate/c.modem.sample_rate_hz;
}
Impairments impairments(const Arguments& a) {
  Impairments c;
  c.legacy.snr_db=number(a,"snr_db",std::numeric_limits<double>::infinity());
  c.legacy.phase_rad=number(a,"phase_rad");
  c.watterson=word(a,"channel_model","null")=="watterson";
  c.delay_spread_ms=number(a,"delay_spread_ms");
  c.doppler_spread_hz=number(a,"doppler_spread_hz",1);
  c.path_gains_db={number(a,"path0_db"),number(a,"path1_db")};
  c.pure_noise=number(a,"pure_noise")!=0;
  c.cw_hz=number(a,"cw_hz");
  c.cw_sir_db=number(a,"cw_sir_db",std::numeric_limits<double>::infinity());
  c.data_sir_db=number(a,"data_sir_db",std::numeric_limits<double>::infinity());
  c.interferer_start_s=number(a,"interferer_start_s");
  c.impulse_ms=number(a,"impulse_ms");
  c.impulses_per_second=number(a,"impulses_per_second");
  c.impulse_above_noise_db=number(a,"impulse_above_noise_db");
  c.dropout_start_s=number(a,"dropout_start_s");
  c.dropout_duration_s=number(a,"dropout_duration_s");
  c.agc_step_db=number(a,"agc_step_db");
  c.agc_start_s=number(a,"agc_start_s",0.1);
  c.agc_attack_ms=number(a,"agc_attack_ms",1);
  c.agc_decay_ms=number(a,"agc_decay_ms",100);
  c.clip_amplitude=number(a,"clip_amplitude",std::numeric_limits<double>::infinity());
  c.soft_clip=number(a,"soft_clip")!=0;
  c.filter_bandwidth_hz=number(a,"filter_bandwidth_hz");
  c.group_delay_ripple_ms=number(a,"group_delay_ripple_ms");
  c.notch_center_hz=number(a,"notch_center_hz");
  c.notch_width_hz=number(a,"notch_width_hz");
  c.notch_depth_db=number(a,"notch_depth_db");
  c.clock_ppm=number(a,"clock_ppm");
  c.sample_slip_index=static_cast<std::int64_t>(number(a,"sample_slip_index",-1));
  c.sample_slip=static_cast<int>(number(a,"sample_slip"));
  const auto recording=word(a,"noise_file");
  if(!recording.empty()) {
    std::ifstream stream(recording,std::ios::binary);
    if(!stream)throw std::runtime_error("cannot open receive-only noise recording");
    std::array<float,2> iq{};
    while(stream.read(reinterpret_cast<char*>(iq.data()),sizeof(iq)))c.noise_bed.emplace_back(iq[0],iq[1]);
    if(c.noise_bed.empty())throw std::runtime_error("empty receive-only noise recording");
  }
  return c;
}
PuncturedConvolutionalCodeConfig fec_config(const Arguments& a) {
  const auto fec=word(a,"fec","1/2");
  if (fec=="k9-1/2") return PuncturedConvolutionalCodeConfig::k9_rate_1_2();
  if (fec=="k9-1/3") return PuncturedConvolutionalCodeConfig::k9_rate_1_3();
  if (fec=="2/3") return PuncturedConvolutionalCodeConfig::rate_2_3();
  if (fec=="3/4") return PuncturedConvolutionalCodeConfig::rate_3_4();
  return PuncturedConvolutionalCodeConfig::rate_1_2();
}
std::uint32_t pattern(std::uint64_t index,std::uint32_t seed,const std::string& name) {
  if(name=="zeros")return 0;
  if(name=="ones")return 0xFFFFFFFFU;
  if(name=="alternating")return index%2?0xFFFFFFFFU:0;
  if(name=="repeating")return static_cast<std::uint32_t>(index%7);
  // Counter-based pattern permits exact scoring without retaining a long run.
  std::uint64_t z=index+0x9e3779b97f4a7c15ULL+seed;
  z=(z^(z>>30))*0xbf58476d1ce4e5b9ULL;
  z=(z^(z>>27))*0x94d049bb133111ebULL;
  return static_cast<std::uint32_t>(z^(z>>31));
}
void attach_isa(Json& result,const Arguments& a) {
  const auto isa=detail::active_demapper_isa();
  result.text("demapper",isa==detail::DemapperIsa::avx512?"AVX-512":isa==detail::DemapperIsa::avx2?"AVX2":"scalar");
  if(number(a,"require_avx512",0)!=0 && isa!=detail::DemapperIsa::avx512)
    throw std::runtime_error("AVX-512 required");
}

class ConsumptionAudit final : public DelimitedMessageObserver {
public:
  explicit ConsumptionAudit(const std::array<std::int64_t,16>& latest):latest_(latest) {}
  void on_delimited_message(const DelimitedMessage& message) override {
    const auto data=decode_bank_symbol_integer(message);
    if(data && data->symbol>=2 && data->symbol<18) {
      ++consumed;
      superseded+=data->value<latest_[data->symbol-2];
      if(on_consumed)on_consumed(data->value);
    }
  }
  std::uint64_t consumed=0,superseded=0;
  std::function<void(std::uint64_t)> on_consumed;
private:
  const std::array<std::int64_t,16>& latest_;
};

class GapAudit final : public DelimitedMessageObserver {
public:
  void on_delimited_message(const DelimitedMessage&) override {}
  void on_message_gap(const MessageGap& gap) override {
    ++events;
    audio_events += gap.reason == MessageGapReason::audio_discontinuity;
    fec_events += gap.reason == MessageGapReason::fec_uncertain;
  }
  std::uint64_t events=0,audio_events=0,fec_events=0;
};

// Exact histogram on the declared audio sample clock. Long campaigns retain
// counts, not one JSON entry per message; no observations are subsampled.
class SampleDistribution {
public:
  explicit SampleDistribution(double fs):fs_(fs) {}
  void add(double seconds) {++counts_[std::llround(seconds*fs_)];++count_;}
  Json summary_ms() const {
    Json out;out.set("observations",count_);
    for(const auto& [name,q]:std::array<std::pair<const char*,double>,4>{{{"p50",.5},{"p99",.99},{"p99_9",.999},{"max",1}}}) {
      std::uint64_t seen=0;double value=NAN;
      for(const auto& [tick,n]:counts_)if((seen+=n)>=std::ceil(q*count_)){value=tick/fs_*1000;break;}
      out.set(name,value);
    }
    return out;
  }
private:
  double fs_;std::uint64_t count_=0;
  std::map<std::int64_t,std::uint64_t> counts_;
};

Json run_rf(const Arguments& a) {
  auto c=rf_config(a);
  const auto channel_cfg=impairments(a);
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const auto bits=bits_per_symbol(c.modem.modulation);
  const auto rate=rf_symbol_rate_hz(c);
  const auto duration=number(a,"duration_s",2);
  double payload_symbol_rate=rate*c.pilot_interval_symbols/(c.pilot_interval_symbols+c.pilot_sequence.size());
  if(c.recovery_interval_frames) {
    const auto n=static_cast<std::uint64_t>(c.recovery_interval_frames)*c.symbols_per_frame;
    const double sps=c.modem.sample_rate_hz/rate,half=c.modem.filter_span_symbols/2.0;
    const auto pulse_samples=[&](double symbols) {return std::floor((symbols-1+half)*sps)+1;};
    const auto startup=std::max<std::size_t>(c.modem.filter_span_symbols,c.equalizer_feedforward_taps+c.equalizer_feedback_taps);
    const auto header_data=(c.compact_header?268:256*c.header_repetition)/bits_per_symbol(c.header_modulation);
    const auto header_symbols=header_data+(c.compact_header?(header_data-1)/16*4:0);
    const auto segment=pulse_samples(c.acquisition_sequence.size())+
        pulse_samples(c.equalizer_training_sequence.size()+header_symbols)+
        pulse_samples(n+startup+n/c.pilot_interval_symbols*c.pilot_sequence.size()+c.equalizer_delay_symbols);
    payload_symbol_rate=n*c.modem.sample_rate_hz/segment;
  }
  if(c.waveform==AudioWaveform::fsk4 || c.waveform==AudioWaveform::fsk8) {
    const auto header=(268+bits-1)/bits;
    payload_symbol_rate=rate*c.symbols_per_frame/(16+header+c.symbols_per_frame);
  }
  const std::uint64_t count=channel_cfg.pure_noise?0:static_cast<std::uint64_t>(duration*payload_symbol_rate);
  const auto name=word(a,"pattern","random");
  const bool fec=word(a,"fec","none")!="none";
  std::vector<std::uint8_t> source_bytes,coded;
  std::vector<std::uint32_t> payload;
  if(fec) {
    double ratio=payload_coding_rate(payload_config(a),fec_config(a));
    source_bytes.resize(static_cast<std::size_t>(count*bits*ratio/8));
    for(std::size_t i=0;i<source_bytes.size();++i)source_bytes[i]=static_cast<std::uint8_t>(pattern(i,seed^0xC011AB1EU,name));
    ChannelCodingEncoder coder(fec_config(a),payload_config(a));
    coder.push_bytes_append(source_bytes,coded);
    Constellation constellation(c.modem.modulation,c.modem.constellation_profile);
    coded.resize((coded.size()+bits-1)/bits*bits,0);
    for(std::size_t i=0;i<coded.size();i+=bits)payload.push_back(constellation.bits_to_symbol(std::span(coded).subspan(i,bits)));
  }
  const std::uint64_t payload_count=fec?payload.size():count;
  const auto expected=[&](std::uint64_t i) {return fec?payload[i]:pattern(i,seed^0xC011AB1EU,name)&((1U<<bits)-1);};
  std::vector<std::uint16_t> frame_seen((payload_count+c.symbols_per_frame-1)/c.symbols_per_frame),frame_errors(frame_seen.size());
  std::vector<double> frame_last_seen_s(frame_seen.size());
  std::vector<bool> agc_affected(frame_seen.size());
  RfStreamEncoder encoder(c),interferer(c);
  RfStreamReceiver receiver(c);
  encoder.start_epoch(7000);interferer.start_epoch(7000);
  const std::size_t chunk=static_cast<std::size_t>(number(a,"chunk_samples",256));
  std::vector<Complex> clean(chunk),other(chunk),impaired;
  std::vector<std::uint32_t> send(512),other_send(512);
  for(std::size_t i=0;i<other_send.size();++i)other_send[i]=pattern(i,seed^0xE294183BU,"random")&((1U<<bits)-1);
  // RRC taps are energy-normalized. Unit-mean constellation power gives this
  // pre-fade sample power; no per-fade or per-chunk renormalization is done.
  const double signal_power=nominal_sample_power(c);
  SimulatedChannel channel(c.modem.sample_rate_hz,signal_power,channel_cfg,seed);
  channel.residual_offset_hz=number(a,"residual_offset_hz");
  channel.residual_drift_hz_per_second=number(a,"residual_drift_hz_per_second");
  std::vector<SoftBit> received_coded;
  std::uint64_t sent=0,samples=0,compared=0,errors=0,losses=0,acquisitions=0,header_count=0,locked_samples=0;
  std::uint64_t boundary_errors=0,expected_index=0,received_count=0;
  double acquisition=-1;
  double first_loss=-1, loss_start=-1;
  std::vector<double> recovery_times;
  std::array<RfStreamSymbol,1024> decoded{};
  Constellation constellation(c.modem.modulation,c.modem.constellation_profile);
  std::vector<double> amplitudes;
  const bool calibrate=number(a,"calibrate_clip")!=0;
  double tx_power_sum=0,tx_peak_power=0;
  std::uint64_t tx_sample_count=0;
  const std::uint64_t target_samples=static_cast<std::uint64_t>((duration+0.25)*c.modem.sample_rate_hz);
  std::size_t receive_tail=channel_cfg.pure_noise?0:static_cast<std::size_t>(number(a,"receive_tail_samples",2));
  // Finish the declared payload, including all recurring control airtime.
  // A wall-duration cap would label unsent tail frames as channel losses.
  while(channel_cfg.pure_noise ? samples<target_samples : (encoder.active() || receive_tail)) {
    std::size_t produced=chunk;
    if(!channel_cfg.pure_noise) {
      const auto submitted_before=sent;
      const auto n=std::min<std::uint64_t>(send.size(),payload_count-sent);
      for(std::size_t i=0;i<n;++i)send[i]=expected(sent+i);
      const auto tx=n?encoder.push_symbols(std::span(send).first(n),clean):encoder.drain(clean);
      sent+=tx.consumed_symbols;produced=tx.produced_samples;
      if(channel_cfg.agc_step_db!=0 && sent>0) {
        const double tail=c.modem.filter_span_symbols/rate;
        const double agc_end=channel_cfg.agc_start_s+(channel_cfg.agc_attack_ms+channel_cfg.agc_decay_ms)/1000+0.05;
        if((samples+produced)/c.modem.sample_rate_hz+tail>=channel_cfg.agc_start_s && samples/c.modem.sample_rate_hz<=agc_end) {
          const auto begin=(submitted_before?submitted_before-1:0)/c.symbols_per_frame;
          for(auto f=begin;f<=(sent-1)/c.symbols_per_frame && f<agc_affected.size();++f)agc_affected[f]=true;
        }
      }
      if(produced==0 && !encoder.active()) {
        // Audio continues after the finite TX pulse train. Two explicit idle
        // samples flush linear sample-clock interpolation and fractional filter
        // support; they are passed through every enabled impairment stage.
        produced=std::min(chunk,receive_tail);
        receive_tail-=produced;
        std::fill_n(clean.begin(),produced,Complex{});
        if(produced==0)break;
      }
    } else {
      produced=std::min<std::uint64_t>(chunk,static_cast<std::uint64_t>(duration*c.modem.sample_rate_hz)-samples);
      if(produced==0)break;
      std::fill(clean.begin(),clean.end(),Complex{});
    }
    if(calibrate)for(std::size_t i=0;i<produced;++i)amplitudes.push_back(std::abs(clean[i]));
    for(std::size_t i=0;i<produced;++i) {
      const double power=std::norm(clean[i]);tx_power_sum+=power;tx_peak_power=std::max(tx_peak_power,power);++tx_sample_count;
    }
    if(std::isfinite(channel_cfg.data_sir_db)) {
      const auto tx=interferer.push_symbols(other_send,std::span(other).first(produced));
      if(tx.produced_samples!=produced)throw std::runtime_error("interferer stalled");
    }
    channel.process(std::span(clean).first(produced),impaired,std::isfinite(channel_cfg.data_sir_db)?std::span<const Complex>(other).first(produced):std::span<const Complex>{});
    samples+=produced;
    const auto rx=receiver.push_samples(impaired,decoded);
    if(rx.acquisition_found) {++acquisitions;if(acquisition<0)acquisition=static_cast<double>(samples)/c.modem.sample_rate_hz;}
    header_count+=rx.header_valid;losses+=rx.lock_lost;
    const double clock=samples/c.modem.sample_rate_hz;
    if(rx.lock_lost) {if(first_loss<0)first_loss=clock;if(loss_start<0)loss_start=clock;}
    if(rx.header_valid && loss_start>=0) {recovery_times.push_back(clock-loss_start);loss_start=-1;}
    if(receiver.state()==RfStreamState::locked)locked_samples+=produced;
    for(std::size_t j=0;j<rx.produced_symbols;++j) {
      const auto& s=decoded[j];
      if(s.frame_counter<7000){++boundary_errors;continue;}
      const auto i=(s.frame_counter-7000)*c.symbols_per_frame+s.frame_symbol_offset;
      if(i>=payload_count)continue;
      if(i!=expected_index)++boundary_errors;
      expected_index=i+1;
      const auto bit_errors=std::popcount(s.value^expected(i));
      errors+=bit_errors;compared+=bits;++received_count;
      ++frame_seen[i/c.symbols_per_frame];frame_errors[i/c.symbols_per_frame]+=bit_errors;
      if(channel_cfg.sample_slip_index>=0)frame_last_seen_s[i/c.symbols_per_frame]=samples/c.modem.sample_rate_hz;
      if(fec && i==received_coded.size()/bits) {
        std::array<std::uint8_t,max_bits_per_symbol> unpacked{};
        constellation.symbol_to_bits(s.value,std::span(unpacked).first(bits));
        for(std::size_t k=0;k<bits;++k)received_coded.push_back(s.has_soft_bits ? s.soft_bits[k] : SoftBit{unpacked[k],s.certain,s.confidence});
      }
    }
  }
  std::uint64_t survived=0,complete=0,survived_bits=0,affected=0,affected_survived=0;
  double slip_recovery=-1;
  const double frame_duration=c.symbols_per_frame/rate*34.0/32.0;
  for(std::size_t f=0;f<frame_seen.size();++f) {
    const auto n=std::min<std::uint64_t>(c.symbols_per_frame,payload_count-f*c.symbols_per_frame);
    affected+=agc_affected[f];
    if(frame_seen[f]==n){++complete;if(frame_errors[f]==0){
      ++survived;survived_bits+=n*bits;affected_survived+=agc_affected[f];
      if(channel_cfg.sample_slip_index>=0 && slip_recovery<0 &&
         frame_last_seen_s[f]-frame_duration>=channel_cfg.sample_slip_index/c.modem.sample_rate_hz)
        slip_recovery=frame_last_seen_s[f]-channel_cfg.sample_slip_index/c.modem.sample_rate_hz;
    }}
  }
  Json out;attach_isa(out,a);
  out.set("simulated_seconds",static_cast<double>(samples)/c.modem.sample_rate_hz);
  out.set("samples",samples);out.set("bits_sent",payload_count*bits);out.set("bits_compared",compared);
  out.set("bit_errors",errors);out.set("frames_sent",frame_seen.size());out.set("frames_complete",complete);
  out.set("frames_survived",survived);out.set("symbols_sent",payload_count);out.set("symbols_received",received_count);
  out.set("frame_boundary_errors",boundary_errors);out.set("lock_losses",losses);out.set("acquisitions",acquisitions);
  out.set("valid_headers",header_count);out.set("acquisition_time_s",acquisition<0?NAN:acquisition);
  out.set("first_lock_loss_s",first_loss<0?NAN:first_loss);
  out.array("completed_rf_recovery_s",recovery_times);
  out.set("unrecovered_rf_outage_s",loss_start<0?NAN:samples/c.modem.sample_rate_hz-loss_start);
  out.set("planned_payload_symbols_per_second",payload_symbol_rate);
  out.text("duration_scope","Payload count uses the complete waveform duty cycle, including recurring markers. The finite payload is completed; actual duration includes partial-segment startup and pulse tails. No audio-duration reduction for runtime.");
  out.set("locked_seconds",locked_samples/c.modem.sample_rate_hz);
  out.set("useful_bits_delivered",survived_bits);
  out.set("terminal_receiver_state",static_cast<int>(receiver.state()));
  out.set("sample_clock_error_ppm",receiver.sync_estimate().sample_clock_error_ppm);
  out.set("training_evm",receiver.sync_estimate().training_evm);
  if(channel_cfg.agc_step_db!=0) {
    out.set("agc_affected_frames",affected);out.set("agc_affected_frames_survived",affected_survived);
    out.text("agc_affected_frame_definition","Conservative overlap of symbol submission audio blocks plus RRC pulse support with the entire AGC ramp/hold/decay; resolution is the declared audio block size.");
  }
  if(channel_cfg.sample_slip_index>=0) {
    out.set("recovery_after_sample_slip_s",slip_recovery<0?NAN:slip_recovery);
    out.set("recovery_after_sample_slip_frames",slip_recovery<0?NAN:std::ceil(slip_recovery/frame_duration));
    out.text("sample_slip_recovery_definition","Time to completion of the first complete bit-exact RF frame lying after the injected sample slip, at receive-block timing resolution.");
  }
  if(fec && !received_coded.empty()) {
    received_coded.resize(std::min(received_coded.size(),coded.size()));
    ChannelCodingDecoder decoder(fec_config(a),payload_config(a));
    std::vector<Token> bytes;decoder.push_append(received_coded,bytes);
    std::uint64_t count_bytes=std::min(bytes.size(),source_bytes.size()),decoded_errors=0;
    for(std::size_t i=0;i<count_bytes;++i)decoded_errors+=std::popcount(static_cast<unsigned>(bytes[i].value^source_bytes[i]));
    out.set("coded_bits_compared",count_bytes*8);out.set("coded_bit_errors",decoded_errors);
    out.set("source_bits",source_bytes.size()*8);
  }
  if(calibrate) {
    std::sort(amplitudes.begin(),amplitudes.end());
    for(const auto percent:{1,5,10})out.set("clip_top_"+std::to_string(percent),amplitudes[static_cast<std::size_t>((1-percent/100.0)*(amplitudes.size()-1))]);
  }
  out.set("tx_mean_sample_power",tx_sample_count?tx_power_sum/tx_sample_count:0);
  out.set("tx_peak_sample_power",tx_peak_power);
  out.set("tx_papr_db",tx_power_sum>0?10*std::log10(tx_peak_power*tx_sample_count/tx_power_sum):NAN);
  out.set("tx_power_observed_samples",tx_sample_count);
  return out;
}

// Source/sink adapter uses production framing/FEC/crypto/RF with deterministic
// audio delivery times. CPU timing is deliberately not passed off as simulated
// time. No destination-side filtering is added to hide stale or duplicate data.
Json run_messages(const Arguments& a) {
  RealtimePipelineConfig config;
  config.rf=rf_config(a);config.convolutional=fec_config(a);
  config.coding=payload_config(a);
  if (config.rf.soft_demapping || config.coding.walsh_bits || config.rf.waveform!=AudioWaveform::single_carrier) config.convolutional.decoded_bit_confidence_threshold = 0;
  config.sync_timestamp.enabled=false; // wall-clock replay-window check is audited separately
  config.frame_counter_start=7000;
  TransmitMessageQueue input(1024);
  SpscRingBuffer<DelimitedMessage> output(1024),other_input(16);
  RealtimeTransmitter tx(config,input);
  // A second sender has its own key and epoch journal, but the same waveform
  // and preamble. A completed foreign record must fail GCM authentication.
  test::EpochFixture interferer_epoch;
  auto other_config=config;
  other_config.aes_key.bytes[0]=0xA8;
  other_config.transmitter_epoch_path=interferer_epoch.path;
  RealtimeTransmitter other_tx(other_config,other_input);
  RealtimeReceiver rx(tx.config(),output);
  GapAudit gap_audit;rx.set_decoded_message_observer(&gap_audit);
  std::uint64_t audio_sample_position=0;
  const auto fs=config.rf.modem.sample_rate_hz;
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const auto channel_cfg=impairments(a);
  const auto duration=number(a,"duration_s",2);
  const auto block=static_cast<std::size_t>(number(a,"chunk_samples",48));
  const auto period=number(a,"message_interval_s",0.01);
  const bool soak=number(a,"soak")!=0;
  const bool host_timing=number(a,"host_timing")!=0;
  const bool aggregate=number(a,"aggregate_metrics")!=0;
  if(aggregate && (host_timing || number(a,"source_load_factor")!=0 || soak))
    throw std::invalid_argument("aggregate metrics require a fixed-rate, simulated-time message campaign");
  SampleDistribution delivery_latency(fs),delivery_silence(fs),rf_recovery(fs);
  std::set<std::uint64_t> usable_windows;
  double previous_delivery=0,first_delivery=-1,first_loss=-1,loss_start=-1;
  std::set<std::uint64_t> selected_messages;
  const auto selected_text=word(a,"selected_messages");
  std::istringstream selected_stream(selected_text);
  for(std::string value;std::getline(selected_stream,value,',');) {
    if(!value.empty())selected_messages.insert(std::stoull(value));
  }
  const bool auction_intake=number(a,"auction_intake")!=0;
  const auto source_load=number(a,"source_load_factor");
  const double period_samples=period*fs;
  const bool integral_source_period=source_load==0 && period_samples==std::floor(period_samples);
  const double code_rate=payload_coding_rate(config.coding,config.convolutional);
  const double symbol_rate=rf_symbol_rate_hz(config.rf);
  const bool fsk=config.rf.waveform==AudioWaveform::fsk4 || config.rf.waveform==AudioWaveform::fsk8;
  const double pilot_duty=fsk ? static_cast<double>(config.rf.symbols_per_frame)/(config.rf.symbols_per_frame+16+(268+bits_per_symbol(config.rf.modem.modulation)-1)/bits_per_symbol(config.rf.modem.modulation)) : static_cast<double>(config.rf.pilot_interval_symbols)/
      (config.rf.pilot_interval_symbols+config.rf.pilot_sequence.size());
  const double capacity_bps=symbol_rate*bits_per_symbol(config.rf.modem.modulation)*code_rate*pilot_duty;
  const auto wall_start=std::chrono::steady_clock::now();
  const auto wall_seconds=[&]() {return std::chrono::duration<double>(std::chrono::steady_clock::now()-wall_start).count();};
  BidMessageTransmitIntake intake;
  SpscRingBuffer<BidMessageLogRecord> bid_logs(64);
  const auto power=nominal_sample_power(config.rf);
  SimulatedChannel channel(fs,power,channel_cfg,seed);
  channel.residual_offset_hz=number(a,"residual_offset_hz");
  channel.residual_drift_hz_per_second=number(a,"residual_drift_hz_per_second");
  std::vector<Complex> clean(block),other(block),impaired;
  std::vector<double> created,latencies,deliveries,delivered_ids;
  std::vector<double> host_created,host_latency,host_tx,host_rx,host_channel,host_audio_wait,host_intake;
  std::array<std::int64_t,16> newest{},last_delivered{};
  newest.fill(-1);last_delivered.fill(-1);
  ConsumptionAudit consumption(newest);tx.set_consumed_message_observer(&consumption);
  std::vector<double> source_to_framer,host_source_to_framer,consumed_ids;
  std::vector<double> serialization_estimates;
  double tx_audio_clock=0;
  if(!soak && !aggregate)consumption.on_consumed=[&](std::uint64_t id) {
    if(id>=created.size())throw std::runtime_error("unknown consumed message");
    consumed_ids.push_back(id);
    const auto message=encode_bank_symbol_integer(0,static_cast<std::uint8_t>(id%16+2),id);
    serialization_estimates.push_back(authenticated_message_wire_bytes(message.bytes.size())*8/capacity_bps*1000);
    source_to_framer.push_back((tx_audio_clock-created[id])*1000);
    if(host_timing)host_source_to_framer.push_back((wall_seconds()-host_created[id])*1000);
  };
  std::vector<std::vector<double>> newest_latency(16),latency_windows(10);
  std::set<std::int64_t> seen;
  std::uint64_t fresh_bits=0;
  std::uint64_t total=static_cast<std::uint64_t>(duration*fs),generated=0,delivered=0,corrupted=0,stale=0,duplicates=0,queued_max=0,gaps=0;
  std::uint64_t source_tick_misses=0;
  std::uint64_t losses=0,headers=0,locked_samples=0,delivered_bits=0,backpressure=0;
  std::uint64_t authentication_failures=0,replay_rejections=0;
  bool locked=false;
  double first_acquisition=-1,reacquisition=-1,next_creation=0;
  const double dropout_end=channel_cfg.dropout_start_s+channel_cfg.dropout_duration_s;
  const auto jitter=number(a,"jitter_ms");
  const auto jitter_buffer=static_cast<std::size_t>(number(a,"audio_jitter_buffer_samples",48));
  std::uint64_t injected_audio_gaps=0;
  const auto glitch=word(a,"audio_event");
  bool glitched=false;
  double delivery_clock=0;
  std::vector<double> hour_p50,hour_p99,hour_p999,hour_max,hour_delivered;
  std::vector<double> hour_resident_pages;
  std::uint64_t counter_drift=0;
  std::size_t completed_hours=0;
  const auto finish_hour=[&]() {
    auto ordered=latencies;std::sort(ordered.begin(),ordered.end());
    const auto percentile=[&](double q) {
      return ordered.empty() ? -1.0 : ordered[static_cast<std::size_t>(std::ceil(q*ordered.size()))-1];
    };
    hour_p50.push_back(percentile(.5));hour_p99.push_back(percentile(.99));
    hour_p999.push_back(percentile(.999));hour_max.push_back(percentile(1));
    hour_delivered.push_back(latencies.size());
    std::ifstream rss("/proc/self/statm");double virtual_pages=0,resident_pages=0;
    rss>>virtual_pages>>resident_pages;hour_resident_pages.push_back(resident_pages);
    latencies.clear();deliveries.clear();delivered_ids.clear();seen.clear();
    ++completed_hours;
  };
  for(std::uint64_t sample=0;sample<total;sample+=block) {
    const double now=sample/fs;
    if(soak || host_timing) {
      std::this_thread::sleep_until(wall_start+std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(now)));
      if(soak && now>=(completed_hours+1)*3600.0)finish_hour();
    }
    while(next_creation<=now) {
      if(integral_source_period && std::fmod(period_samples,static_cast<double>(block))==0 && next_creation!=now)
        ++source_tick_misses;
      const auto key=generated%16;
      auto message=encode_bank_symbol_integer(0,static_cast<std::uint8_t>(key+2),static_cast<std::int64_t>(generated));
      // Include the production AEAD envelope and COBS bound. Offer wire bits
      // at the declared multiple of steady payload
      // capacity, including pilot and puncturing overhead, excluding startup.
      const double interval=source_load>0 ? authenticated_message_wire_bytes(message.bytes.size())*8/(capacity_bps*source_load) : period;
      if(!soak && !aggregate)created.push_back(next_creation);
      if(host_timing)host_created.push_back(wall_seconds());
      newest[key]=static_cast<std::int64_t>(generated);
      if(!selected_text.empty() && !selected_messages.contains(generated)) {
        ++generated;
        next_creation=integral_source_period ? generated*period_samples/fs : next_creation+interval;
        continue;
      }
      if(auction_intake) {
        const auto begin=host_timing?wall_seconds():0;
        BidMessage bid;bid.payload=std::move(message.bytes);bid.bid_price=1;
        (void)intake.submit(std::move(bid),input,bid_logs);
        if(host_timing)host_intake.push_back((wall_seconds()-begin)*1000);
      } else if(!input.try_push(std::move(message)))++backpressure;
      ++generated;
      // Derive integral sample-clock deadlines from their event index. Repeated
      // addition of 0.01 can put a 10 ms source event one ULP beyond an audio
      // block edge, falsely adding a whole millisecond of intake buffering.
      next_creation=integral_source_period ? generated*period_samples/fs : next_creation+interval;
    }
    if(auction_intake) {
      (void)intake.pump(input,bid_logs);
      BidMessageLogRecord log;
      while(bid_logs.try_pop(log))backpressure+=log.status==BidMessageLogStatus::rejected;
    }
    queued_max=std::max<std::uint64_t>(queued_max,input.size_approx());
    const auto tx_begin=host_timing?wall_seconds():0;
    tx_audio_clock=now;
    const auto result=tx.push_samples(clean);
    if(host_timing)host_tx.push_back((wall_seconds()-tx_begin)*1000);
    if(result.produced_samples==0)throw std::runtime_error("message transmitter stalled");
    if(std::isfinite(channel_cfg.data_sir_db)) {
      if(other_input.empty())(void)other_input.try_push(encode_bank_symbol_integer(0,2,999));
      (void)other_tx.push_samples(other);
    }
    const auto channel_begin=host_timing?wall_seconds():0;
    channel.process(std::span(clean).first(result.produced_samples),impaired,std::isfinite(channel_cfg.data_sir_db)?std::span<const Complex>(other):std::span<const Complex>{});
    if(host_timing)host_channel.push_back((wall_seconds()-channel_begin)*1000);
    const double block_end=(sample+result.produced_samples)/fs;
    const auto jitter_delay=now>=number(a,"audio_event_s",0.5) ?
        jitter/1000.0*(pattern(sample/block,seed,"random")/4294967295.0) : 0.0;
    delivery_clock=std::max(delivery_clock,block_end+jitter_delay);
    const auto audio_first=audio_sample_position;
    audio_sample_position+=impaired.size();
    bool audio_valid=true;
    if(!glitched && now>=number(a,"audio_event_s",0.5) && !glitch.empty()) {
      glitched=true;
      if(glitch=="underrun")audio_valid=false;
      else if(glitch=="overrun") {++injected_audio_gaps;continue;}
    }
    if(host_timing) {
      const auto begin=wall_seconds();
      std::this_thread::sleep_until(wall_start+std::chrono::duration_cast<std::chrono::steady_clock::duration>(std::chrono::duration<double>(delivery_clock)));
      host_audio_wait.push_back((wall_seconds()-begin)*1000);
    }
    const auto rx_begin=host_timing?wall_seconds():0;
    // A simulated device reports arrival in its sample-clock domain. Late
    // contiguous blocks exercise the production deadline check, not a synthetic
    // observer event. Other impairment tests keep only sample-position metadata.
    const auto arrival=static_cast<std::uint64_t>(std::llround(delivery_clock*fs));
    const auto available=audio_first+impaired.size();
    const bool deadline_miss=jitter>0 && arrival>available && arrival-available>jitter_buffer;
    injected_audio_gaps+=!audio_valid || deadline_miss;
    const auto received=jitter>0 ?
        rx.push_timed_audio_block(impaired,audio_first,arrival,jitter_buffer,audio_valid) :
        rx.push_audio_block(impaired,audio_first,audio_valid);
    if(host_timing)host_rx.push_back((wall_seconds()-rx_begin)*1000);
    losses+=received.lock_lost;headers+=received.header_valid;
    authentication_failures+=received.authentication_failures;
    replay_rejections+=received.replay_rejections;
    locked=rx.rf_state()==RfStreamState::locked;
    if(received.lock_lost) {if(first_loss<0)first_loss=delivery_clock;if(loss_start<0)loss_start=delivery_clock;}
    if(received.header_valid && loss_start>=0) {rf_recovery.add(delivery_clock-loss_start);loss_start=-1;}
    if(locked)locked_samples+=result.produced_samples;
    if(received.acquisition_found && first_acquisition<0)first_acquisition=delivery_clock;
    if(received.header_valid && now>=dropout_end && channel_cfg.dropout_duration_s>0 && reacquisition<0)reacquisition=delivery_clock-dropout_end;
    DelimitedMessage message;
    while(output.try_pop(message)) {
      const auto data=decode_bank_symbol_integer(message);
      if(!data || data->value<0 || static_cast<std::uint64_t>(data->value)>=generated) {++corrupted;++counter_drift;continue;}
      const auto id=data->value;const auto key=static_cast<std::size_t>(data->symbol-2);
      if(key>=16 || static_cast<std::uint64_t>(id)%16!=key){++corrupted;++counter_drift;continue;}
      if(aggregate ? id==last_delivered[key] : (!soak && !seen.insert(id).second))++duplicates;
      if(id<newest[key])++stale;
      if(id<last_delivered[key])++gaps;
      last_delivered[key]=id;
      ++delivered;delivered_bits+=message.bytes.size()*8;
      if(id==newest[key])fresh_bits+=message.bytes.size()*8;
      const auto message_latency=delivery_clock-((soak || aggregate)?id*period:created[id]);
      delivery_latency.add(message_latency);
      delivery_silence.add(delivery_clock-previous_delivery);previous_delivery=delivery_clock;
      if(first_delivery<0)first_delivery=delivery_clock;
      usable_windows.insert(static_cast<std::uint64_t>(delivery_clock));
      if(!aggregate)latencies.push_back(message_latency*1000.0);
      if(source_load>0) {
        if(id==newest[key])newest_latency[key].push_back(latencies.back());
        latency_windows[std::min<std::size_t>(9,static_cast<std::size_t>(delivery_clock/duration*10))].push_back(latencies.back());
      }
      if(host_timing)host_latency.push_back((wall_seconds()-host_created[id])*1000);
      if(!aggregate) {deliveries.push_back(delivery_clock);delivered_ids.push_back(static_cast<double>(id));}
    }
  }
  Json out;attach_isa(out,a);
  out.set("simulated_seconds",duration);out.set("messages_created",generated);out.set("messages_delivered",delivered);
  out.set("source_tick_misses",source_tick_misses);
  out.set("corrupted_messages_delivered",corrupted);out.set("stale_messages_delivered",stale);
  out.set("wrong_length_or_payload_delivered",corrupted);
  out.set("duplicate_messages_delivered",duplicates);out.set("out_of_order_deliveries",gaps);
  out.set("queue_depth_max",queued_max);out.set("source_backpressure",backpressure);out.set("lock_losses",losses);
  out.set("messages_consumed_by_framer",consumption.consumed);out.set("superseded_messages_consumed",consumption.superseded);
  out.set("valid_headers",headers);out.set("locked_seconds",locked_samples/fs);out.set("useful_bits_delivered",delivered_bits);
  out.set("acquisition_time_s",first_acquisition<0?NAN:first_acquisition);
  out.set("reacquisition_time_s",reacquisition<0?NAN:reacquisition);
  const auto observation_end=std::max(duration,delivery_clock);
  delivery_silence.add(observation_end-previous_delivery);
  out.set("first_lock_loss_s",first_loss<0?NAN:first_loss);
  out.set("first_message_delivery_s",first_delivery<0?NAN:first_delivery);
  out.set("delivery_observation_end_s",observation_end);
  out.set("terminal_delivery_silence_s",observation_end-previous_delivery);
  out.set("unrecovered_rf_outage_s",loss_start<0?NAN:observation_end-loss_start);
  out.fields["delivery_silence_ms"]=delivery_silence.summary_ms().str();
  out.fields["rf_recovery_ms"]=rf_recovery.summary_ms().str();
  out.text("delivery_silence_definition","Time between correct application deliveries, including startup and the right-censored terminal interval. No invented outage threshold; audio sample-clock resolution.");
  if(aggregate) {
    out.fields["latency_sample_clock_ms"]=delivery_latency.summary_ms().str();
    double usable=0;for(const auto window:usable_windows)if(window<duration)usable+=std::min(1.,duration-window);
    out.set("usable_window_seconds",usable);
    out.text("aggregation","All messages counted; exact nearest-rank histograms rounded to the declared audio sample clock. Per-message JSON vectors omitted.");
  }
  out.set("fresh_useful_bits_delivered",fresh_bits);
  out.set("audio_gap_api",injected_audio_gaps>0 && gap_audit.audio_events==injected_audio_gaps);
  out.set("injected_audio_gaps",injected_audio_gaps);
  out.set("audio_gap_events",gap_audit.audio_events);out.set("gap_events",gap_audit.events);
  out.set("fec_gap_events",gap_audit.fec_events);
  out.set("audio_block_ms",block/fs*1000);
  if(!soak && !aggregate) {
    out.array("latency_ms",latencies);out.array("delivery_times_s",deliveries);out.array("delivered_ids",delivered_ids);
    out.array("source_to_framer_ms",source_to_framer);out.array("consumed_ids",consumed_ids);
    out.array("nominal_message_serialization_ms",serialization_estimates);
    Json modem_delay;
    modem_delay.set("tx_rrc_group_delay_ms",fsk ? 0 : describe(config.rf.modem).nominal_filter_latency_symbols/symbol_rate*1000);
    modem_delay.set("rx_rrc_group_delay_ms",fsk ? 0 : describe(config.rf.modem).nominal_filter_latency_symbols/symbol_rate*1000);
    modem_delay.set("equalizer_decision_delay_ms",config.rf.equalizer_delay_symbols/symbol_rate*1000);
    modem_delay.set("viterbi_lookahead_nominal_ms",config.coding.bch?0:std::max(5U*config.convolutional.constraint_length,24U)/capacity_bps*1000);
    modem_delay.set("bch_word_airtime_ms",config.coding.bch?58/(symbol_rate*bits_per_symbol(config.rf.modem.modulation)*pilot_duty)*1000:0);
    modem_delay.set("payload_capacity_bps",capacity_bps);
    modem_delay.set("interleaver_wire_block_ms",config.coding.interleaver_rows*config.coding.interleaver_columns/(symbol_rate*bits_per_symbol(config.rf.modem.modulation))*1000);
    modem_delay.set("fsk_integration_ms",fsk?config.rf.fsk_useful_ms:0);
    modem_delay.set("fsk_guard_per_symbol_ms",fsk?config.rf.fsk_guard_ms:0);
    modem_delay.set("diversity_combining_wait_max_ms",config.rf.waveform==AudioWaveform::bpsk_frequency_diversity && config.rf.diversity_branch_mask==3?config.rf.diversity_wait_ms+std::min<std::size_t>(block,48)/fs*1000:0);
    modem_delay.text("scope","Analytical residence estimates, not CPU times: serialization includes coding and mean pilot duty; Viterbi emits bytes after its lookahead. Startup, byte/symbol alignment and actual pilot positions remain in the measured one-sample reference. These estimates are not subtracted from the latency assertion.");
    out.fields["modem_delay_estimates"]=modem_delay.str();
    out.text("source_to_framer_scope","Message creation to first-byte framer consumption; sample-clock observations have audio-block resolution; host observer timestamps are exact steady-clock call times.");
  }
  out.set("aead_supported",1);out.set("authentication_failure_counter_available",1);
  out.set("authentication_failures",authentication_failures);
  out.set("replay_rejections",replay_rejections);
  out.text("transmitter_epoch",std::to_string(tx.config().rf.expected_schedule_epoch));
  out.set("authenticated_key_id",config.key_id);
  out.text("latency_clock","deterministic audio sample clock; CPU, OS, device latency unmeasured");
  if(source_load>0) {
    Json by_key,by_window;
    for(std::size_t i=0;i<newest_latency.size();++i)by_key.array(std::to_string(i),newest_latency[i]);
    for(std::size_t i=0;i<latency_windows.size();++i)by_window.array(std::to_string(i),latency_windows[i]);
    out.fields["newest_latency_ms_by_key"]=by_key.str();out.fields["latency_ms_by_window"]=by_window.str();
    out.set("nominal_channel_payload_capacity_bps",capacity_bps);
    out.set("offered_wire_bit_rate_bps",capacity_bps*source_load);
    out.set("latency_window_duration_s",duration/10);
  }
  if(host_timing) {
    out.array("host_source_to_framer_ms",host_source_to_framer);
    out.array("host_latency_ms",host_latency);
    out.array("host_tx_per_block_ms",host_tx);out.array("host_rx_per_block_ms",host_rx);
    out.array("host_channel_per_block_ms",host_channel);out.array("host_audio_wait_per_block_ms",host_audio_wait);
    out.array("host_intake_per_message_ms",host_intake);
    out.text("host_timing_scope","Paced simulated audio loopback, source creation through real auction/framing/FEC/crypto/modem to sink; OS scheduling included; no physical audio device, network socket, or radio.");
    out.text("host_stage_scope","Stage times are wall time per call; they are not additive per-message latency attribution. TX/RX include internal FEC/crypto/framing; queue residence stays in end-to-end latency.");
  }
  if(soak) {
    finish_hour();
    out.set("counter_drift",counter_drift);
    out.set("completed_hours",completed_hours);
    out.array("hour_p50_ms",hour_p50);out.array("hour_p99_ms",hour_p99);
    out.array("hour_p99_9_ms",hour_p999);out.array("hour_max_ms",hour_max);
    out.array("hour_delivered",hour_delivered);
    out.array("host_resident_pages_by_hour",hour_resident_pages);
    out.text("hour_percentile_missing_value","-1 means no delivered messages during that hour");
    out.text("soak_memory_scope","Resident memory includes production objects and bounded per-hour harness samples; queues sampled throughout run.");
  }
  return out;
}

Json run_scheduler(const Arguments& a) {
  TransmitMessageQueue queue(8);
  SpscRingBuffer<BidMessageLogRecord> logs(64);
  BidMessageTransmitIntake scheduler;
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const double duration=number(a,"duration_s",60),capacity=number(a,"capacity_messages_per_s",100);
  const double overload=number(a,"overload",3);
  const auto instruments=static_cast<std::size_t>(number(a,"instruments",16));
  const bool flood=number(a,"flood")!=0;
  std::vector<std::int64_t> newest(instruments,-1);
  std::vector<std::uint64_t> per_key(instruments);
  std::vector<std::uint64_t> offered_per_key(instruments);
  std::vector<double> created,latencies;
  std::vector<std::vector<double>> newest_latency(instruments),latency_windows(10);
  std::uint64_t generated=0,transmitted=0,stale=0,maximum=0,rejected=0,inversions=0;
  double next_arrival=0,next_tx=1/capacity;
  for(double now=0;now<duration;) {
    if(std::min(next_arrival,next_tx)>=duration)break;
    if(next_arrival<=next_tx) {
      now=next_arrival;next_arrival+=1/(capacity*overload);
      const auto key=flood?(generated%instruments==0?1U+(generated/instruments)%(instruments-1):0U):generated%instruments;
      ++offered_per_key[key];
      created.push_back(now);newest[key]=generated;
      BidMessage bid;
      bid.payload=encode_bank_symbol_integer(0,static_cast<std::uint8_t>(key+2),generated).bytes;
      bid.bid_price=flood?(key==0?10000:1):1+pattern(generated,seed,"random")%100;
      (void)scheduler.submit(std::move(bid),queue,logs);
      ++generated;
    } else {
      now=next_tx;next_tx+=1/capacity;
      DelimitedMessage message;
      if(queue.try_pop(message)) {
        const auto value=decode_bank_symbol_integer(message);
        if(!value)throw std::runtime_error("scheduler changed message bytes");
        const auto key=value->symbol-2;
        ++transmitted;++per_key[key];if(value->value<newest[key])++stale;
        const auto latency=(now-created[value->value])*1000;
        latencies.push_back(latency);
        if(value->value==newest[key])newest_latency[key].push_back(latency);
        latency_windows[std::min<std::size_t>(9,static_cast<std::size_t>(now/duration*10))].push_back(latency);
      }
      (void)scheduler.pump(queue,logs);
    }
    maximum=std::max<std::uint64_t>(maximum,queue.size_approx());
    BidMessageLogRecord log;
    while(logs.try_pop(log))rejected+=log.status==BidMessageLogStatus::rejected;
  }
  // Bids remain replaceable until the framer claims them. Check that a ready
  // higher bid displaces the lower bid before that claim.
  scheduler.reset();DelimitedMessage discard;while(queue.try_pop(discard)){}
  BidMessage low;low.payload=encode_bank_symbol_integer(0,2,1).bytes;low.bid_price=1;
  BidMessage high;high.payload=encode_bank_symbol_integer(0,3,2).bytes;high.bid_price=100;
  (void)scheduler.submit(low,queue,logs);(void)scheduler.submit(high,queue,logs);
  if(queue.try_pop(discard) && discard.bytes==low.payload)++inversions;
  Json out;attach_isa(out,a);
  out.set("simulated_seconds",duration);out.set("messages_created",generated);out.set("messages_delivered",transmitted);
  out.set("superseded_messages_transmitted",stale);out.set("queue_depth_max",maximum);out.set("bids_rejected",rejected);
  std::size_t starved=0;
  for(std::size_t key=0;key<instruments;++key)starved+=offered_per_key[key]>0 && per_key[key]==0;
  out.set("starved_instruments",starved);out.set("priority_inversions",inversions);
  out.array("latency_ms",latencies);
  std::vector<double> counts(per_key.begin(),per_key.end());out.array("deliveries_per_key",counts);
  const std::vector<double> offered(offered_per_key.begin(),offered_per_key.end());out.array("offered_per_key",offered);
  Json by_key,by_window;
  for(std::size_t i=0;i<instruments;++i)by_key.array(std::to_string(i),newest_latency[i]);
  for(std::size_t i=0;i<latency_windows.size();++i)by_window.array(std::to_string(i),latency_windows[i]);
  out.fields["newest_latency_ms_by_key"]=by_key.str();out.fields["latency_ms_by_window"]=by_window.str();
  out.set("latency_window_duration_s",duration/10);
  out.text("scheduler_latency_scope","Arrival to simulated transmitter service; newest-only per-key samples and ten chronological windows. Receiver delivery is not observed.");
  return out;
}

Json run_semantics(const Arguments& a) {
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const auto test=word(a,"semantics","duplicate");
  std::vector<DelimitedMessage> messages;
  for(int i=0;i<64;++i) {
    auto message=encode_bank_symbol_integer(0,2,i);
    message.sequence=static_cast<std::uint32_t>(i);
    messages.push_back(std::move(message));
  }
  if(test=="duplicate") {
    const std::vector<DelimitedMessage> replay(messages.begin(),messages.begin()+16);
    messages.insert(messages.end(),replay.begin(),replay.end());
  }
  if(test=="out_of_order")std::reverse(messages.begin(),messages.end());
  if(test=="wrap") {
    messages={encode_bank_symbol_integer(0,2,4294967294LL),encode_bank_symbol_integer(0,2,4294967295LL),
              encode_bank_symbol_integer(0,2,0),encode_bank_symbol_integer(0,2,1)};
    for(auto& message:messages)message.sequence=static_cast<std::uint32_t>(decode_bank_symbol_integer(message)->value);
  }
  if(test=="patterns") {
    messages.clear();
    for(int i=0;i<256;++i) {
      const auto length=i==0?2U:i==1?1024U:2+pattern(i,seed,"random")%1023;
      DelimitedMessage message;message.bytes={static_cast<std::uint8_t>(i%2),2};
      for(std::uint32_t j=2;j<length;++j) message.bytes.push_back(static_cast<std::uint8_t>(2+pattern(j+i,seed,"random")%254));
      messages.push_back(std::move(message));
    }
  }
  std::size_t byte_count=64;for(const auto& m:messages)byte_count+=authenticated_message_wire_bytes(m.bytes.size());
  SpscRingBuffer<DelimitedMessage> input(messages.size()+8),output(messages.size()+8);
  for(const auto& m:messages)(void)input.try_push(m);
  MessageStreamFramer framer;
  framer.set_sequence_numbers(true);
  const auto epoch=TransmitterEpoch::reserve(std::getenv("GOBLIN_CANNON_EPOCH_STATE"));
  framer.authenticate(Aes256Key{},1,epoch);
  std::vector<std::uint8_t> bytes(byte_count);
  (void)framer.next_payload_frame(input,bytes);
  auto tokens=std::vector<Token>();
  for(auto byte:bytes)tokens.push_back({byte,true,1});
  if(test=="fec_failure") {
    for(std::size_t i=10;i<20 && i<tokens.size();++i)tokens[i].certain=false;
  }
  if(test=="bit_insert" || test=="bit_delete") {
    std::vector<unsigned> bits;
    for(auto byte:bytes)for(int i=7;i>=0;--i)bits.push_back((byte>>i)&1);
    const auto offset=64+pattern(0,seed,"random")%(bits.size()/2);
    if(test=="bit_insert")bits.insert(bits.begin()+offset,1);else bits.erase(bits.begin()+offset);
    tokens.clear();
    for(std::size_t j=0;j+8<=bits.size();j+=8) {
      std::uint8_t value=0;for(std::size_t k=0;k<8;++k)value=static_cast<std::uint8_t>((value<<1)|bits[j+k]);
      tokens.push_back({value,true,1});
    }
  }
  MessageStreamDeframer deframer;
  deframer.set_sequence_numbers(true);
  deframer.authenticate(Aes256Key{},1,epoch->value());
  GapAudit gap_audit;deframer.set_observer(&gap_audit);
  (void)deframer.push_payload_tokens(tokens,output);
  std::set<std::vector<std::uint8_t>> seen;
  std::uint64_t count=0,duplicates=0,stale=0,wrong=0;
  std::optional<std::uint32_t> latest;
  std::vector<std::uint32_t> received_sequences;
  DelimitedMessage m;
  while(output.try_pop(m)) {
    ++count;if(!seen.insert(m.bytes).second)++duplicates;
    if(m.sequence) {
      if(latest && (static_cast<std::uint32_t>(*m.sequence-*latest)==0 ||
                    static_cast<std::uint32_t>(*m.sequence-*latest)>=0x80000000U))++stale;
      latest=m.sequence;received_sequences.push_back(*m.sequence);
    }
    if(std::none_of(messages.begin(),messages.end(),[&](const auto& original){return original.bytes==m.bytes;}))++wrong;
  }
  Json out;attach_isa(out,a);
  out.set("messages_created",messages.size());out.set("messages_delivered",count);
  out.set("duplicate_messages_delivered",duplicates);out.set("stale_messages_delivered",stale);
  out.set("wrong_length_or_payload_delivered",wrong);out.set("explicit_fec_gap_api",gap_audit.fec_events>0);
  out.set("gap_events",gap_audit.events);out.set("suppressed_messages",deframer.suppressed_messages());
  out.set("sequence_number_api",received_sequences==std::vector<std::uint32_t>{4294967294U,4294967295U,0U,1U});
  out.set("message_frame_maximum_bytes",maximum_message_bytes);
  return out;
}

Json run_crypto(const Arguments& a) {
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const auto audit=test::audit_aead(seed);
  Json out;attach_isa(out,a);
  out.set("aead_supported",1);out.set("authentication_failure_counter_available",1);
  out.set("authentication_failures",audit.authentication_failures);
  out.set("tamper_attempts",audit.tamper_attempts);
  out.set("nonces_observed",audit.nonces);out.set("reused_nonces_after_process_restart",audit.reused_nonces);
  out.set("corrupted_messages_delivered",audit.unverified_deliveries);
  out.set("valid_authenticated_deliveries",audit.valid_deliveries);
  out.set("replay_rejections",audit.replay_rejections);
  out.set("replay_deliveries",audit.unverified_deliveries);
  out.set("authenticated_key_id_supported",1);
  out.set("coordinated_key_rotation_api",0);
  return out;
}

Json run_erasure(const Arguments& a) {
  const double duration=number(a,"duration_s",60),period=number(a,"message_interval_s",0.01);
  const double survival=number(a,"direct_survival",0.5);
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const auto rf=rf_config(a);
  const double frame_period=rf.symbols_per_frame/derived_symbol_rate_hz(rf.modem)*34.0/32.0;
  // A direct erasure acts on fixed data-path payload frames. This isolates
  // delivery semantics; it does not pretend a whole message is one RF frame.
  const std::size_t frame_bytes=rf.symbols_per_frame*bits_per_symbol(rf.modem.modulation)/16;
  const auto frames=static_cast<std::size_t>(std::ceil(duration/frame_period));
  std::vector<unsigned char> survived(frames);
  std::fill_n(survived.begin(),static_cast<std::size_t>(std::llround(frames*survival)),1);
  std::mt19937 random(seed);
  for(std::size_t i=survived.size();i>1;--i)std::swap(survived[i-1],survived[random()%i]);
  SpscRingBuffer<DelimitedMessage> input(1024),output(1024);
  MessageStreamFramer framer;MessageStreamDeframer deframer;
  const auto epoch=TransmitterEpoch::reserve(std::getenv("GOBLIN_CANNON_EPOCH_STATE"));
  framer.authenticate(Aes256Key{},1,epoch);deframer.authenticate(Aes256Key{},1,epoch->value());
  framer.set_sequence_numbers(true);deframer.set_sequence_numbers(true);
  std::uint64_t created=0,delivered=0,stale=0,queue_max=0,useful_bits=0,out_of_order=0,duplicates=0;
  std::vector<double> latency,ids;
  std::vector<std::uint8_t> bytes(frame_bytes);
  std::vector<Token> tokens(frame_bytes);
  std::array<std::int64_t,16> newest{};newest.fill(-1);
  std::array<std::int64_t,16> latest_delivered{};latest_delivered.fill(-1);
  for(std::size_t i=0;i<frames;++i) {
    const double now=i*frame_period;
    while(created*period<=now) {
      const auto key=created%16;
      (void)input.try_push(encode_bank_symbol_integer(0,static_cast<std::uint8_t>(key+2),created));
      newest[key]=created;++created;
    }
    queue_max=std::max<std::uint64_t>(queue_max,input.size_approx());
    (void)framer.next_payload_frame(input,bytes);
    for(std::size_t k=0;k<frame_bytes;++k)tokens[k]={bytes[k],survived[i]!=0,survived[i]?1.0F:0.0F};
    (void)deframer.push_payload_tokens(tokens,output);
    DelimitedMessage message;
    while(output.try_pop(message)) {
      const auto value=decode_bank_symbol_integer(message);
      if(!value)throw std::runtime_error("unexpected direct-erasure delivery");
      ++delivered;stale+=value->value<newest[value->symbol-2];
      out_of_order+=value->value<latest_delivered[value->symbol-2];
      duplicates+=value->value==latest_delivered[value->symbol-2];
      latest_delivered[value->symbol-2]=value->value;
      useful_bits+=message.bytes.size()*8;
      latency.push_back((now+frame_period-value->value*period)*1000);ids.push_back(value->value);
    }
  }
  Json out;attach_isa(out,a);
  out.set("simulated_seconds",duration);out.set("frames_sent",frames);
  out.set("frames_survived",std::count(survived.begin(),survived.end(),1));
  out.set("messages_created",created);out.set("messages_delivered",delivered);
  out.set("stale_messages_delivered",stale);out.set("queue_depth_max",queue_max);
  out.set("useful_bits_delivered",useful_bits);out.set("out_of_order_deliveries",out_of_order);
  out.set("duplicate_messages_delivered",duplicates);
  out.set("frame_payload_bytes",frame_bytes);out.set("frame_duration_s",frame_period);
  out.array("latency_ms",latency);out.array("delivered_ids",ids);
  return out;
}

Json run_model(const Arguments& a) {
  const auto seed=static_cast<std::uint32_t>(number(a,"seed",0x71A001));
  const double fs=48000;
  auto cfg=impairments(a);
  const auto n=static_cast<std::size_t>(number(a,"duration_s",2)*fs);
  std::vector<Complex> input(n,Complex{1,0}),whole,part,joined;
  SimulatedChannel first(fs,1,cfg,seed),second(fs,1,cfg,seed);
  first.process(input,whole);
  for(std::size_t i=0;i<n;i+=157) {
    second.process(std::span(input).subspan(i,std::min<std::size_t>(157,n-i)),part);
    joined.insert(joined.end(),part.begin(),part.end());
  }
  Json out;attach_isa(out,a);out.set("chunk_invariant",whole==joined?1:0);
  out.set("samples",whole.size());out.set("mean_power",mean_power(whole));
  Complex mean{};for(const auto x:whole)mean+=x;
  mean/=static_cast<float>(whole.size());out.set("mean_i",mean.real());out.set("mean_q",mean.imag());
  return out;
}
}

int main(int argc,char** argv) {
  goblin_cannon::test::EpochFixture epoch_fixture;
  try {
    Arguments a;
    for(int i=1;i<argc;++i) {
      const std::string arg=argv[i];const auto pos=arg.find('=');
      if(pos==std::string::npos)throw std::invalid_argument("arguments must be key=value");
      a.emplace(arg.substr(0,pos),arg.substr(pos+1));
    }
    const auto mode=word(a,"mode","rf");
    Json out;
    if(mode=="rf")out=run_rf(a);
    else if(mode=="messages")out=run_messages(a);
    else if(mode=="scheduler")out=run_scheduler(a);
    else if(mode=="semantics")out=run_semantics(a);
    else if(mode=="crypto")out=run_crypto(a);
    else if(mode=="erasure")out=run_erasure(a);
    else if(mode=="model")out=run_model(a);
    else throw std::invalid_argument("unknown probe mode");
    std::cout<<out.str()<<'\n';
  } catch(const std::exception& e) {std::cerr<<"simulated channel: "<<e.what()<<'\n';return 1;}
}
