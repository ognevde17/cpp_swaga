#include <iostream>

struct Base {
    protected:
    void f(double) {
        std::cout << 1;
    }
    void g(double) {
        std::cout << 3;
    }
};
struct Derived : Base {
    using Base::f;
    int f(int) {
        std::cout << 2;
        return 0;
    }
};
int main() {
    Derived d;
    d.f(0.0);//OK, мы юзингом в публичной секции наследника разрешили доступ к методу родителя извне
    d.g(0.0);//CE, g() протектед метод в Derived, вызвать извне нельзя
}
