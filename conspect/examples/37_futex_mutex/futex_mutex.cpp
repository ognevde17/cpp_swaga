#include <atomic>
#include <errno.h>
#include <linux/futex.h>
#include <stdint.h>
#include <sys/syscall.h>
#include <thread>
#include <unistd.h>

static int futex_wait(std::atomic<int> *addr, int expected) {
  return (int)syscall(SYS_futex, (int *)addr, FUTEX_WAIT, expected, 0, 0, 0);
}

static int futex_wake(std::atomic<int> *addr, int n) {
  return (int)syscall(SYS_futex, (int *)addr, FUTEX_WAKE, n, 0, 0, 0);
}

class FutexMutex {
 public:
  void lock() {
    int expected = 0;
    if (state.compare_exchange_strong(expected, 1, std::memory_order_acquire)) return;
    for (;;) {
      while (state.load(std::memory_order_relaxed) != 0) {
        futex_wait(&state, 1);
      }
      expected = 0;
      if (state.compare_exchange_strong(expected, 1, std::memory_order_acquire)) return;
    }
  }

  void unlock() {
    state.store(0, std::memory_order_release);
    futex_wake(&state, 1);
  }

 private:
  std::atomic<int> state{0};
};

int main() {
  FutexMutex m;
  long long x = 0;
  auto job = [&]() {
    for (int i = 0; i < 100000; ++i) {
      m.lock();
      x += 1;
      m.unlock();
    }
  };
  std::thread a(job);
  std::thread b(job);
  a.join();
  b.join();
  dprintf(1, "%lld\n", x);
  return 0;
}

