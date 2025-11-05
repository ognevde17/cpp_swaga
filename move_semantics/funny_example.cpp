#include <iostream>
template <typename T>
class Optional {
    public:
    Optional() = default;
    Optional (const Optional& other) {
        std::cout << "A";
    }
    template <typename U>
    Optional (Optional<U>&& other) {
        std::cout << "B";
    }
    template <typename U>
    Optional (U&& other) {
        std::cout << "C";
    }
};
int main() {
    Optional<int> a;
    Optional<int> b = a;
}