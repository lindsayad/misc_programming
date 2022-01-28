#include <thread>
#include <atomic>
#include <mutex>
#include <cassert>

std::mutex cv_m;
std::atomic<bool> array_is_present = false;
bool values_read_only = false;

int
fib(int n)
{
  if (n <= 1)
    return n;
  return fib(n - 1) + fib(n - 2);
}

void
getArray(const int thread_id)
{
  const bool initially_array_is_present = array_is_present.load(std::memory_order_acquire);
  assert(!initially_array_is_present);

  // Make thread 1 wait longer, but make both threads wait such that initially_array_is_present
  // should be false for both
  if (thread_id)
    fib(31);
  else
    fib(30);

  if (initially_array_is_present)
    const auto value = values_read_only;

  if (!initially_array_is_present)
  {
    std::lock_guard<std::mutex> lock(cv_m);
    if (!array_is_present.load(std::memory_order_relaxed))
    {
      values_read_only = true;
      array_is_present.store(true, std::memory_order_release);
    }
  }

  const auto val = values_read_only;
}

int
main()
{
  std::thread t0(getArray, 0), t1(getArray, 1);
  t0.join();
  t1.join();
}
