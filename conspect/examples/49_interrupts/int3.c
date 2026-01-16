#include <stdio.h>

int main() {
  puts("before");
  __asm__ __volatile__("int3");
  puts("after");
  return 0;
}

