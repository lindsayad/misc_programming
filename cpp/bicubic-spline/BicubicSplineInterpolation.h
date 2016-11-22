#ifndef SPLINEINTERPOLATION_H
#define SPLINEINTERPOLATION_H

#include <vector>
#include <fstream>
#include <sstream>
#include <string>

typedef double Real;
typedef std::vector<std::vector<Real> > matrix;

/**
 * This class interpolates tabulated functions with a bi-cubic
 *
 * Adopted from Numerical Recipes in C (section 3.6).
 */
class BicubicSplineInterpolation
{
public:
  BicubicSplineInterpolation();
  /**
   * If yp1, ypn are not specified or greater or equal that 1e30, we use natural spline
   */
  BicubicSplineInterpolation(const std::vector<double> & x1, const std::vector<double> & x2, const std::vector<double> & y, double yp1 = 1e30, double ypn = 1e30);

  virtual ~BicubicSplineInterpolation() = default;

  /**
   * Set the x-, y- values and first derivatives
   */
  void setData(const std::vector<double> & x1, const std::vector<double> & x2, const std::vector<double> & y, double yp1 = 1e30, double ypn = 1e30);

  void errorCheck();

  void calcCoeffs(std::vector<Real> & y, std::vector<Real> & y1, std::vector<Real> & y2, std::vector<Real> & y12, Real & d1, Real & d2, std::vector<std::vector<Real> > & coeffs);

protected:
  std::vector<double> _x1;
  std::vector<double> _x2;
  std::vector<double> _y;
  /// boundary conditions
  double _yp1, _ypn;
  /// second derivatives of the interpolating function: may not exist for bicubic interpolation
  std::vector<double> _y2;

  void solve();

  static int _file_number;
};

#endif //LINEARINTERPOLATION_H
