#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>

int main() {
  int x = 0;
  int b = 0;
  std::cout << &x - &b << "\n";//1
  std::cout << (long long)&x - (long long)&b;//2
  //1 = ?
  //2 = ?
  //why
}
