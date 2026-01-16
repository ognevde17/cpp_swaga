#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv) {
  if (argc != 3) {
    dprintf(2, "usage: %s <target> <linkpath>\n", argv[0]);
    return 2;
  }
  if (symlink(argv[1], argv[2]) != 0) {
    perror("symlink");
    return 1;
  }
  return 0;
}

