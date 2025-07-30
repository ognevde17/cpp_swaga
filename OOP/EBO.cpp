//EBO - emphty base optimization

#include <iostream>
struct Granny{
    void f() {
        std::cout << 1;
    }
};
struct Mom : Granny{
    int x;
    void f2() {
        std::cout << 1;
    }
};
struct Other {
};
int main() {
    Mom m;
    std::cout << sizeof(m);//sizeof равен 4 байтам, потому что granny оптимизируется до 0 байт и хранится только один инт
    Other o;
    std::cout << sizeof(o);//sizeof равен 1 байту, потому что объект в плюсах должен весть минимум 1 байт, даже если это пустая структура.
}
