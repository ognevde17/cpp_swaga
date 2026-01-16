#include <iostream>
#include <thread>
void job() {  
    std::vector<int> v; 
    for (int i = 0; i < 100000; ++i) {  
      v.push_back(i);  
    }  
  }  
    
  int main() {  
    std::thread t(job);  
    job();
    t.join();  
  }