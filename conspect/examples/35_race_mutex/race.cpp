#include <thread>
#include <vector>

static std::vector<int> v;

static void job() {
  for (int i = 0; i < 200000; ++i) v.push_back(i);
}

int main() {
  std::thread t(job);
  job();
  t.join();
  return 0;
}

