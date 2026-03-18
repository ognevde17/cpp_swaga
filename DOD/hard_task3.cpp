#include <iostream>

struct base {};

struct a : base {
  int first;
  long long second;
  char third;	
};

struct b {
  long long first;
  int second;
  char third;
};

int main() {
  std::cout << sizeof(base) << '\n';
  std::cout << sizeof(a) << '\n';
  std::cout << sizeof(b) << '\n';
}
