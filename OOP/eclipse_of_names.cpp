
#include <iostream>
#include <compare>

struct Base {
    void foo(int x) {
        std::cout << 1;
    }
};
struct Derived : Base {
    void foo() {
        std::cout << 2;
    }
};

int main() {
    Derived d;
    d.foo(1);
}
