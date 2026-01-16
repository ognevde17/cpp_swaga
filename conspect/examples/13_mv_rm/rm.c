#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 2) {
    dprintf(2, "usage: %s <path>\n", argv[0]);
    return 2;
  }
  if (unlink(argv[1]) != 0) {
    perror("unlink");
    return 1;
  }
  return 0;
}

