
#include <iostream>
#include <compare>

struct Base {
    void foo(int x) {
        std::cout << 1;
    }
};
struct Derived {
    void foo() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    d.foo(1);// error: too many arguments to function call, expected 0, have 1
}
