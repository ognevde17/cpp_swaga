#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    dprintf(2, "usage: %s <src> <dst>\n", argv[0]);
    return 2;
  }
  if (rename(argv[1], argv[2]) != 0) {
    perror("rename");
    return 1;
  }
  return 0;
}

