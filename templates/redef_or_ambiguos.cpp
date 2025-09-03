#include <iostream>
#include <vector>
template <typename T>
void foo(T a) {
    std::cout << 1;
}
template <typename T>
void foo(T a) {
    std::cout << 2;
}
//CE in this case, redefinition of foo

template <typename T>
void foo(T a) {
    std::cout << 1;
}
template <typename T>
int foo(T a) {
    std::cout << 2;
    return 0;
}
//not CE in this case, different return type, but if we use foo(1) we will get CE, ambiguous call
int main() {
    
}
