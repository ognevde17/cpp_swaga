#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main() {
  pid_t pid = fork();
  if (pid < 0) {
    perror("fork");
    return 1;
  }
  if (pid == 0) {
    char *argv[] = {(char *)"ls", (char *)"-l", 0};
    execvp("ls", argv);
    perror("execvp");
    _exit(1);
  }
  int status = 0;
  waitpid(pid, &status, 0);
  dprintf(1, "%d\n", status);
  return 0;
}

