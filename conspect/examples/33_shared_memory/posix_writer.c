// writer
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
  
#define SHM_SIZE 1024  // Размер разделяемой памяти  
  
int main() {  
  key_t key = 1234;  // Тот же ключ, что и в writer.c  
  
  // Получение сегмента разделяемой памяти, IPC_CREAT говорит, что нужно создать память
  int shmid = shmget(key, SHM_SIZE, IPC_CREAT | 0666);  
  if (shmid < 0) {  
    perror("shmget");  
    exit(1);  
  }  
  
  // Присоединение сегмента разделяемой памяти  
  char *data = (char *)shmat(shmid, NULL, 0);  
  if (data == (char *)(-1)) {  
    perror("shmat");  
    exit(1);  
  }  
  
  // Пишем в память из потока ввода  
  fgets(data, SHM_SIZE, stdin);  
  getchar();  
  
  shmdt(data);  
  
  return 0;  
}