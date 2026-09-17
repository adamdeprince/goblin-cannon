#pragma once
#include "goblin_cannon/rf_stream.hpp"

namespace goblin_cannon::detail {
class AudioWaveformEncoder {
public:
  virtual ~AudioWaveformEncoder() = default;
  virtual const RfStreamConfig& config() const noexcept = 0;
  virtual bool active() const noexcept = 0;
  virtual RfStreamState state() const noexcept = 0;
  virtual RfStreamHeader current_header() const noexcept = 0;
  virtual void start_epoch(std::uint64_t) = 0;
  virtual RfStreamEncodeResult push_symbols(std::span<const std::uint32_t>, std::span<Complex>) = 0;
  virtual RfStreamEncodeResult drain(std::span<Complex>) = 0;
  virtual void reset() = 0;
};
class AudioWaveformReceiver {
public:
  virtual ~AudioWaveformReceiver() = default;
  virtual const RfStreamConfig& config() const noexcept = 0;
  virtual RfStreamState state() const noexcept = 0;
  virtual std::optional<RfStreamHeader> header() const noexcept = 0;
  virtual RfSyncEstimate sync_estimate() const noexcept = 0;
  virtual RfStreamReceiveResult push_samples(std::span<const Complex>, std::span<RfStreamSymbol>) = 0;
  virtual void reset() = 0;
};
void validate_audio_waveform(const RfStreamConfig& config);
std::unique_ptr<AudioWaveformEncoder> make_audio_encoder(RfStreamConfig config);
std::unique_ptr<AudioWaveformReceiver> make_audio_receiver(RfStreamConfig config);
} // namespace goblin_cannon::detail
