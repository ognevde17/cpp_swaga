#include <unistd.h>
#include <fcntl.h>
#include <iostream>
int main();

extern "C" void my_start() {
    std::cout << "HU" << std::endl;
    int code = main();
    return;
}

int main() {
    int fd = open("/dev/random", O_RDONLY);
    char buffer[10];
    read(fd, buffer, 10);
    write(1, buffer, 10);
    close(fd);
    return 0;
}