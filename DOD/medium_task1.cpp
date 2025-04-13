#include <iostream>
int& f(int x) {
  return x * x;
}
int main() {
    std::cout << f(5);
}
