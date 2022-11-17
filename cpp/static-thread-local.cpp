#include <thread>
#include <iostream>

struct ADReal
{
  static thread_local bool do_derivatives;
};

thread_local bool ADReal::do_derivatives = true;

int
main()
{
  ADReal dual0;
  std::cout << dual0.do_derivatives << std::endl;
  bool & t0res = ADReal::do_derivatives;
  t0res = false;
  ADReal dual1;

  bool t1res;
  bool t2res;

  auto foo = [&t1res]() { t1res = ADReal::do_derivatives; };
  auto bar = [&t2res]() { t2res = ADReal::do_derivatives; };

  {
    std::thread t1(foo), t2(bar);
    t1.join();
    t2.join();
  }

  std::cout << ADReal::do_derivatives << std::endl;
  std::cout << dual0.do_derivatives << std::endl;
  std::cout << dual1.do_derivatives << std::endl;
  std::cout << t1res << std::endl;
  std::cout << t2res << std::endl;
}
