#include <iostream>
#
extern "C" int asm_if_abs(int x);
extern "C" int asm_while_sum(int n);
extern "C" int asm_for_count(int n);
#
int main() {
  int x, n;
  std::cout << "x n: ";
  if (!(std::cin >> x >> n)) return 1;
#
  std::cout << "abs(x) = " << asm_if_abs(x) << "\n";
  std::cout << "sum_while(n) = " << asm_while_sum(n) << "\n";
  std::cout << "count_for(n) = " << asm_for_count(n) << "\n";
  return 0;
}

