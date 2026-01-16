#include <seccomp.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
  scmp_filter_ctx ctx = seccomp_init(SCMP_ACT_ALLOW);
  if (!ctx) return 1;
  if (seccomp_rule_add(ctx, SCMP_ACT_KILL, SCMP_SYS(getpid), 0) != 0) return 1;
  if (seccomp_load(ctx) != 0) return 1;
  seccomp_release(ctx);
  getpid();
  puts("unreachable");
  return 0;
}

