#include <fcntl.h>
#include <stdio.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(2, "usage: %s <file>\n", argv[0]);
    return 2;
  }
  int fd = open(argv[1], O_RDWR);
  if (fd < 0) {
    perror("open");
    return 1;
  }
  struct stat st;
  if (fstat(fd, &st) != 0) {
    perror("fstat");
    return 1;
  }
  if (st.st_size == 0) return 0;
  char *p = mmap(0, st.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if (p == MAP_FAILED) {
    perror("mmap");
    return 1;
  }
  p[0] = 'X';
  msync(p, st.st_size, MS_SYNC);
  munmap(p, st.st_size);
  close(fd);
  return 0;
}

