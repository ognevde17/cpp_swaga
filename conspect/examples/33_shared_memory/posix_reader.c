// reader
#include <stdio.h>  
#include <stdlib.h>  
#include <sys/ipc.h>  
#include <sys/shm.h>  
  
#define SHM_SIZE 1024  // Размер разделяемой памяти  
  
int main() {  
  key_t key = 1234;  // Тот же ключ, что и в writer.c  
  
  // Получение сегмента разделяемой памяти
  int shmid = shmget(key, SHM_SIZE, 0666);  
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
  
  // Чтение из разделяемой памяти  
  printf("Прочитано сообщение: %s", data);  
  
  // Отсоединение от разделяемой памяти  
  shmdt(data);  
  
  // Удаление сегмента памяти  
  shmctl(shmid, IPC_RMID, NULL);  
  
  return 0;  
}