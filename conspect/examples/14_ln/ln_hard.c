#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    dprintf(2, "usage: %s <existing> <new>\n", argv[0]);
    return 2;
  }
  if (link(argv[1], argv[2]) != 0) {
    perror("link");
    return 1;
  }
  return 0;
}

