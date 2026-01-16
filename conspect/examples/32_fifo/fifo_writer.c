#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
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
    dprintf(2, "usage: %s <fifo_path> <msg>\n", argv[0]);
    return 2;
  }
  if (mkfifo(argv[1], 0666) != 0 && errno != EEXIST) {
    perror("mkfifo");
    return 1;
  }
  int fd = open(argv[1], O_WRONLY);
  if (fd < 0) {
    perror("open");
    return 1;
  }
  if (write_all(fd, argv[2], strlen(argv[2])) != 0) {
    perror("write");
    close(fd);
    return 1;
  }
  close(fd);
  return 0;
}

