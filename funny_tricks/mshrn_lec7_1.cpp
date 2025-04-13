void f() {
  int* p = new int(5);
  int* pp = new int(6);
  delete p, pp; //what happened?
  delete (p, pp); //what happend?
}
