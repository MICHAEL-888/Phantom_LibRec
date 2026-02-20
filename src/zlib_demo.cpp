#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <array>
#include <cstdint>

#include <zlib.h>

int main() {
  const std::array<std::uint8_t, 6> input{{1, 2, 3, 4, 5, 6}};
  std::array<std::uint8_t, 32> compressed{};
  uLongf compressed_len = static_cast<uLongf>(compressed.size());
  int result = compress2(reinterpret_cast<Bytef*>(compressed.data()), &compressed_len,
                         reinterpret_cast<const Bytef*>(input.data()),
                         static_cast<uLong>(input.size()), Z_BEST_SPEED);
  if (result != Z_OK) {
    std::printf("zlib compress failed: %d\n", result);
    return 1;
  }
  std::printf("zlib compressed %lu bytes\n", static_cast<unsigned long>(compressed_len));
  return 0;
}
#else
int main() {
  std::printf("zlib demo (deps disabled)\n");
  return 0;
}
#endif
