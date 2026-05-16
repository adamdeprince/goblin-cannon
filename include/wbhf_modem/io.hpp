#pragma once

#include <complex>
#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <functional>
#include <iosfwd>
#include <span>
#include <vector>

#include "wbhf_modem/modem.hpp"

namespace wbhf_modem {

enum class SampleFormat {
  fc32_iq,
  sc16_iq,
  f32_stereo_iq,
  s16_stereo_iq,
};

class IqSink {
public:
  virtual ~IqSink() = default;
  virtual std::size_t write(std::span<const Complex> samples) = 0;
  virtual void flush() = 0;
};

class IqSource {
public:
  virtual ~IqSource() = default;
  virtual std::size_t read(std::span<Complex> samples) = 0;
};

class CallbackIqSink final : public IqSink {
public:
  using WriteCallback = std::function<std::size_t(std::span<const Complex>)>;
  using FlushCallback = std::function<void()>;

  explicit CallbackIqSink(WriteCallback write, FlushCallback flush = {});

  std::size_t write(std::span<const Complex> samples) override;
  void flush() override;

private:
  WriteCallback write_;
  FlushCallback flush_;
};

class CallbackIqSource final : public IqSource {
public:
  using ReadCallback = std::function<std::size_t(std::span<Complex>)>;

  explicit CallbackIqSource(ReadCallback read);

  std::size_t read(std::span<Complex> samples) override;

private:
  ReadCallback read_;
};

class FileIqSink final : public IqSink {
public:
  FileIqSink(const std::filesystem::path& path,
             SampleFormat format = SampleFormat::sc16_iq,
             float scale = 0.95F,
             std::size_t pipe_capacity_bytes = 0);
  ~FileIqSink() override;

  FileIqSink(const FileIqSink&) = delete;
  FileIqSink& operator=(const FileIqSink&) = delete;

  std::size_t write(std::span<const Complex> samples) override;
  void flush() override;
  [[nodiscard]] std::size_t queued_bytes() const;

private:
  SampleFormat format_;
  float scale_;
  std::vector<std::uint8_t> buffer_;
  struct Impl;
  Impl* impl_;
};

class FileIqSource final : public IqSource {
public:
  FileIqSource(const std::filesystem::path& path,
               SampleFormat format = SampleFormat::sc16_iq,
               float scale = 0.95F,
               std::size_t pipe_capacity_bytes = 0);
  ~FileIqSource() override;

  FileIqSource(const FileIqSource&) = delete;
  FileIqSource& operator=(const FileIqSource&) = delete;

  std::size_t read(std::span<Complex> samples) override;
  [[nodiscard]] std::size_t readable_bytes() const;

private:
  SampleFormat format_;
  float inverse_scale_;
  std::vector<std::uint8_t> buffer_;
  std::size_t residual_bytes_ = 0;
  struct Impl;
  Impl* impl_;
};

std::size_t encoded_sample_size_bytes(SampleFormat format);
std::size_t encode_samples(std::span<const Complex> in,
                           SampleFormat format,
                           float scale,
                           std::span<std::uint8_t> out);
std::size_t decode_samples(std::span<const std::uint8_t> in,
                           SampleFormat format,
                           float inverse_scale,
                           std::span<Complex> out);

} // namespace wbhf_modem
