#include <iostream>

#include "metaphysicl/dualnumberarray.h"

using namespace MetaPhysicL;
typedef double Real;

typedef DualNumber<Real, NumberArray<4, Real>> ADReal;
typedef DualNumber<ADReal, NumberArray<2, ADReal>> CompoundADType;

int
main(int argc, const char * argv[])
{
  ADReal u0 = 2;
  u0.derivatives()[0] = 1;
  ADReal u1 = 3;
  u1.derivatives()[1] = 1;
  ADReal v0 = 4;
  v0.derivatives()[2] = 1;
  ADReal v1 = 5;
  v1.derivatives()[3] = 1;

  ADReal u = 0.5 * (u0 + u1);
  ADReal v = 0.5 * (v0 + v1);

  std::cout << "u is: " << u.value() << std::endl;
  std::cout << "v is: " << v.value() << std::endl;

  const ADReal zero(0, 0);
  const ADReal one(1, 0);

  CompoundADType u_c(u, zero);
  auto & u_cd = u_c.derivatives();
  u_cd[0] = one;

  CompoundADType v_c(v, zero);
  auto & v_cd = v_c.derivatives();
  v_cd[1] = one;

  const auto f = u_c * v_c;
  const auto & f_d = f.derivatives();

  const auto & df_du_dual = f_d[0];
  const auto & df_dv_dual = f_d[1];

  std::cout << "df_du is: " << df_du_dual.value() << std::endl;
  std::cout << "df_dv is: " << df_dv_dual.value() << std::endl;

  for (std::size_t i = 0; i < 4; ++i)
    std::cout << "Derivative of df_du with respect to '" << std::to_string(i)
              << "' dof is: " << df_du_dual.derivatives()[i] << std::endl;
  for (std::size_t i = 0; i < 4; ++i)
    std::cout << "Derivative of df_dv with respect to '" << std::to_string(i)
              << "' dof is: " << df_dv_dual.derivatives()[i] << std::endl;

  return 0;
}
