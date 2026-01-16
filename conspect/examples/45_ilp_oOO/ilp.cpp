#include <chrono>
#include <cstdint>
#include <cstdio>
#include <vector>

static uint64_t dep(const std::vector<uint64_t> &a) {
  volatile uint64_t x = 1;
  auto t0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < a.size(); ++i) x = x * 3 + a[i];
  auto t1 = std::chrono::steady_clock::now();
  return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() + (uint64_t)x;
}

static uint64_t indep(const std::vector<uint64_t> &a) {
  volatile uint64_t x0 = 1, x1 = 2, x2 = 3, x3 = 4;
  auto t0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < a.size(); i += 4) {
    x0 = x0 * 3 + a[i + 0];
    x1 = x1 * 3 + a[i + 1];
    x2 = x2 * 3 + a[i + 2];
    x3 = x3 * 3 + a[i + 3];
  }
  auto t1 = std::chrono::steady_clock::now();
  return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() + (uint64_t)(x0 + x1 + x2 + x3);
}

int main() {
  size_t n = 200000000;
  std::vector<uint64_t> a(n);
  for (size_t i = 0; i < n; ++i) a[i] = (uint64_t)i;
  if (a.size() % 4 != 0) a.resize(a.size() + (4 - a.size() % 4), 0);

  uint64_t t1 = dep(a);
  uint64_t t2 = indep(a);
  std::printf("dependent %llu\n", (unsigned long long)t1);
  std::printf("independent %llu\n", (unsigned long long)t2);
  return 0;
}

