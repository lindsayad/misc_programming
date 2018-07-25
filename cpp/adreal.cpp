#include "libmesh/vector_value.h"
#include "metaphysicl/compare_types.h"
#include "metaphysicl/dualnumber.h"
#include "metaphysicl/dualnumber_decl.h"
#include "metaphysicl/numberarray.h"
#include <iostream>
#include <string>

class A {};

#define AD_MAX_DOFS_PER_ELEM 100
typedef MetaPhysicL::DualNumber<
    double, MetaPhysicL::NumberArray<AD_MAX_DOFS_PER_ELEM, double>>
    ADReal;

using namespace libMesh;
using namespace MetaPhysicL;

template <>
struct MetaPhysicL::MultipliesType<DualNumber<double, NumberArray<10, double>>,
                                   VectorValue<double>, false, void> {
  typedef VectorValue<DualNumber<double, NumberArray<10, double>>> supertype;
};

struct TypedefStruct {
  typedef std::string type;
};

// VectorValue<ADReal> operator*(const ADReal &a, const VectorValue<Real> &b) {
//   return VectorValue<ADReal>(b(0) * a, b(1) * a, b(2) * a);
// }

// VectorValue<ADReal> operator*(const VectorValue<Real> &b, const ADReal &a) {
//   return VectorValue<ADReal>(b(0) * a, b(1) * a, b(2) * a);
// }

template <typename T1, typename T2>
auto operator*(const VectorValue<T1> &vec, const T2 &scalar)
    -> VectorValue<decltype(vec(0) * scalar)> {
  return {vec(0) * scalar, vec(1) * scalar, vec(2) * scalar};
}

template <typename T1, typename T2>
auto operator*(const T2 &scalar, const VectorValue<T1> &vec)
    -> VectorValue<decltype(vec(0) * scalar)> {
  return {vec(0) * scalar, vec(1) * scalar, vec(2) * scalar};
}

// template <>
// inline typename MultipliesType<DualNumber<double, NumberArray<10, double>>,
//                                VectorValue<double>, false>::supertype
//     MetaPhysicL::operator*(DualNumber<double, NumberArray<10, double>> &&a,
//                            const VectorValue<double> &b) {
//   typedef typename MultipliesType<DualNumber<double, NumberArray<10,
//   double>>,
//                                   VectorValue<double>, false>::supertype DS;
//   DS returnval = std::move(a);
//   returnval *= b;
//   return returnval;
// }

// class MyInt {
// public:
//   MyInt(int i) : _i(i) {}

//   double operator*(double x) const { return x * this->i(); }

//   const int &i() const { return _i; }

// private:
//   int _i;
// };

// template <typename T, typename D> D operator*(T &a, D &b) {
//   return a.operator*(b)*10.;
// }

int main() {
  // ADReal x = 5.;
  // ADReal y = 7.;

  // x.derivatives()[0] = 1.;
  // y.derivatives()[1] = 1.;

  // auto f = 7. * x * x + 3. * y * y * y;
  // std::cout << f.value() << std::endl;
  // std::cout << f.derivatives()[0] << std::endl;
  // std::cout << f.derivatives()[1] << std::endl;

  VectorValue<double> vector(0, 1, 2);
  DualNumber<double, NumberArray<100, double>> dual_number = 10;
  VectorValue<ADReal> az = vector * dual_number;
  // MyInt b(7);
  // double c = 10;
  // auto bc = b.i() * c;
  // std::cout << bc << std::endl;
  // auto bc2 = operator*<MyInt, double>(b, c);
  // std::cout << bc2 << std::endl;

  typename MetaPhysicL::MultipliesType<
      DualNumber<double, NumberArray<10, double>>,
      VectorValue<double>>::supertype g;

  typename MetaPhysicL::boostcopy::enable_if<BuiltinTraits<double>,
                                             double>::type h;
  std::cout << typeid(h).name() << std::endl;

  // typename MetaPhysicL::boostcopy::enable_if<BuiltinTraits<A>, A>::type j; //
  // Error, A is not built-in!
}
