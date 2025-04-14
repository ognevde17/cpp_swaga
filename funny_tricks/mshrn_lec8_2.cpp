#include <iostream>
#include <vector>

int main() {
  std::vector<int> v(100);
  v[-1] = 500000; //what happend?
}
