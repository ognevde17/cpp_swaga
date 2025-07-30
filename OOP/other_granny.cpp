#include <iostream>
struct Granny{
    int x; 
};
struct Mom : private Granny{
    int x;
    friend int main();
};
struct Son : Mom {
    int x;
    void f(Granny& g) {//CE, компилятор думает что имя бабушка для нас не доступно из-за приватности наследования.
      //Для того чтобы компилять понял что мы имеем ввиду не нашу бабушку(про которую мы не знаем, что она наша), а просто рандомную чужую бабушку, нужно написать void f(::Granny& g)
        std::cout << g.x;
    }
};
int main() {

}
