#define _GNU_SOURCE
#include <errno.h>
#include <linux/futex.h>
#include <sched.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/syscall.h>
#include <unistd.h>

static int futex_wait_int(int *addr, int expected) {
  return (int)syscall(SYS_futex, addr, FUTEX_WAIT, expected, 0, 0, 0);
}

static int thread_fn(void *arg) {
  (void)arg;
  for (int i = 0; i < 5; ++i) {
    dprintf(1, "thread %d\n", i);
  }
  return 0;
}

int main() {
  const size_t stack_size = 1 << 20;
  void *stack = mmap(0, stack_size, PROT_READ | PROT_WRITE,
                     MAP_PRIVATE | MAP_ANONYMOUS | MAP_STACK, -1, 0);
  if (stack == MAP_FAILED) {
    perror("mmap");
    return 1;
  }

  int tid = 0;
  int flags = CLONE_VM | CLONE_FS | CLONE_FILES | CLONE_SIGHAND | CLONE_SYSVSEM |
              CLONE_THREAD | CLONE_PARENT_SETTID | CLONE_CHILD_CLEARTID;

  int rc = clone(thread_fn, (char *)stack + stack_size, flags, 0, &tid, 0, &tid);
  if (rc < 0) {
    perror("clone");
    return 1;
  }

  while (tid != 0) {
    futex_wait_int(&tid, tid);
  }

  munmap(stack, stack_size);
  return 0;
}

