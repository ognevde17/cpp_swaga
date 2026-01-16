#include <stdio.h>
#include <stdint.h>

int main() {
  uint64_t a = 1;
  uint64_t b = 2;
  __asm__ __volatile__("xchg %0, %1" : "+r"(a), "+r"(b));
  printf("%llu %llu\n", (unsigned long long)a, (unsigned long long)b);
  return 0;
}

