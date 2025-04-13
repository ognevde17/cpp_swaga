#include <iostream>

struct Base {
  virtual int foo() = 0;
};

int Base::foo() {
  return 5
}

struct Derived: Base {};

int main() {
  Derived d;
  std::cout << d.foo();
}
