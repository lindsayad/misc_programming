#include "newton.h"
#include <vector>
#include <iostream>

int main()
{
  const double u_i = 1;
  const double e_i = 10;
  const double ht_i = 2 * e_i + 0.5 * u_i * u_i;
  auto cfd_resid = [e_i, ht_i](std::vector<ADReal> & residuals, const std::vector<Real> & u)
                     {
                       ADReal rho = u[0];
                       rho.derivatives().insert(0) = 1;
                       ADReal vel = u[1];
                       vel.derivatives().insert(1) = 1;
                       ADReal e = u[2];
                       e.derivatives().insert(2) = 1;


                       residuals[0] = rho * vel - 2.;
                       residuals[1] = vel + rho * e - (1. + e_i);
                       residuals[2] = 2. * e + 0.5 * vel * vel - ht_i;
                     };

  auto no_pressure_resid = [e_i, ht_i](std::vector<ADReal> & residuals, const std::vector<Real> & u)
                     {
                       ADReal rho = u[0];
                       rho.derivatives().insert(0) = 1;
                       ADReal vel = u[1];
                       vel.derivatives().insert(1) = 1;
                       ADReal e = u[2];
                       e.derivatives().insert(2) = 1;


                       residuals[0] = rho * vel - 2.;
                       residuals[1] = vel - 1.;
                       residuals[2] = 2. * e + 0.5 * vel * vel - ht_i;
                     };

  // u
  std::vector<double> soln = {{1., 1., 1.}};

  newton(cfd_resid, soln);

  for (const auto comp : soln)
    std::cout << comp << std::endl;

  newton(no_pressure_resid, soln);

  for (const auto comp : soln)
    std::cout << comp << std::endl;

  return 0;
}
