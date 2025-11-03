#include <iostream>

template <typename T>
class Base {
    public:
    void interface() {
        static_cast<T*>(this)->implementation();
    }
};

class Derived : public Base<Derived> {
    public:
    void implementation() {
        std::cout << "Derived implementation" << std::endl;
    }
};

int main() {
    Derived derived;
    derived.interface();
    return 0;
}
/*
    CRTP is a technique where a base class template is used to implement a polymorphic interface.
    The base class template is parameterized by the derived class, and the derived class is passed to the base class template.
    The base class template then calls the implementation method of the derived class.
    This is a compile-time polymorphism technique.
*/