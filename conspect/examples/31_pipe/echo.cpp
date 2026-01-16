#include <unistd.h>
#include <sys/wait.h>
#include <stdio.h>

int main() {
    int fd[2];
    pipe(fd);

    pid_t pid1 = fork();
    if (pid1 == 0) {
        // Первый процесс: prog1
        close(fd[0]);                   // закрыть чтение
        dup2(fd[1], 1);                 // перенаправить stdout в pipe
        close(fd[1]);
        
        execlp("echo", "echo", "Hello World", NULL);
        perror("execlp");
        return 1;
    }

    pid_t pid2 = fork();
    if (pid2 == 0) {
        // Второй процесс: prog2
        close(fd[1]);                   // закрыть запись
        dup2(fd[0], 0);                 // перенаправить stdin в pipe
        close(fd[0]);

        execlp("wc", "wc", "-w", NULL);
        perror("execlp");
        return 1;
    }

    // Родитель закрывает оба конца
    close(fd[0]);
    close(fd[1]);

    // Подождать обоих детей
    waitpid(pid1, NULL, 0);
    waitpid(pid2, NULL, 0);
}