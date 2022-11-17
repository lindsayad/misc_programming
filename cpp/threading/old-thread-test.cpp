#include <thread>
#include <atomic>
#include <mutex>

std::mutex cv_m;
std::atomic<bool> done = false;
int a;

void
fillContainer()
{
  bool local_done = done.load(std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_acquire);
  if (!local_done)
  {
    std::lock_guard<std::mutex> lock(cv_m);
    local_done = done.load(std::memory_order_relaxed);
    if (!local_done)
    {
      a = 0;
      local_done = true;
      std::atomic_thread_fence(std::memory_order_release);
      done.store(local_done, std::memory_order_relaxed);
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
