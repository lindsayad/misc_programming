#include <thread>
#include <atomic>
#include <mutex>

class Singleton
{
public:
  Singleton() = default;

  static Singleton * getInstance();

private:
  static std::atomic<Singleton *> m_instance;
  static std::mutex m_mutex;
};

std::atomic<Singleton *> Singleton::m_instance;
std::mutex Singleton::m_mutex;
int a;

Singleton *
Singleton::getInstance()
{
  Singleton * tmp = m_instance.load(std::memory_order_relaxed);
  std::atomic_thread_fence(std::memory_order_acquire);
  if (tmp == nullptr)
  {
    std::lock_guard<std::mutex> lock(m_mutex);
    tmp = m_instance.load(std::memory_order_relaxed);
    if (tmp == nullptr)
    {
      tmp = new Singleton;
      a = 5;
      std::atomic_thread_fence(std::memory_order_release);
      m_instance.store(tmp, std::memory_order_relaxed);
    }
  }

  if (tmp)
    const auto val = a;

  return tmp;
}

int
main()
{
  std::thread t1(Singleton::getInstance), t2(Singleton::getInstance), t3(Singleton::getInstance),
      t4(Singleton::getInstance), t5(Singleton::getInstance), t6(Singleton::getInstance),
      t7(Singleton::getInstance), t8(Singleton::getInstance);
  t1.join();
  t2.join();
  t3.join();
  t4.join();
  t5.join();
  t6.join();
  t7.join();
  t8.join();
}
