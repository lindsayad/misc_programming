#include <iostream>
#include <type_traits>

struct A {};
struct B {};

template <typename T> struct Foo {
  template <typename U = T>
  typename std::enable_if<std::is_same<U, A>::value>::type bar() {
    std::cout << "I'm an A!" << std::endl;
  }

  template <typename U = T>
  typename std::enable_if<std::is_same<U, B>::value>::type bar() {
    std::cout << "I'm a B!" << std::endl;
  }
};

// // As template parameter
// template <typename T,
//           typename std::enable_if<std::is_same<T, int>::value, T>::type = 0>
// void print_things(void * = 0) {
//   std::cout << "This is the 'specialization'" << std::endl;
// }

// As parameter
template <typename T>
void print_things(
    typename std::enable_if<std::is_same<T, int>::value>::type * = 0) {
  std::cout << "This is the 'specialization'" << std::endl;
}

// template <typename T> void print_things(...) {
//   std::cout << "This is the main" << std::endl;
// }

template <typename T> void print_things() {
  std::cout << "This is the main" << std::endl;
}

template <typename T> void print_type_info(T /*t*/) {
  std::cout
      << typeid(typename std::enable_if<std::is_same<T, int>::value, T>::type)
             .name()
      << std::endl;
}

int main() {
  Foo<A> a;
  Foo<B> b;
  a.bar();
  b.bar();

  print_things<double>();
  print_things<int>();
  // print_things<int>(std::string());

  std::cout << std::is_same<int, int>::value << std::endl;
  print_type_info(int());
  // print_type_info(double()); Error
}
