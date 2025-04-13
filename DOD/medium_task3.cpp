//in which string will be CE, 1, 2 or 3? 
class Granny {
 protected:
  int g;
  friend int main();
};
class Mom: private Granny { int m; };
class Son: public Mom {
 public:
  void f() {
    Granny granny; // 1
    std::cout << g; // 2
  }
};
Son s;
std::cout << s.m << s.g; // 3
