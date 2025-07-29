#include <iostream>
struct S {
    int x = 0;
    int& ref_x = x;

    void foo(int p) const {
        ref_x = p;
    }
};

int main() {
    const S s;
    s.foo(10);
    std::cout << s.x;
}   
//WE COULD CHANGE CONST FIELD XDD
