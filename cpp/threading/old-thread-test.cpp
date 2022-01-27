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
  for (unsigned int i = 0; i < 1; ++i)
  {
    {
      std::thread t1(fillContainer), t2(fillContainer), t3(fillContainer), t4(fillContainer),
          t5(fillContainer), t6(fillContainer), t7(fillContainer), t8(fillContainer);
      t1.join();
      t2.join();
      t3.join();
      t4.join();
      t5.join();
      t6.join();
      t7.join();
      t8.join();
    }

    container.clear();
    done = false;
  }
}
