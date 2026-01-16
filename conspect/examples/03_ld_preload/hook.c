#define _GNU_SOURCE
#include <dlfcn.h>
#include <stdio.h>

int puts(const char *s) {
  static int (*real_puts)(const char *) = 0;
  if (!real_puts) real_puts = (int (*)(const char *))dlsym(RTLD_NEXT, "puts");
  real_puts("hooked");
  return real_puts(s);
}

