#include <unistd.h>  
#include <cstdlib>  
#include <string>  
  
int main() {  
  char buffer[100];  
  auto taken = read(0, buffer, 100);  
  if (taken == -1) {  
    auto errno_str = std::to_string(errno);  
    write(2, errno_str.data(), errno_str.size());  
    exit(1);  
  }
  if (write(1, buffer, taken) == -1) {  
    auto errno_str = std::to_string(errno);  
    write(2, errno_str.data(), errno_str.size());  
    exit(1);  
  }  
}