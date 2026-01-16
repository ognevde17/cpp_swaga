#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <random>
#include <vector>

static uint64_t bench(size_t n_ints) {
  std::vector<uint32_t> a(n_ints, 1);
  std::vector<size_t> idx(n_ints);
  for (size_t i = 0; i < n_ints; ++i) idx[i] = i;
  std::mt19937_64 rng(123);
  std::shuffle(idx.begin(), idx.end(), rng);

  volatile uint64_t s = 0;
  auto t0 = std::chrono::steady_clock::now();
  for (size_t k = 0; k < n_ints; ++k) s += a[idx[k]];
  auto t1 = std::chrono::steady_clock::now();
  return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() + (uint64_t)s;
}

int main() {
  for (size_t bytes = 4 * 1024; bytes <= 256ull * 1024 * 1024; bytes *= 2) {
    size_t n = bytes / sizeof(uint32_t);
    uint64_t ns = bench(n);
    std::printf("%zu %llu\n", bytes, (unsigned long long)ns);
  }
  return 0;
}

