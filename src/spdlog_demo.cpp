#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <spdlog/spdlog.h>

int main() {
  spdlog::info("spdlog demo start");
  std::printf("spdlog demo running\n");
  spdlog::info("spdlog demo done");
  return 0;
}
#else
int main() {
  std::printf("spdlog demo (deps disabled)\n");
  return 0;
}
#endif
