#include <manifold/os/env.hpp>

#ifdef MANIFOLD_PLATFORM_WINDOWS
#include <Windows.h>
#elif defined(MANIFOLD_PLATFORM_LINUX)
#include <unistd.h>
#include <stdlib.h>
#elif defined(MANIFOLD_PLATFORM_APPLE)
#include <mach-o/dyld.h>
#endif

#define kMaxEnvVarBufferSize 4096

namespace manifold::env {

auto get(const std::string &key) -> std::string {
#ifdef MANIFOLD_PLATFORM_WINDOWS
  char buffer[kMaxEnvVarBufferSize];
  GetEnvironmentVariable(key.c_str(), buffer, kMaxEnvVarBufferSize);
  return std::string(buffer);
#elif defined(MANIFOLD_PLATFORM_LINUX) || defined(MANIFOLD_PLATFORM_APPLE)
  char *value = getenv(key.c_str());

  return value == nullptr ? "" : std::string(value);
#endif
}

auto set(const std::string &key, const std::string &value) -> void {
#ifdef MANIFOLD_PLATFORM_WINDOWS
  SetEnvironmentVariable(key.c_str(), value.c_str());
#elif defined(MANIFOLD_PLATFORM_LINUX) || defined(MANIFOLD_PLATFORM_APPLE)
  setenv(key.c_str(), value.c_str(), 1);
#endif
}

auto processor_count() -> std::size_t {
  // yay! C++11 supports this for our use c:
  return std::thread::hardware_concurrency();
}
}
