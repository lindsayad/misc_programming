#include <iostream>
#include <ostream>
#include <vector>

int main() {
  std::vector<double> v(10, 1);
  std::ostream myout(std::cout.rdbuf());
  // myout.write((char *)&v.size(), sizeof(v.size()));
  myout.write((char *)&v[0], sizeof(v[0]));
  auto size = v.size();
  myout.write((char *)&size, sizeof(size));
  myout.write((char *)&size, sizeof(size));
}
