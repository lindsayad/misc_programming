#include <iostream>

template <typename T> struct RawValue {
  static void foo() { std::cout << "I'm the primary template\n"; }
};

template <typename T> struct RealTraits { static const bool value = false; };

template <> struct RealTraits<double> { static const bool value = true; };

template <typename> struct TypeVector {};

template <typename T>
struct RawValue<
    typename std::enable_if<RealTraits<T>::value, TypeVector<T>>::type> {
  static void foo() { std::cout << "Im the vector real template\n"; }
};

template <typename T>
struct RawValue<
    typename std::enable_if<!RealTraits<T>::value, TypeVector<T>>::type> {
  static void foo() { std::cout << "Im the vector non-real template\n"; }
};

int main() {
  RawValue<double>::foo();
  RawValue<TypeVector<double>>::foo();
  RawValue<TypeVector<int>>::foo();
}
