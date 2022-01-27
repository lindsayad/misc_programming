#include <thread>
#include <vector>
#include <atomic>
#include <mutex>
#include <iostream>
#include <condition_variable>

int main()
{
  std::vector<int> container;
  std::mutex mx;
  std::mutex do_once_mx;
  std::condition_variable cv;
  std::atomic<bool> container_filled(false);

  auto get = [&container, &cv, &mx, &do_once_mx, &container_filled]()
    {
      {
        // _getArray
        if (!container_filled)
        {
          std::lock_guard<std::mutex> do_once(do_once_mx);
          if (!container_filled)
          {
            container = {1, 2, 3, 4};
            container_filled = true;
            cv.notify_all();
          }
        }
      }

      std::unique_lock<std::mutex> lock(mx);
      cv.wait(lock, [&container_filled](){ return container_filled.load(); });
      lock.unlock();
      container.front();
    };

  for (unsigned int i = 0; i < 1000; ++i)
  {
    {
      std::thread t1(get), t2(get), t3(get), t4(get), t5(get), t6(get), t7(get), t8(get);
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
    container_filled = false;
  }
}
