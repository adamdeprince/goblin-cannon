#include "goblin_cannon/crypto.hpp"

#include <openssl/err.h>
#include <openssl/evp.h>

#include <array>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>
#include <algorithm>
#include <cerrno>
#include <cstring>
#include <filesystem>
#include <fcntl.h>
#include <sys/file.h>
#include <sys/stat.h>
#include <unistd.h>

namespace goblin_cannon {

namespace {

struct EvpCipherCtxDeleter {
  void operator()(EVP_CIPHER_CTX* ctx) const noexcept { EVP_CIPHER_CTX_free(ctx); }
};

using EvpCipherCtx = std::unique_ptr<EVP_CIPHER_CTX, EvpCipherCtxDeleter>;

std::string openssl_error_message(const char* operation) {
  const auto code = ERR_get_error();
  if (code == 0UL) {
    return operation;
  }
  std::array<char, 256> buffer{};
  ERR_error_string_n(code, buffer.data(), buffer.size());
  return std::string(operation) + ": " + buffer.data();
}

} // namespace

namespace {
struct File {
  int fd;
  explicit File(int f) : fd(f) { if (fd < 0) throw std::runtime_error(std::string("epoch state: ") + std::strerror(errno)); }
  ~File() { close(fd); }
};
constexpr std::array<std::uint8_t, 16> epoch_magic{'G','O','B','L','I','N','-','E','P','O','C','H','-','0','1','\n'};
void write_all(int fd, std::span<const std::uint8_t> bytes) {
  while (!bytes.empty()) {
    const auto n = write(fd, bytes.data(), bytes.size());
    if (n < 0 && errno == EINTR) continue;
    if (n <= 0) throw std::runtime_error("cannot persist transmitter epoch");
    bytes = bytes.subspan(static_cast<std::size_t>(n));
  }
}
void read_at(int fd, std::span<std::uint8_t> bytes, off_t at) {
  while (!bytes.empty()) {
    const auto n = pread(fd, bytes.data(), bytes.size(), at);
    if (n < 0 && errno == EINTR) continue;
    if (n <= 0) throw std::runtime_error("truncated transmitter epoch state");
    bytes = bytes.subspan(static_cast<std::size_t>(n)); at += n;
  }
}
void put64(std::span<std::uint8_t> out, std::uint64_t value) {
  for (int i = 7; i >= 0; --i) { out[i] = static_cast<std::uint8_t>(value); value >>= 8; }
}
std::uint64_t get64(std::span<const std::uint8_t> in) {
  std::uint64_t value = 0;
  for (auto b : in.first(8)) value = (value << 8) | b;
  return value;
}
void check_evp(int ok, const char* operation) {
  if (ok != 1) throw std::runtime_error(openssl_error_message(operation));
}
int evp_size(std::size_t size) {
  if (size > static_cast<std::size_t>(std::numeric_limits<int>::max())) throw std::length_error("GCM record too large");
  return static_cast<int>(size);
}
}

void initialize_transmitter_epoch_store(const std::string& path) {
  // O_EXCL deliberately forbids reinitialization. Never unlink failed state.
  File file(open(path.c_str(), O_WRONLY | O_CREAT | O_EXCL | O_NOFOLLOW | O_CLOEXEC, 0600));
  write_all(file.fd, epoch_magic);
  if (fsync(file.fd)) throw std::runtime_error("cannot sync transmitter epoch state");
  const auto parent = std::filesystem::path(path).parent_path();
  File directory(open((parent.empty() ? std::filesystem::path(".") : parent).c_str(), O_RDONLY | O_DIRECTORY | O_CLOEXEC));
  if (fsync(directory.fd)) throw std::runtime_error("cannot sync transmitter epoch directory");
}

std::shared_ptr<TransmitterEpoch> TransmitterEpoch::reserve(const std::string& path, std::uint64_t minimum) {
  if (path.empty() || minimum == 0) throw std::invalid_argument("a provisioned epoch-state path and nonzero epoch are required");
  File file(open(path.c_str(), O_RDWR | O_APPEND | O_NOFOLLOW | O_CLOEXEC));
  if (flock(file.fd, LOCK_EX)) throw std::runtime_error("cannot lock transmitter epoch state");
  struct stat state{};
  if (fstat(file.fd, &state) || !S_ISREG(state.st_mode) || state.st_uid != geteuid() || (state.st_mode & 0077) ||
      state.st_size < 16 || state.st_size % 16) throw std::runtime_error("invalid or insecure transmitter epoch state");
  std::array<std::uint8_t, 16> record{};
  read_at(file.fd, record, 0);
  if (record != epoch_magic) throw std::runtime_error("invalid transmitter epoch signature");
  std::uint64_t previous = 0;
  if (state.st_size > 16) {
    read_at(file.fd, record, state.st_size - 16);
    previous = get64(record);
    if (!previous || get64(std::span(record).subspan(8)) != ~previous)
      throw std::runtime_error("damaged transmitter epoch journal; rotate key before reprovisioning");
  }
  if (previous == std::numeric_limits<std::uint64_t>::max()) throw std::overflow_error("transmitter epoch exhausted");
  const auto next = std::max(previous + 1, minimum);
  put64(record, next); put64(std::span(record).subspan(8), ~next);
  write_all(file.fd, record);
  // No nonce from this epoch may leave this function before durable commit.
  if (fsync(file.fd)) throw std::runtime_error("cannot commit transmitter epoch");
  return std::shared_ptr<TransmitterEpoch>(new TransmitterEpoch(next));
}
void TransmitterEpoch::claim() {
  if (claimed_.exchange(true)) throw std::logic_error("transmitter epoch was already claimed");
}
GcmNonce message_nonce(std::uint64_t epoch, std::uint32_t sequence) {
  if (!epoch || !sequence) throw std::invalid_argument("GCM epoch and frame sequence must be nonzero");
  GcmNonce nonce{};
  put64(nonce, epoch);
  for (int i = 11; i >= 8; --i) { nonce[i] = static_cast<std::uint8_t>(sequence); sequence >>= 8; }
  return nonce;
}

class Aes256Gcm::Impl {
public:
  explicit Impl(const Aes256Key& key) : encrypt(EVP_CIPHER_CTX_new()), decrypt(EVP_CIPHER_CTX_new()) {
    if (!encrypt || !decrypt) throw std::runtime_error("cannot allocate GCM contexts");
    check_evp(EVP_EncryptInit_ex(encrypt.get(), EVP_aes_256_gcm(), nullptr, key.bytes.data(), nullptr), "GCM encryption key");
    check_evp(EVP_DecryptInit_ex(decrypt.get(), EVP_aes_256_gcm(), nullptr, key.bytes.data(), nullptr), "GCM decryption key");
  }
  EvpCipherCtx encrypt, decrypt;
  std::vector<std::uint8_t> scratch;
};
Aes256Gcm::Aes256Gcm(const Aes256Key& key) : impl_(std::make_unique<Impl>(key)) {}
Aes256Gcm::~Aes256Gcm() = default;
void Aes256Gcm::seal(const GcmNonce& nonce, std::span<const std::uint8_t> ad,
                    std::span<const std::uint8_t> plain, std::vector<std::uint8_t>& cipher, GcmTag& tag) {
  auto* ctx = impl_->encrypt.get();
  check_evp(EVP_EncryptInit_ex(ctx, nullptr, nullptr, nullptr, nonce.data()), "GCM nonce");
  int n = 0, final = 0;
  check_evp(EVP_EncryptUpdate(ctx, nullptr, &n, ad.data(), evp_size(ad.size())), "GCM associated data");
  cipher.resize(plain.size() + 16);
  check_evp(EVP_EncryptUpdate(ctx, cipher.data(), &n, plain.data(), evp_size(plain.size())), "GCM encrypt");
  check_evp(EVP_EncryptFinal_ex(ctx, cipher.data() + n, &final), "GCM encryption final");
  cipher.resize(static_cast<std::size_t>(n + final));
  check_evp(EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_GET_TAG, tag.size(), tag.data()), "GCM get tag");
}
bool Aes256Gcm::open(const GcmNonce& nonce, std::span<const std::uint8_t> ad,
                    std::span<const std::uint8_t> cipher, const GcmTag& tag, std::vector<std::uint8_t>& plain) {
  plain.clear();
  auto* ctx = impl_->decrypt.get();
  check_evp(EVP_DecryptInit_ex(ctx, nullptr, nullptr, nullptr, nonce.data()), "GCM nonce");
  int n = 0, final = 0;
  check_evp(EVP_DecryptUpdate(ctx, nullptr, &n, ad.data(), evp_size(ad.size())), "GCM associated data");
  auto& scratch = impl_->scratch;
  scratch.resize(cipher.size() + 16);
  check_evp(EVP_DecryptUpdate(ctx, scratch.data(), &n, cipher.data(), evp_size(cipher.size())), "GCM decrypt");
  auto expected_tag = tag;
  check_evp(EVP_CIPHER_CTX_ctrl(ctx, EVP_CTRL_GCM_SET_TAG, expected_tag.size(), expected_tag.data()), "GCM set tag");
  const bool authenticated = EVP_DecryptFinal_ex(ctx, scratch.data() + n, &final) == 1;
  if (authenticated) plain.assign(scratch.begin(), scratch.begin() + n + final);
  OPENSSL_cleanse(scratch.data(), scratch.size());
  return authenticated;
}

class Aes128CtrKeystream::Impl {
public:
  Impl(const Aes128Key& key, const Aes128CtrCounter& initial_counter) {
    ctx_.reset(EVP_CIPHER_CTX_new());
    if (!ctx_) {
      throw std::runtime_error(openssl_error_message("EVP_CIPHER_CTX_new failed"));
    }
    if (EVP_EncryptInit_ex(ctx_.get(),
                           EVP_aes_128_ctr(),
                           nullptr,
                           key.bytes.data(),
                           initial_counter.data()) != 1) {
      throw std::runtime_error(openssl_error_message("EVP_EncryptInit_ex failed"));
    }
    if (EVP_CIPHER_CTX_set_padding(ctx_.get(), 0) != 1) {
      throw std::runtime_error(openssl_error_message("EVP_CIPHER_CTX_set_padding failed"));
    }
  }

  void generate(std::span<std::uint8_t> out) {
    std::vector<std::uint8_t> zeros(out.size(), 0U);
    xor_bytes(zeros, out);
  }

  void xor_bytes(std::span<const std::uint8_t> in, std::span<std::uint8_t> out) {
    if (in.size() != out.size()) {
      throw std::invalid_argument("AES-128-CTR input and output sizes must match");
    }
    if (in.size() > static_cast<std::size_t>(std::numeric_limits<int>::max())) {
      throw std::invalid_argument("AES-128-CTR buffer exceeds OpenSSL EVP int range");
    }

    int produced = 0;
    if (!in.empty() &&
        EVP_EncryptUpdate(ctx_.get(),
                          reinterpret_cast<unsigned char*>(out.data()),
                          &produced,
                          reinterpret_cast<const unsigned char*>(in.data()),
                          static_cast<int>(in.size())) != 1) {
      throw std::runtime_error(openssl_error_message("EVP_EncryptUpdate failed"));
    }
    if (produced != static_cast<int>(in.size())) {
      throw std::runtime_error("AES-128-CTR produced an unexpected byte count");
    }
  }

private:
  EvpCipherCtx ctx_;
};

Aes128CtrKeystream::Aes128CtrKeystream(Aes128Key key, Aes128CtrCounter initial_counter)
    : impl_(std::make_unique<Impl>(key, initial_counter)) {}

Aes128CtrKeystream::~Aes128CtrKeystream() = default;
Aes128CtrKeystream::Aes128CtrKeystream(Aes128CtrKeystream&&) noexcept = default;
Aes128CtrKeystream& Aes128CtrKeystream::operator=(Aes128CtrKeystream&&) noexcept = default;

void Aes128CtrKeystream::generate(std::span<std::uint8_t> out) {
  impl_->generate(out);
}

void Aes128CtrKeystream::xor_bytes(std::span<const std::uint8_t> in, std::span<std::uint8_t> out) {
  impl_->xor_bytes(in, out);
}

} // namespace goblin_cannon
