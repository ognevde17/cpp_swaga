#include <thread>
#include <mutex>
#include <vector>
#include <stdio.h>

int counter = 0;
std::mutex mtx; 

void increment() {
    for (int i = 0; i < 100000; ++i) {
        //mtx.lock();            
        counter++;              
        //mtx.unlock();           
    }
}

int main() {
    std::vector<std::thread> threads;
    
    for (int i = 0; i < 10; ++i) {
        threads.emplace_back(increment);
    }
    
    for (auto &t : threads) {
        t.join();
    }
    
    printf("Result: %d (expected 1000000)\n", counter);
    
    return 0;
}