#include <sys/resource.h>
#include <iostream>


int main() {
    struct rlimit rl;
    int result;
    result = getrlimit(RLIMIT_STACK, &rl);
    //std::cout << rl.rlim_cur;
    rl.rlim_cur = 210 * 1024;
    std::cout << rl.rlim_max << "\n";
    result = setrlimit(RLIMIT_STACK, &rl);
    if (result != 0) {
        std::cerr << "FAILED\n";
        exit(1);
    }
    std::cout << "stack size is set to " << std::endl;
    struct rlimit rl2;
    result = getrlimit(RLIMIT_CPU, &rl2);
    rl2.rlim_cur = 1;
    result = setrlimit(RLIMIT_CPU, &rl2);
    while (true) {}
}