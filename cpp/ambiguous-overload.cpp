#include "MooseADTypes.h"

#include <iostream>
#include <vector>

template <typename T> using vec = std::vector<T>;

template <typename T> vec<T> operator*(const T &scalar, const vec<T> &vector) {
  std::cout << "called overload 1\n";
  vec<T> return_vec;
  for (const auto &element : vector)
    return_vec.push_back(scalar * element);
  return return_vec;
}

template <typename T> vec<T> operator*(const vec<T> &vector, const T &scalar) {
  std::cout << "called overload 2\n";
  vec<T> return_vec;
  for (const auto &element : vector)
    return_vec.push_back(scalar * element);
  return return_vec;
}

int main() {
  double x = 5;
  std::vector<double> vec(10, 1);
  operator*<double>(x *x, vec);
  operator*<double>(vec, x);

  VectorValueDN<Real> vector_dual_number;
  VectorValue<Real> vector_value;
  auto intermed = x * vector_value;

  operator*<VectorValue, Real>(intermed, vector_dual_number);
  operator*<VectorValue>(intermed, vector_dual_number);
  operator*<>(intermed, vector_dual_number);
  auto final = intermed * vector_dual_number;
}
