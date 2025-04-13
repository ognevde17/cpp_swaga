int main() {
  int x = 0;
  int b = 0;
  decltype(++x) y = x;
  decltype(x++) z = b;
  //type y = ?
  //type z = ?
}
