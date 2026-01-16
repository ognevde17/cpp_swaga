#include <stdio.h>

int main() {
  puts("before");
  __asm__ __volatile__("ud2");
  puts("after");
  return 0;
}

