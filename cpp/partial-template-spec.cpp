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

template <typename T> class Vector {};

template <typename T> class Tensor {};

template <typename T> struct ScalarTraits { static const bool value = false; };

template <> struct ScalarTraits<double> { static const bool value = true; };

template <template <typename> class> struct VectorTraits {
  static const bool value = false;
};

template <> struct VectorTraits<Vector> { static const bool value = true; };

template <template <typename> class> struct TensorTraits {
  static const bool value = false;
};

template <> struct TensorTraits<Tensor> { static const bool value = true; };

class B {};

template <typename T, typename Enable = void> class DN {
public:
  DN() { std::cout << "I'm the general version!\n"; }
};

template <typename T>
class DN<T, typename std::enable_if<ScalarTraits<T>::value>::type> : public B {
public:
  DN() { std::cout << "Im the scalar version\n"; }
};

template <typename T, template <typename> class W>
class DN<W<T>, typename std::enable_if<TensorTraits<W>::value>::type> {
public:
  DN() { std::cout << "I'm the tensor version\n"; }

  void func();
};

template <typename T, template <typename> class W>
void DN<W<T>, typename std::enable_if<TensorTraits<W>::value>::type>::func() {}

template <typename T, template <typename> class W>
class DN<W<T>, typename std::enable_if<VectorTraits<W>::value>::type> {
public:
  DN() { std::cout << "I'm the vector version\n"; }
};

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
  // std::string e = "Hi";
  // double f = std::move(e); // error!

  void *void_thing = 0;
  DN<double> dn;
  DN<Vector<double>> vector_dn;
  DN<Tensor<double>> tensor_dn;
  DN<int> dn_int; // no definition
}
