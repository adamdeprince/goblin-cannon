#include "goblin_cannon/crypto.hpp"

#include <openssl/err.h>
#include <openssl/evp.h>

#include <array>
#include <limits>
#include <memory>
#include <stdexcept>
#include <string>
#include <vector>

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
