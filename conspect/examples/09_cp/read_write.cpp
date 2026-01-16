#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <unistd.h>
#include <iostream>
int main() {  
    int fd = open("./output.txt", O_WRONLY|O_CREAT);  
    int offset = lseek(fd, 50, SEEK_SET);  
    const char* buf = "Hello world";  
    int res = write(fd, buf, 10);  
    std::cout << res;  
    close(fd);
}