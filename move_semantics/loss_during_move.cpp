#include <vector>
#include<iostream>
int main() {
  std::vector<int>a = {1, 2, 3};
  std::vector<int>& b = a;
  std::vector<int>& c = a;
  b = std::move(c);
  std::cout << a.size();
}
//we lost vector a((
