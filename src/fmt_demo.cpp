#include <cstdio>

#ifndef LIBREC_DEPS_ENABLED
#define LIBREC_DEPS_ENABLED 0
#endif

#if LIBREC_DEPS_ENABLED
#include <string>

#include <fmt/format.h>

int main() {
  const std::string value = "fmt demo";
  const std::string formatted = fmt::format("{} (len={})", value, value.size());
  std::printf("%s\n", formatted.c_str());
  return 0;
}
#else
int main() {
  std::printf("fmt demo (deps disabled)\n");
  return 0;
}
#endif
