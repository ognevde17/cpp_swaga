#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static long execve_syscall(const char *path, char *const argv[], char *const envp[]) {
  long ret;
  register long rax __asm__("rax") = 59;
  register const char *rdi __asm__("rdi") = path;
  register char *const *rsi __asm__("rsi") = argv;
  register char *const *rdx __asm__("rdx") = envp;
  __asm__ __volatile__("syscall"
                       : "=a"(ret)
                       : "a"(rax), "D"(rdi), "S"(rsi), "d"(rdx)
                       : "rcx", "r11", "memory");
  return ret;
}

int main() {
  char *argv[] = {(char *)"echo", (char *)"hello", 0};
  char *envp[] = {0};
  long r = execve_syscall("/bin/echo", argv, envp);
  dprintf(2, "execve failed: %s (%ld)\n", strerror(errno), r);
  return 1;
}

