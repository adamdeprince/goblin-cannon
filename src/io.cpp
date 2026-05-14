#include "wbhf_modem/io.hpp"

#include <algorithm>
#include <bit>
#include <cerrno>
#include <cstring>
#include <limits>
#include <stdexcept>
#include <string>
#include <system_error>

#include <fcntl.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <unistd.h>

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

std::string errno_message(const std::string& prefix) {
  return prefix + ": " + std::strerror(errno);
}

int open_fd(const std::filesystem::path& path, int flags, const char* role) {
#ifdef O_CLOEXEC
  flags |= O_CLOEXEC;
#endif
  int fd = -1;
  do {
    fd = ::open(path.c_str(), flags, 0666);
  } while (fd < 0 && errno == EINTR);
  if (fd < 0) {
    throw std::runtime_error(errno_message("failed to open IQ " + std::string(role) + ": " + path.string()));
  }
#ifndef O_CLOEXEC
  (void)::fcntl(fd, F_SETFD, FD_CLOEXEC);
#endif
  return fd;
}

void close_fd(int fd) noexcept {
  if (fd < 0) {
    return;
  }
  while (::close(fd) != 0 && errno == EINTR) {
  }
}

bool is_fifo_fd(int fd) {
  struct stat st {};
  if (::fstat(fd, &st) != 0) {
    throw std::runtime_error(errno_message("failed to stat IQ file descriptor"));
  }
  return S_ISFIFO(st.st_mode);
}

void set_pipe_capacity_if_fifo(int fd, std::size_t capacity_bytes) {
  if (capacity_bytes == 0U || !is_fifo_fd(fd)) {
    return;
  }
#ifdef F_SETPIPE_SZ
  const auto requested = static_cast<int>(std::min<std::size_t>(
      capacity_bytes,
      static_cast<std::size_t>(std::numeric_limits<int>::max())));
  if (::fcntl(fd, F_SETPIPE_SZ, requested) < 0) {
    throw std::runtime_error(errno_message("failed to set FIFO pipe capacity"));
  }
#else
  (void)fd;
  throw std::runtime_error("FIFO pipe capacity control is not supported on this platform");
#endif
}

void write_all(int fd, std::span<const std::uint8_t> bytes) {
  std::size_t offset = 0;
  while (offset < bytes.size()) {
    const auto remaining = bytes.size() - offset;
    const auto written = ::write(fd, bytes.data() + offset, remaining);
    if (written < 0) {
      if (errno == EINTR) {
        continue;
      }
      throw std::runtime_error(errno_message("failed to write IQ samples"));
    }
    if (written == 0) {
      throw std::runtime_error("failed to write IQ samples: zero-byte write");
    }
    offset += static_cast<std::size_t>(written);
  }
}

std::size_t pending_pipe_bytes(int fd) {
  int bytes = 0;
  if (::ioctl(fd, FIONREAD, &bytes) != 0 || bytes < 0) {
    return 0U;
  }
  return static_cast<std::size_t>(bytes);
}

} // namespace

struct FileIqSink::Impl {
  explicit Impl(const std::filesystem::path& path, std::size_t pipe_capacity_bytes)
      : fd(open_fd(path, O_WRONLY | O_CREAT | O_TRUNC, "sink")) {
    set_pipe_capacity_if_fifo(fd, pipe_capacity_bytes);
  }

  ~Impl() { close_fd(fd); }

  int fd = -1;
};

struct FileIqSource::Impl {
  explicit Impl(const std::filesystem::path& path, std::size_t pipe_capacity_bytes)
      : fd(open_fd(path, O_RDONLY, "source")) {
    set_pipe_capacity_if_fifo(fd, pipe_capacity_bytes);
  }

  ~Impl() { close_fd(fd); }

  int fd = -1;
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

FileIqSink::FileIqSink(const std::filesystem::path& path,
                       SampleFormat format,
                       float scale,
                       std::size_t pipe_capacity_bytes)
    : format_(format), scale_(scale), impl_(nullptr) {
  if (scale_ <= 0.0F) {
    throw std::invalid_argument("scale must be positive");
  }
  impl_ = new Impl(path, pipe_capacity_bytes);
}

FileIqSink::~FileIqSink() {
  delete impl_;
}

std::size_t FileIqSink::write(std::span<const Complex> samples) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format_);
  buffer_.resize(samples.size() * bytes_per_sample);
  const auto bytes = encode_samples(samples, format_, scale_, buffer_);
  write_all(impl_->fd, std::span<const std::uint8_t>(buffer_.data(), bytes));
  return samples.size();
}

void FileIqSink::flush() {
}

std::size_t FileIqSink::queued_bytes() const {
  return impl_ == nullptr ? 0U : pending_pipe_bytes(impl_->fd);
}

FileIqSource::FileIqSource(const std::filesystem::path& path,
                           SampleFormat format,
                           float scale,
                           std::size_t pipe_capacity_bytes)
    : format_(format), inverse_scale_(1.0F), impl_(nullptr) {
  if (scale <= 0.0F) {
    throw std::invalid_argument("scale must be positive");
  }
  inverse_scale_ = 1.0F / scale;
  impl_ = new Impl(path, pipe_capacity_bytes);
}

FileIqSource::~FileIqSource() {
  delete impl_;
}

std::size_t FileIqSource::read(std::span<Complex> samples) {
  const auto bytes_per_sample = encoded_sample_size_bytes(format_);
  const auto previous_pending = buffer_.size();
  buffer_.resize(previous_pending + samples.size() * bytes_per_sample);
  ssize_t read_bytes = 0;
  do {
    read_bytes = ::read(impl_->fd,
                        buffer_.data() + previous_pending,
                        buffer_.size() - previous_pending);
  } while (read_bytes < 0 && errno == EINTR);
  if (read_bytes < 0) {
    throw std::runtime_error(errno_message("failed to read IQ samples"));
  }
  buffer_.resize(previous_pending + static_cast<std::size_t>(read_bytes));
  const auto complete_bytes = (buffer_.size() / bytes_per_sample) * bytes_per_sample;
  const auto decoded = decode_samples(std::span<const std::uint8_t>(buffer_.data(), complete_bytes),
                                      format_,
                                      inverse_scale_,
                                      samples);
  if (complete_bytes != 0U) {
    buffer_.erase(buffer_.begin(), buffer_.begin() + static_cast<std::ptrdiff_t>(complete_bytes));
  }
  return decoded;
}

std::size_t FileIqSource::readable_bytes() const {
  return impl_ == nullptr ? 0U : pending_pipe_bytes(impl_->fd) + buffer_.size();
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
