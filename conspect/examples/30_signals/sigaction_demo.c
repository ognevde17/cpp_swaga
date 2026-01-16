#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static volatile sig_atomic_t got = 0;

static void handler(int signo) {
  got = signo;
  for (volatile int i = 0; i < 200000000; ++i) {
  }
}

int main() {
  struct sigaction sa = {0};
  sa.sa_handler = handler;
  sigfillset(&sa.sa_mask);
  sa.sa_flags = SA_RESTART;
  if (sigaction(SIGINT, &sa, 0) != 0) return 1;
  while (got == 0) pause();
  dprintf(1, "%d\n", got);
  return 0;
}

