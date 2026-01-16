#include <unistd.h>  
#include <string.h>  
#include <sys/wait.h>  
#include <stdlib.h>  
#include <signal.h>  
#include <iostream>  
  
void handle(int signum) {  
  std::cout << "caught " << signum << std::endl;  
}  
  
int main(int argc, char* argv[]) {  
  int pipefd[2];  
  pipe(pipefd);  
  signal(SIGPIPE, &handle);  
  int cpid = fork();  
  if (cpid == 0) {  
    close(pipefd[1]);  
    close(pipefd[0]);
    _exit(0);  
  } else {  
    close(pipefd[0]);  
    sleep(1);  
    write(pipefd[1], argv[1], strlen(argv[1]));  
    close(pipefd[1]);  
    wait(NULL);  
    exit(0);  
  }  
}