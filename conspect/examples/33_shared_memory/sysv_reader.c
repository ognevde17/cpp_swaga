#include <stdio.h>
#include <sys/ipc.h>
#include <sys/shm.h>

int main() {
  key_t key = 1234;
  int shmid = shmget(key, 4096, 0666);
  if (shmid < 0) {
    perror("shmget");
    return 1;
  }
  void *p = shmat(shmid, 0, 0);
  if (p == (void *)-1) {
    perror("shmat");
    return 1;
  }
  dprintf(1, "%s\n", (char *)p);
  shmdt(p);
  shmctl(shmid, IPC_RMID, 0);
  return 0;
}

