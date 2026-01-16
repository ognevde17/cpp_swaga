#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(2, "usage: %s <fifo_path>\n", argv[0]);
    return 2;
  }
  int fd = open(argv[1], O_RDONLY);
  if (fd < 0) {
    perror("open");
    return 1;
  }
  char buf[4096];
  ssize_t r;
  while ((r = read(fd, buf, sizeof(buf))) > 0) {
    ssize_t off = 0;
    while (off < r) {
      ssize_t w = write(1, buf + off, (size_t)(r - off));
      if (w < 0) return 1;
      off += w;
    }
  }
  close(fd);
  return 0;
}

