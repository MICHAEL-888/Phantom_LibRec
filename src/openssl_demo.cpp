#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <array>
#include <cstdint>

#include <openssl/evp.h>

int main() {
  const std::array<std::uint8_t, 6> input{{1, 2, 3, 4, 5, 6}};
  std::array<std::uint8_t, EVP_MAX_MD_SIZE> digest{};
  unsigned int digest_len = 0;
  if (EVP_Digest(input.data(), input.size(), digest.data(), &digest_len, EVP_sha256(), nullptr) != 1) {
    std::printf("OpenSSL digest failed\n");
    return 1;
  }
  std::printf("OpenSSL digest length: %u\n", digest_len);
  return 0;
}
#else
int main() {
  std::printf("OpenSSL demo (deps disabled)\n");
  return 0;
}
#endif
