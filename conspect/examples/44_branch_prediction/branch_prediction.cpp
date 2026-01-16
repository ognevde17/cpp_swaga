#include <algorithm>
#include <chrono>
#include <cstdint>
#include <cstdio>
#include <random>
#include <vector>

static uint64_t run(const std::vector<int> &a) {
  volatile uint64_t s = 0;
  auto t0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < a.size(); ++i) {
    if (a[i] >= 0) s += 1;
  }
  auto t1 = std::chrono::steady_clock::now();
  return (uint64_t)std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count() + (uint64_t)s;
}

int main() {
  size_t n = 200000000;
  std::vector<int> a(n);
  std::mt19937 rng(123);
  std::uniform_int_distribution<int> dist(-1, 1);
  for (size_t i = 0; i < n; ++i) a[i] = dist(rng);

  std::vector<int> b = a;
  std::sort(b.begin(), b.end());

  uint64_t t_sorted = run(b);
  uint64_t t_random = run(a);

  std::printf("sorted %llu\n", (unsigned long long)t_sorted);
  std::printf("random %llu\n", (unsigned long long)t_random);
  return 0;
}

