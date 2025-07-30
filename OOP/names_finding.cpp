#include <iostream>
struct Granny:
    int x = 1;
    void f() {
        std::cout << x;
    }
};

struct Mom: Granny {
    int x = 2;
};

int main() {

    Mom m;
    m.f();//выведется 1, потому что функция не виртуальная, соответственно после того как компилятор нашёл имя функции в родителе, он будет там же искать и имя поля

}
