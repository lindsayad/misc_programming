#include <iostream>
#include <map>

class A {
public:
  double &give_me_double(unsigned i, const double &d) {
    return my_map.emplace(i, d).first->second;
  }

protected:
  std::map<unsigned, double> my_map;
};

int main() {

  A a;

  std::cout << a.give_me_double(0, 5) << std::endl;
}
