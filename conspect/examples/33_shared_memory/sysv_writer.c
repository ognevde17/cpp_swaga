#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <unistd.h>

int main(int argc, char **argv) {
  const char *msg = (argc == 2) ? argv[1] : "hello";
  key_t key = 1234;
  int shmid = shmget(key, 4096, IPC_CREAT | 0666);
  if (shmid < 0) {
    perror("shmget");
    return 1;
  }
  void *p = shmat(shmid, 0, 0);
  if (p == (void *)-1) {
    perror("shmat");
    return 1;
  }
  strncpy((char *)p, msg, 4095);
  ((char *)p)[4095] = 0;
  sleep(5);
  shmdt(p);
  return 0;
}

