#include <iostream>

std::size_t Fibonacci(std::size_t n) {
  if (n == 1)
    return 0;
  else if (n == 2)
    return 1;
  else
    return Fibonacci(n - 1) + Fibonacci(n - 2);
}

int main() {
  Fibonacci(47);
  double x = 0.175781;
  std::cout << x << std::endl;
}
