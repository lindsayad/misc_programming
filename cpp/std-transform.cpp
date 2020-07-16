#include <algorithm>
#include <cmath>
#include <functional>
#include <iostream>
#include <vector>

int main() {
  std::function<double(double)> fn = static_cast<double (*)(double)>(&std::abs);

  std::vector<double> vec = {1, -1};

  std::transform(vec.cbegin(), vec.cend(), vec.begin(), fn);

  for (const auto elem : vec)
    std::cout << elem << std::endl;
}
