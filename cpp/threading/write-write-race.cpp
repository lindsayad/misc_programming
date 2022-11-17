#include <thread>

int
main()
{
  int i = 5;

  auto foo = [&i]() { i = 2; };

  auto bar = [&i]() { i = 3; };

  std::thread t1(foo), t2(bar);

  t1.join();
  t2.join();
}
