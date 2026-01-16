#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void h(int signo) {
  dprintf(1, "AHAHAHAHAHAHAA\n");
}

int main() {
  signal(SIGSEGV, h);
  int *p = 0;
  *p = 1;
  return 0;
}

