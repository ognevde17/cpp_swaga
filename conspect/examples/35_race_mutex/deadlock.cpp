#include <thread>
#include <mutex>
#include <vector>
#include <stdio.h>  
#include <unistd.h>
std::mutex mtx1, mtx2;

void thread1_func() {
    std::lock_guard<std::mutex> lock1(mtx1);  
    sleep(1);  
    std::lock_guard<std::mutex> lock2(mtx2);  
}

void thread2_func() {
    std::lock_guard<std::mutex> lock2(mtx2);  
    sleep(1);
    std::lock_guard<std::mutex> lock1(mtx1);
}

int main() {
    std::thread t1(thread1_func);
    std::thread t2(thread2_func);
    t1.join();
    t2.join();
    return 0;
}