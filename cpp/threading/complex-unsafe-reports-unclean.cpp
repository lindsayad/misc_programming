#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>

std::mutex cv_m;
std::atomic<bool> done = false;
bool payload = false;

int
fib(int n)
{
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

void
foo(const int thread_id)
{
  const bool initially_done = done.load(std::memory_order_acquire);
  assert(!initially_done);

  // Make thread 1 wait longer, but make both threads wait such that initially_done should be
  // false for both
  if (thread_id)
    fib(31);
  else
    fib(30);

  const auto val = payload;

  if (!initially_done)
  {
    std::lock_guard<std::mutex> lock(cv_m);
    if (!done.load(std::memory_order_relaxed))
    {
      payload = true;
      done.store(true, std::memory_order_release);
    }
  }
}

int
main()
{
  std::thread t1(foo, 0), t2(foo, 1);
  t1.join();
  t2.join();
}
