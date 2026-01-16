#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>

static int write_all(int fd, const char *buf, size_t n) {
  size_t off = 0;
  while (off < n) {
    ssize_t w = write(fd, buf + off, n - off);
    if (w < 0) return -1;
    off += (size_t)w;
  }
  return 0;
}

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(2, "usage: %s <file>\n", argv[0]);
    return 2;
  }

  int fd = open(argv[1], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (fd < 0) {
    perror("open");
    return 1;
  }

  char buf[1 << 15];
  while (1) {
    ssize_t r = read(0, buf, sizeof(buf));
    if (r < 0) {
      perror("read");
      close(fd);
      return 1;
    }
    if (r == 0) break;
    if (write_all(1, buf, (size_t)r) != 0) {
      perror("write stdout");
      close(fd);
      return 1;
    }
    if (write_all(fd, buf, (size_t)r) != 0) {
      perror("write file");
      close(fd);
      return 1;
    }
  }

  close(fd);
  return 0;
}

