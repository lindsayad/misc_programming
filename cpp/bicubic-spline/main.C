#include "BicubicSplineInterpolation.h"
#include "SplineInterpolation.h"
#include <math.h>
#include <iostream>
#include <iomanip>

int main()
{
  std::vector<Real> x1;
  std::vector<Real> x2;
  Real min = -5, max = 5, step = 2;

  for (Real val = min; val <= max; val += step)
  {
    x1.push_back(val);
    x2.push_back(val);
  }

  int m = x1.size();
  int n = x2.size();
  std::vector<std::vector<Real> > y(m, std::vector<Real>(n));

  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      y[i][j] = std::sin(std::pow(x1[i], 2) + std::pow(x2[j], 2));
      std::cout << std::setprecision(3) << y[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;

  BicubicSplineInterpolation bsi;
  bsi.setData(x1, x2, y);

  std::vector<Real> x1new, x2new;
  Real step_new = 1;
  for (Real val = min; val <= max; val += step_new)
  {
    x1new.push_back(val);
    x2new.push_back(val);
  }

  m = x1new.size(), n = x2new.size();
  std::vector<std::vector<Real> > ynew(m, std::vector<Real>(n));

  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      ynew[i][j] = bsi.sample(x1new[i], x2new[j]);
      std::cout << std::setprecision(3) << ynew[i][j] << " ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
  for (int i = 0; i < m; ++i)
  {
    for (int j = 0; j < n; ++j)
    {
      std::cout << std::setprecision(3) << std::sin(std::pow(x1new[i], 2) + std::pow(x2new[j], 2)) << " ";
    }
    std::cout << std::endl;
  }

}
