#include <iostream>

union a {
  int32_t first;
  int64_t second;
};

int main(){
  a b;
  std::cout << sizeof(b); // Что выведет?
}
