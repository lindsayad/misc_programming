#ifndef BICUBICSPLINEINTERPOLATION_H
#define BICUBICSPLINEINTERPOLATION_H

#include "SplineInterpolationBase.h"
#include <fstream>
#include <sstream>
#include <string>

typedef std::vector<std::vector<Real> > matrix;

/**
 * This class interpolates tabulated functions with a bi-cubic
 *
 * Adopted from Numerical Recipes in C (section 3.6).
 */
class BicubicSplineInterpolation : SplineInterpolationBase
{
public:
  BicubicSplineInterpolation();
  /**
   * If yp1, ypn are not specified or greater or equal that 1e30, we use natural spline
   */
  BicubicSplineInterpolation(const std::vector<Real> & x1, const std::vector<Real> & x2, const std::vector<std::vector<Real> > & y, Real yp1 = 1e30, Real ypn = 1e30);

  virtual ~BicubicSplineInterpolation() = default;

  /**
   * Set the x-, y- values and first derivatives
   */
  void setData(const std::vector<Real> & x1, const std::vector<Real> & x2, const std::vector<std::vector<Real> > & y, Real yp1 = 1e30, Real ypn = 1e30);

  void errorCheck();

  void calcCoeffs(std::vector<Real> & y, std::vector<Real> & y1, std::vector<Real> & y2, std::vector<Real> & y12, Real & d1, Real & d2, std::vector<std::vector<Real> > & coeffs);

  void interpolate(std::vector<Real> & y, std::vector<Real> & y1, std::vector<Real> & y2, std::vector<Real> & y12, Real & x1l, Real & x1u, Real & x2l, Real & x2u, Real & x1, Real & x2, Real & ansy, Real & ansy1, Real & ansy2);

protected:
  std::vector<Real> _x1;
  std::vector<Real> _x2;
  std::vector<std::vector<Real> > _y;
  /// boundary conditions
  Real _yp1, _ypn;
  /// Second derivatives
  std::vector<std::vector<Real> > _y2;

  void precomputeAuxSecondDerivativeTable();
  void solve();

  static int _file_number;
};

#endif //LINEARINTERPOLATION_H
