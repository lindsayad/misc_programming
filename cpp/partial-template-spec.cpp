#include <iostream>
#include <utility>

template <typename T, typename T2> class A {
public:
  void print_info() {
    std::cout << "I'm from the primary template!" << std::endl;
  }
};

template <typename T> class A<T &, T> {
public:
  void print_info() { std::cout << "I'm partially specialized!" << std::endl; }
};

template <typename T> T return_value(T x) {
  std::cout << "general\n";
  return x;
}

// Error because specialization doesn't match primary template!
// template <> double return_value<int>(int x) {
//   std::cout << "special\n";
//   return x;
// }

template <typename T, typename T2, typename T3>
void my_function(T t, T2 t2, T3 t3) {
  std::cout << "I'm the main" << std::endl;
}

template <> void my_function(int t, double t2, float t3) {
  std::cout << "I'm specd\n";
}

int main() {
  int x = 5;
  int &y = x;
  A<decltype(x), decltype(x)> a;
  a.print_info();
  A<decltype(y), decltype(x)> b;
  b.print_info();

  double c = return_value(5.);
  double d = return_value<int>(5);

  my_function(float(), double(), float());
  my_function(int(), double(), float());
  std::string e = "Hi";
  double f = std::move(e);
}
