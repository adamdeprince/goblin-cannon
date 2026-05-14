#include "wbhf_modem/io.hpp"

#include <algorithm>
#include <bit>
#include <cstring>
#include <fstream>
#include <limits>
#include <stdexcept>

namespace wbhf_modem {

namespace {

std::int16_t clamp_s16(float value) {
  const auto scaled = std::clamp(value, -1.0F, 1.0F) * 32767.0F;
  return static_cast<std::int16_t>(scaled >= 0.0F ? scaled + 0.5F : scaled - 0.5F);
}

void put_le16(std::span<std::uint8_t> out, std::int16_t value) {
  const auto u = static_cast<std::uint16_t>(value);
  out[0] = static_cast<std::uint8_t>(u & 0xFFU);
  out[1] = static_cast<std::uint8_t>((u >> 8U) & 0xFFU);
}

std::int16_t get_le16(std::span<const std::uint8_t> in) {
  const auto u = static_cast<std::uint16_t>(in[0]) |
                 static_cast<std::uint16_t>(static_cast<std::uint16_t>(in[1]) << 8U);
  return static_cast<std::int16_t>(u);
}

void put_f32(std::span<std::uint8_t> out, float value) {
  static_assert(sizeof(float) == 4);
  std::memcpy(out.data(), &value, sizeof(float));
}

float get_f32(std::span<const std::uint8_t> in) {
  float value = 0.0F;
  std::memcpy(&value, in.data(), sizeof(float));
  return value;
}

} // namespace

struct FileIqSink::Impl {
  explicit Impl(const std::filesystem::path& path) : stream(path, std::ios::binary) {}
  std::ofstream stream;
};

struct FileIqSource::Impl {
  explicit Impl(const std::filesystem::path& path) : stream(path, std::ios::binary) {}
  std::ifstream stream;
};

CallbackIqSink::CallbackIqSink(WriteCallback write, FlushCallback flush)
    : write_(std::move(write)), flush_(std::move(flush)) {
  if (!write_) {
    throw std::invalid_argument("CallbackIqSink requires a write callback");
  }
}

std::size_t CallbackIqSink::write(std::span<const Complex> samples) {
  return write_(samples);
}

void CallbackIqSink::flush() {
  if (flush_) {
    flush_();
  }
}

CallbackIqSource::CallbackIqSource(ReadCallback read) : read_(std::move(read)) {
  if (!read_) {
    throw std::invalid_argument("CallbackIqSource requires a read callback");
  }
}

std::size_t CallbackIqSource::read(std::span<Complex> samples) {
  return read_(samples);
}

FileIqSink::FileIqSink(const std::filesystem::path& path, SampleFormat format, float scale)
    : format_(format), scale_(scale), impl_(nullptr) {
  if (scale_ <= 0.0F) {
    throw std::invalid_argument("scale must be positive");
  }
  impl_ = new Impl(path);
  if (!impl_->stream) {
    delete impl_;
    impl_ = nullptr;
    throw std::runtime_error("failed to open IQ sink: " + path.string());
  }
}

FileIqSink::~FileIqSink() {
  delete impl_;
}

std::size_t FileIqSink::write(std::span<const Complex> samples) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format_);
  buffer_.resize(samples.size() * bytes_per_sample);
  const auto bytes = encode_samples(samples, format_, scale_, buffer_);
  impl_->stream.write(reinterpret_cast<const char*>(buffer_.data()), static_cast<std::streamsize>(bytes));
  if (!impl_->stream) {
    throw std::runtime_error("failed to write IQ samples");
  }
  return samples.size();
}

void FileIqSink::flush() {
  impl_->stream.flush();
}

FileIqSource::FileIqSource(const std::filesystem::path& path, SampleFormat format, float scale)
    : format_(format), inverse_scale_(1.0F), impl_(nullptr) {
  if (scale <= 0.0F) {
    throw std::invalid_argument("scale must be positive");
  }
  inverse_scale_ = 1.0F / scale;
  impl_ = new Impl(path);
  if (!impl_->stream) {
    delete impl_;
    impl_ = nullptr;
    throw std::runtime_error("failed to open IQ source: " + path.string());
  }
}

FileIqSource::~FileIqSource() {
  delete impl_;
}

std::size_t FileIqSource::read(std::span<Complex> samples) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format_);
  buffer_.resize(samples.size() * bytes_per_sample);
  impl_->stream.read(reinterpret_cast<char*>(buffer_.data()), static_cast<std::streamsize>(buffer_.size()));
  const auto bytes = static_cast<std::size_t>(impl_->stream.gcount());
  if (bytes == 0U && impl_->stream.eof()) {
    impl_->stream.clear();
  }
  return decode_samples(std::span<const std::uint8_t>(buffer_.data(), bytes), format_, inverse_scale_, samples);
}

std::size_t encoded_sample_size_bytes(SampleFormat format) {
  switch (format) {
  case SampleFormat::fc32_iq:
  case SampleFormat::f32_stereo_iq:
    return 8;
  case SampleFormat::sc16_iq:
  case SampleFormat::s16_stereo_iq:
    return 4;
  }
  throw std::invalid_argument("unknown sample format");
}

std::size_t encode_samples(std::span<const Complex> in,
                           SampleFormat format,
                           float scale,
                           std::span<std::uint8_t> out) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format);
  const auto count = std::min(in.size(), out.size() / bytes_per_sample);

  for (std::size_t n = 0; n < count; ++n) {
    const auto sample = in[n] * scale;
    auto dst = out.subspan(n * bytes_per_sample, bytes_per_sample);
    switch (format) {
    case SampleFormat::fc32_iq:
    case SampleFormat::f32_stereo_iq:
      put_f32(dst.first(4), sample.real());
      put_f32(dst.subspan(4, 4), sample.imag());
      break;
    case SampleFormat::sc16_iq:
    case SampleFormat::s16_stereo_iq:
      put_le16(dst.first(2), clamp_s16(sample.real()));
      put_le16(dst.subspan(2, 2), clamp_s16(sample.imag()));
      break;
    }
  }

  return count * bytes_per_sample;
}

std::size_t decode_samples(std::span<const std::uint8_t> in,
                           SampleFormat format,
                           float inverse_scale,
                           std::span<Complex> out) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format);
  const auto count = std::min(out.size(), in.size() / bytes_per_sample);

  for (std::size_t n = 0; n < count; ++n) {
    auto src = in.subspan(n * bytes_per_sample, bytes_per_sample);
    switch (format) {
    case SampleFormat::fc32_iq:
    case SampleFormat::f32_stereo_iq:
      out[n] = {get_f32(src.first(4)) * inverse_scale, get_f32(src.subspan(4, 4)) * inverse_scale};
      break;
    case SampleFormat::sc16_iq:
    case SampleFormat::s16_stereo_iq:
      out[n] = {static_cast<float>(get_le16(src.first(2))) / 32767.0F * inverse_scale,
                static_cast<float>(get_le16(src.subspan(2, 2))) / 32767.0F * inverse_scale};
      break;
    }
  }

  return count;
}

} // namespace wbhf_modem
