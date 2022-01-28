#include <thread>
#include <atomic>
#include <mutex>

std::mutex cv_m;
std::atomic<bool> done = false;
bool payload = false;

void
foo()
{
  const auto val = payload;

  if (!done.load(std::memory_order_acquire))
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
  std::thread t1(foo), t2(foo);
  t1.join();
  t2.join();
}
