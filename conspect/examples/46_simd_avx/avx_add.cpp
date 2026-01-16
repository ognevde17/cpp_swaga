#include <immintrin.h>
#include <chrono>
#include <cstdio>
#include <vector>

static float sum(const std::vector<float> &a) {
  float s = 0;
  for (float x : a) s += x;
  return s;
}

int main() {
  size_t n = 1 << 26;
  std::vector<float> a(n, 1.0f), b(n, 2.0f), c(n, 0.0f);

  auto t0 = std::chrono::steady_clock::now();
  for (size_t i = 0; i < n; ++i) c[i] = a[i] + b[i];
  auto t1 = std::chrono::steady_clock::now();

  auto t2 = std::chrono::steady_clock::now();
  for (size_t i = 0; i + 8 <= n; i += 8) {
    __m256 va = _mm256_loadu_ps(&a[i]);
    __m256 vb = _mm256_loadu_ps(&b[i]);
    __m256 vc = _mm256_add_ps(va, vb);
    _mm256_storeu_ps(&c[i], vc);
  }
  auto t3 = std::chrono::steady_clock::now();

  auto ns_scalar = std::chrono::duration_cast<std::chrono::nanoseconds>(t1 - t0).count();
  auto ns_avx = std::chrono::duration_cast<std::chrono::nanoseconds>(t3 - t2).count();

  std::printf("scalar %lld\n", (long long)ns_scalar);
  std::printf("avx2 %lld\n", (long long)ns_avx);
  std::printf("check %f\n", sum(c));
  return 0;
}

