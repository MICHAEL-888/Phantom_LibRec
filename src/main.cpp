#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <array>
#include <cstdint>
#include <string>
#include <fmt/format.h>
#include <spdlog/spdlog.h>

#include <zlib.h>

#include <openssl/evp.h>

#include <curl/curl.h>
#endif

#if LIBREC_DEPS_ENABLED
namespace {
size_t discard_write(char* ptr, size_t size, size_t nmemb, void* userdata) {
  (void)ptr;
  (void)userdata;
  return size * nmemb;
}
}
#endif

int main() {
#if LIBREC_DEPS_ENABLED
  spdlog::info("librec_static_demo start");

  const std::string message = "static-link smoke test";
  std::string formatted = fmt::format("message: {} (len={})", message, message.size());
  std::printf("%s\n", formatted.c_str());

  const std::array<std::uint8_t, 6> input{{1, 2, 3, 4, 5, 6}};
  std::array<std::uint8_t, 32> compressed{};
  uLongf compressed_len = static_cast<uLongf>(compressed.size());
  int z_result = compress2(reinterpret_cast<Bytef*>(compressed.data()), &compressed_len,
                           reinterpret_cast<const Bytef*>(input.data()),
                           static_cast<uLong>(input.size()), Z_BEST_SPEED);
  if (z_result != Z_OK) {
    spdlog::error("zlib compress failed: {}", z_result);
  }

  std::array<std::uint8_t, EVP_MAX_MD_SIZE> digest{};
  unsigned int digest_len = 0;
  if (EVP_Digest(input.data(), input.size(), digest.data(), &digest_len, EVP_sha256(), nullptr) != 1) {
    spdlog::error("OpenSSL digest failed");
  } else {
    spdlog::info("OpenSSL digest length: {}", digest_len);
  }

  CURLcode curl_init_code = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (curl_init_code != CURLE_OK) {
    spdlog::error("curl global init failed: {}", curl_easy_strerror(curl_init_code));
  } else {
    CURL* handle = curl_easy_init();
    if (handle) {
      curl_easy_setopt(handle, CURLOPT_URL, "https://example.com");
      curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
      curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, discard_write);
      CURLcode curl_result = curl_easy_perform(handle);
      if (curl_result != CURLE_OK) {
        spdlog::warn("curl request failed: {}", curl_easy_strerror(curl_result));
      } else {
        spdlog::info("curl request completed");
      }
      curl_easy_cleanup(handle);
    } else {
      spdlog::error("curl easy init failed");
    }
    curl_global_cleanup();
  }

  spdlog::info("librec_static_demo done");
#else
  std::printf("librec_static_demo (deps disabled)\n");
#endif
  return 0;
}
