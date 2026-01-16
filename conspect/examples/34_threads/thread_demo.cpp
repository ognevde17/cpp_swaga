#include <iostream>
#include <thread>

static void job(char c) {
  for (int i = 0; i < 200000; ++i) std::cout << c;
}

int main() {
  std::thread t(job, 'a');
  job('b');
  t.join();
  std::cout << "\n";
  return 0;
}

