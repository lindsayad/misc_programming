#include <iostream>

#include "metaphysicl/dualnumberarray.h"

using namespace MetaPhysicL;
typedef double Real;

typedef DualNumber<Real, NumberArray<4, Real>> ADReal;
typedef DualNumber<ADReal, NumberArray<2, ADReal>> CompoundADType;

template <typename T>
std::pair<T, T>
makeZeroAndOne(const T & /*ex*/)
{
  return {T{0, 0}, T{1, 0}};
}

template <>
std::pair<Real, Real>
makeZeroAndOne(const Real & /*ex*/)
{
  return {Real{0}, Real{1}};
}

template <typename T, typename ADFunctor>
void
xyDerivatives(const T x, const T & y, T & z, T & dz_dx, T & dz_dy, const ADFunctor & z_from_x_y_ad)
{
  typedef DualNumber<T, NumberArray<2, T>> CompoundType;
  const auto [zero, one] = makeZeroAndOne(x);

  CompoundType x_c(x, zero);
  auto & x_cd = x_c.derivatives();
  x_cd[0] = one;
  CompoundType y_c(y, zero);
  auto & y_cd = y_c.derivatives();
  y_cd[1] = one;

  const auto z_c = z_from_x_y_ad(x_c, y_c);
  z = z_c.value();
  dz_dx = z_c.derivatives()[0];
  dz_dy = z_c.derivatives()[1];
}

template <typename T, typename Functor>
std::pair<T, T>
NewtonSolve(const T & x,
            const T & y,
            const Real z_initial_guess,
            const Real tolerance,
            const Functor & func,
            const unsigned int max_its = 100)
{
  std::function<bool(const T &, const T &)> abs_tol_check =
      [tolerance](const T & f, const T & /*y*/)
  { return MetaPhysicL::raw_value(std::abs(f)) < tolerance; };
  std::function<bool(const T &, const T &)> rel_tol_check = [tolerance](const T & f, const T & y)
  { return MetaPhysicL::raw_value(std::abs(f / y)) < tolerance; };
  auto convergence_check = MetaPhysicL::raw_value(y) == 0 ? abs_tol_check : rel_tol_check;

  T z = z_initial_guess, f, new_y, dy_dx, dy_dz;
  unsigned int iteration = 0;

  do
  {
    func(x, z, new_y, dy_dx, dy_dz);
    f = new_y - y;

    const bool converged = convergence_check(f, y);

    z += -(f / dy_dz);

    if (converged)
      break;
  } while (++iteration < max_its);

  return {z, dy_dz};
}

template <typename T>
T
rho_from_p_T(const T & pressure, const T & temperature)
{
  return pressure * pressure * temperature * temperature * temperature;
}

template <typename T>
void
rho_from_p_T(
    const T & pressure, const T & temperature, T & rho, T & drho_dpressure, T & drho_dtemperature)
{
  auto functor = [](const auto & pressure, const auto & temperature)
  { return rho_from_p_T(pressure, temperature); };
  xyDerivatives(pressure, temperature, rho, drho_dpressure, drho_dtemperature, functor);
}

template <typename T>
T
T_from_p_rho(const T & pressure, const T & rho)
{
  auto functor = [](const auto & pressure,
                    const auto & temperature,
                    auto & rho,
                    auto & drho_dpressure,
                    auto & drho_dtemperature)
  { rho_from_p_T(pressure, temperature, rho, drho_dpressure, drho_dtemperature); };
  return NewtonSolve(pressure, rho, 0.1, 1e-8, functor).first;
}

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

  ADReal p0 = 2;
  p0.derivatives()[0] = 1;
  ADReal p1 = 2;
  p1.derivatives()[1] = 1;
  ADReal rho0 = 32;
  rho0.derivatives()[2] = 1;
  ADReal rho1 = 32;
  rho1.derivatives()[3] = 1;

  const auto pressure = 0.5 * (p0 + p1);
  const auto rho = 0.5 * (rho0 + rho1);

  const auto temperature = T_from_p_rho(pressure, rho);

  return 0;
}
