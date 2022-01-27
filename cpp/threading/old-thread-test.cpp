#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <iostream>
#include <condition_variable>

std::mutex cv_m;
std::atomic<bool> done = false;
std::vector<int> container;

void
fillContainer()
{
  if (!done)
  {
    std::lock_guard<std::mutex> lock(cv_m);
    if (!done)
    {
      container = {1, 2, 3, 4};
      done = true;
    }
  }

  container.front();
}

int
main()
{
  std::thread t1(fillContainer), t2(fillContainer);
  t1.join();
  t2.join();
}
