#include <iostream>

template <typename T, typename D> struct DualNumber {};

template <typename T, typename T2> struct CompareTypes {
  CompareTypes() { std::cout << "generic\n"; }
};

template <typename T, typename T2, typename D>
struct CompareTypes<T, DualNumber<T2, D>> {
  CompareTypes() { std::cout << "spec1\n"; }
};
template <typename T, typename D, typename T2>
struct CompareTypes<DualNumber<T, D>, T2> {
  CompareTypes() { std::cout << "spec2\n"; }
};
template <typename T, typename D, typename T2, typename D2>
struct CompareTypes<DualNumber<T, D>, DualNumber<T2, D2>> {
  CompareTypes() { std::cout << "spec3\n"; }
};
template <typename T> struct CompareTypes<T, T> {
  CompareTypes() { std::cout << "spec4\n"; }
};
template <typename T, typename D>
struct CompareTypes<DualNumber<T, D>, DualNumber<T, D>> {
  CompareTypes() { std::cout << "spec5\n"; }
};

int main() {
  CompareTypes<DualNumber<double, double>, DualNumber<double, double>> ct;
}
