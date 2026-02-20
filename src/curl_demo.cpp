#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <curl/curl.h>

namespace {
size_t discard_write(char* ptr, size_t size, size_t nmemb, void* userdata) {
  (void)ptr;
  (void)userdata;
  return size * nmemb;
}
}

int main() {
  CURLcode init_result = curl_global_init(CURL_GLOBAL_DEFAULT);
  if (init_result != CURLE_OK) {
    std::printf("curl global init failed: %s\n", curl_easy_strerror(init_result));
    return 1;
  }

  CURL* handle = curl_easy_init();
  if (!handle) {
    std::printf("curl easy init failed\n");
    curl_global_cleanup();
    return 1;
  }

  curl_easy_setopt(handle, CURLOPT_URL, "https://example.com");
  curl_easy_setopt(handle, CURLOPT_NOBODY, 1L);
  curl_easy_setopt(handle, CURLOPT_WRITEFUNCTION, discard_write);
  CURLcode result = curl_easy_perform(handle);
  if (result != CURLE_OK) {
    std::printf("curl request failed: %s\n", curl_easy_strerror(result));
  } else {
    std::printf("curl request completed\n");
  }

  curl_easy_cleanup(handle);
  curl_global_cleanup();
  return result == CURLE_OK ? 0 : 1;
}
#else
int main() {
  std::printf("curl demo (deps disabled)\n");
  return 0;
}
#endif
