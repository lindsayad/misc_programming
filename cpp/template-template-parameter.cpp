#include <iostream>
#include <vector>

template <typename T, template <typename> class W>
void my_template(const W<T> & /*arg*/) {
  std::cout << "primary\n";
}

template <typename T> class A {};

// Error because A<double> does not match double, e.g. we're applying A<double>
// to the first template parameter from the explicit template argument list, but
// the deduction from the function parameter is double
// template <> void my_template<A<double>>(const A<double> & /*arg*/) {
//   std::cout << "secondary\n";
// }

template <> void my_template(const A<double> & /*arg*/) {
  std::cout << "secondary\n";
}

int main() {
  A<double> a;
  A<int> a2;
  // std::vector<double> v1;
  // std::vector<int> v2;
  my_template(a);
  my_template(a2);
  // my_template(v1);
  // my_template(v2);
}
