#include <stdint.h>
#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  size_t n = 4096;
  unsigned char *p = mmap(0, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) return 1;
  unsigned char code[] = {0xb8, 0x2a, 0x00, 0x00, 0x00, 0xc3};
  for (size_t i = 0; i < sizeof(code); ++i) p[i] = code[i];
  if (mprotect(p, n, PROT_READ | PROT_EXEC) != 0) return 1;
  int (*f)() = (int (*)())p;
  int r = f();
  dprintf(1, "%d\n", r);
  munmap(p, n);
  return 0;
}

