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
  if (argc != 3) {
    dprintf(2, "usage: %s <src> <dst>\n", argv[0]);
    return 2;
  }

  int in = open(argv[1], O_RDONLY);
  if (in < 0) {
    perror("open src");
    return 1;
  }

  int out = open(argv[2], O_WRONLY | O_CREAT | O_TRUNC, 0644);
  if (out < 0) {
    perror("open dst");
    close(in);
    return 1;
  }

  char buf[1 << 16];
  while (1) {
    ssize_t r = read(in, buf, sizeof(buf));
    if (r < 0) {
      perror("read");
      close(in);
      close(out);
      return 1;
    }
    if (r == 0) break;
    if (write_all(out, buf, (size_t)r) != 0) {
      perror("write");
      close(in);
      close(out);
      return 1;
    }
  }

  close(in);
  close(out);
  return 0;
}

