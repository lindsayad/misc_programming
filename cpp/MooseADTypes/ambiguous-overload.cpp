#include "MooseTypes.h"

#include <iostream>
#include <vector>

template <typename T>
using vec = std::vector<T>;
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

PerfLog Moose::perf_log("MooseADTypes");

void
do_nothing(const TypeVector<Real> &)
{
}

class A
{
};

class B : public A
{
};

void
do_nothing(const A &)
{
}

int
main()
{
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

  scalar_ad_prop = 1.;
  scalar_ad_prop *= scalar_ad_prop;
  scalar_ad_prop = scalar_ad_prop * scalar_ad_prop;

  vector_ad_prop = scalar_ad_prop * RealVectorValue(1., 1., 1.);
  auto intermed = vector_ad_prop * vector_ad_prop;
  scalar_ad_prop = intermed;
  vector_ad_prop *= 2.;
  vector_ad_prop = 2. * vector_ad_prop + vector_ad_prop * 2.;

  tensor_ad_prop = scalar_ad_prop * RealTensorValue(1., 1., 1., 1., 1., 1., 1., 1., 1.);

  vector_ad_prop = tensor_ad_prop * vector_ad_prop;

  tensor_ad_prop *= 2.;
  tensor_ad_prop *= tensor_ad_prop;
  tensor_ad_prop = tensor_ad_prop * tensor_ad_prop;
  tensor_ad_prop = 2. * tensor_ad_prop + tensor_ad_prop * 2.;
  tensor_ad_prop = 2. * tensor_ad_prop - tensor_ad_prop * 2.;

  Real scalar_reg_prop(scalar_ad_prop);
  VectorValue<Real> vector_reg_prop(vector_ad_prop);
  TensorValue<Real> tensor_reg_prop(tensor_ad_prop);
  ADRankTwoTensor ad_rnk2_tensor;
  RankTwoTensor rnk2_tensor(ad_rnk2_tensor);

  ad_rnk2_tensor(0, 0);
  const ADRankTwoTensor const_rnk2;
  const_rnk2(0, 0);

  std::vector<Real> eigvals;
  RankTwoTensor eigvecs;
  ad_rnk2_tensor.symmetricEigenvaluesEigenvectors(eigvals, eigvecs);

  RealTensorValue rot;
  ADRankFourTensor ad_rnk4;
  ad_rnk4.rotate(rot);

  B b;
  do_nothing(b);

  // scalar_reg_prop = scalar_ad_prop;
  // vector_reg_prop = vector_ad_prop;
  // tensor_reg_prop = tensor_ad_prop;
}
