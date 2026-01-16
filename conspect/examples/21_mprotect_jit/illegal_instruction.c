#include <stdint.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  size_t n = 4096;
  unsigned char *p = (unsigned char*)mmap(0, n, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) return 1;
  unsigned char code[] = {0x0f, 0x0b};
  p[0] = code[0];
  p[1] = code[1];
  if (mprotect(p, n, PROT_READ | PROT_EXEC) != 0) return 1;
  void (*f)() = (void (*)())p;
  f();
  munmap(p, n);
  return 0;
}

