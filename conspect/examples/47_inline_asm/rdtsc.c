#include <stdint.h>
#include <stdio.h>

static inline void cpuid_serialize() {
  uint32_t a, b, c, d;
  a = 0;
  __asm__ __volatile__("cpuid" : "+a"(a), "=b"(b), "=c"(c), "=d"(d));
}

static inline uint64_t rdtsc() {
  uint32_t lo, hi;
  __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
  return ((uint64_t)hi << 32) | lo;
}

int main() {
  cpuid_serialize();
  uint64_t t0 = rdtsc();
  volatile uint64_t x = 0;
  for (uint64_t i = 0; i < 100000000; ++i) x += i;
  cpuid_serialize();
  uint64_t t1 = rdtsc();
  printf("%llu\n", (unsigned long long)(t1 - t0 + x));
  return 0;
}

