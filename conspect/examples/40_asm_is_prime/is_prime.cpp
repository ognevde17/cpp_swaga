#include <iostream>

extern "C" int is_prime(int n);

int main() {
  int n;
  if (!(std::cin >> n)) return 1;
  std::cout << is_prime(n) << "\n";
  return 0;
}

