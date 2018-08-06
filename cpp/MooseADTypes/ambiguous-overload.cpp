#include "MooseTypes.h"

#include <iostream>
#include <vector>

template <typename T> using vec = std::vector<T>;
typedef VectorValue<Real> RealVectorValue;
typedef TensorValue<Real> RealTensorValue;

// template <typename T> vec<T> operator*(const T &scalar, const vec<T> &vector)
// {
//   std::cout << "called overload 1\n";
//   vec<T> return_vec;
//   for (const auto &element : vector)
//     return_vec.push_back(scalar * element);
//   return return_vec;
// }

// template <typename T> vec<T> operator*(const vec<T> &vector, const T &scalar)
// {
//   std::cout << "called overload 2\n";
//   vec<T> return_vec;
//   for (const auto &element : vector)
//     return_vec.push_back(scalar * element);
//   return return_vec;
// }

int main() {
  // double x = 5;
  // std::vector<double> vec(10, 1);
  // operator*<double>(x *x, vec);
  // operator*<double>(vec, x);

  // VectorValueDN<Real> vector_dual_number;
  // VectorValue<Real> vector_value;
  // auto intermed = x * vector_value;

  // operator*<VectorValue, Real>(intermed, vector_dual_number);
  // operator*<VectorValue>(intermed, vector_dual_number);
  // operator*<>(intermed, vector_dual_number);
  // auto final = intermed * vector_dual_number;

  ScalarDN<Real> scalar_ad_prop;
  VectorDN<Real> vector_ad_prop;
  TensorDN<Real> tensor_ad_prop;
  Real scalar_reg_prop;
  VectorValue<Real> vector_reg_prop;
  TensorValue<Real> tensor_reg_prop;

  scalar_ad_prop = 1.;
  scalar_ad_prop *= scalar_ad_prop;
  scalar_ad_prop = scalar_ad_prop * scalar_ad_prop;

  vector_ad_prop = scalar_ad_prop * RealVectorValue(1., 1., 1.);
  auto intermed = vector_ad_prop * vector_ad_prop;
  scalar_ad_prop = intermed;
  vector_ad_prop *= 2.;
  vector_ad_prop = 2. * vector_ad_prop + vector_ad_prop * 2.;

  tensor_ad_prop =
      scalar_ad_prop * RealTensorValue(1., 1., 1., 1., 1., 1., 1., 1., 1.);

  vector_ad_prop = tensor_ad_prop * vector_ad_prop;

  NumberArray<AD_MAX_DOFS_PER_ELEM, TensorValue<Real>> d_tensor{
      RealTensorValue(1., 1., 1., 1., 1., 1., 1., 1., 1.)};
  NumberArray<AD_MAX_DOFS_PER_ELEM, VectorValue<Real>> d_vector{
      RealVectorValue(1., 1., 1.)};
  auto tensor_result = tensor_reg_prop * d_tensor;
  TypeTensor<Real> type_tensor_prop(tensor_reg_prop);
  type_tensor_prop *= type_tensor_prop;
  tensor_reg_prop *= tensor_reg_prop;
  auto tensor_result2 = d_tensor * tensor_reg_prop;

  tensor_ad_prop *= 2.;
  tensor_ad_prop *= tensor_ad_prop;
  tensor_ad_prop = tensor_ad_prop * tensor_ad_prop;
  tensor_ad_prop = 2. * tensor_ad_prop + tensor_ad_prop * 2.;
  tensor_ad_prop = 2. * tensor_ad_prop - tensor_ad_prop * 2.;

  scalar_reg_prop = scalar_ad_prop;
  vector_reg_prop = vector_ad_prop;
  tensor_reg_prop = tensor_ad_prop;
}