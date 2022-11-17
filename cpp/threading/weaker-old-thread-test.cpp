#include <thread>
#include <atomic>
#include <mutex>

std::mutex cv_m;
std::atomic<bool> done = false;
int a;

void
fillContainer()
{
  if (!done.load(std::memory_order_acquire))
  {
    std::lock_guard<std::mutex> lock(cv_m);
    if (!done.load(std::memory_order_relaxed))
    {
      a = 0;
      done.store(true, std::memory_order_release);
    }
  }

  const auto val = a;
}

int
main()
{
  std::thread t1(fillContainer), t2(fillContainer);
  t1.join();
  t2.join();
}
