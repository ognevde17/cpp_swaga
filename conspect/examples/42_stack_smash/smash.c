#include <stdio.h>

static void f() {
  char buf[10];
  scanf("%s", buf);
}

int main() {
  f();
  return 0;
}

