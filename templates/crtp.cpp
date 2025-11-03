#include <iostream>
#include <vector>
#include <type_traits>

// Простой пример CRTP
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

