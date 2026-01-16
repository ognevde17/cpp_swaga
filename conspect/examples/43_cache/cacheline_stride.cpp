#include <chrono>
#include <cstdint>
#include <cstdio>
#include <vector>

static uint64_t bench(size_t n_bytes, size_t stride) {
  std::vector<uint8_t> a(n_bytes);
  volatile uint64_t s = 0;
  auto t0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < n_bytes; i += stride) s += a[i];
  auto t1 = std::chrono::steady_clock::now();
  return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() + (uint64_t)s;
}

int main() {
  size_t n = 256ull * 1024 * 1024;
  for (size_t stride : {4u, 8u, 16u, 32u, 64u, 128u, 256u, 512u, 1024u}) {
    uint64_t ns = bench(n, stride);
    std::printf("%zu %llu\n", stride, (unsigned long long)ns);
  }
  return 0;
}

