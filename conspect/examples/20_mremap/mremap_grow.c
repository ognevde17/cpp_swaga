
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

int main() {
  long page_l = sysconf(_SC_PAGESIZE);
  if (page_l <= 0) {
    fprintf(stderr, "sysconf(_SC_PAGESIZE) failed\n");
    return 1;
  }

  size_t old_sz = (size_t)page_l;
  size_t new_sz = 2 * old_sz;

  char *p = mmap(NULL, old_sz, PROT_READ | PROT_WRITE,
                 MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
  if (p == MAP_FAILED) {
    fprintf(stderr, "mmap: %s\n", strerror(errno));
    return 1;
  }

  p[0] = 'A';

  char *q = mremap(p, old_sz, new_sz, MREMAP_MAYMOVE);
  if (q == MAP_FAILED) {
    fprintf(stderr, "mremap: %s\n", strerror(errno));
    munmap(p, old_sz);
    return 1;
  }

  q[old_sz] = 'B'; 
  printf("%p -> %p  bytes=[%c,%c]\n", (void *)p, (void *)q, q[0], q[old_sz]);

  munmap(q, new_sz);
  return 0;
}

