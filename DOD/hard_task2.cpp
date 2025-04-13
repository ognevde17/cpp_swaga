#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_set>
#include <vector>
template <typename T>
struct Debug { //just for answer demo
  Debug(T) = delete;
};
int main() {
  int x = 0;
  int& y = x;
  const decltype(y) z = y; // what type of z?
  Debug<decltype(z)>();//just for answer demo
}
