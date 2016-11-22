#include "BicubicSplineInterpolation.h"
#include <assert.h>

int BicubicSplineInterpolation::_file_number = 0;

BicubicSplineInterpolation::BicubicSplineInterpolation()
{
}

BicubicSplineInterpolation::BicubicSplineInterpolation(const std::vector<double> & x1, const std::vector<double> & x2, const std::vector<double> & y, double yp1/* = 1e30*/, double ypn/* = 1e30*/) :
    _x1(x1),
    _x2(x2),
    _y(y),
    _yp1(yp1),
    _ypn(ypn)
{
  errorCheck();
  solve();
}

void
BicubicSplineInterpolation::setData(const std::vector<double> & x1, const std::vector<double> & x2, const std::vector<double> & y, double yp1/* = 1e30*/, double ypn/* = 1e30*/)
{
  _x1 = x1;
  _x2 = x2;
  _y = y;
  _yp1 = yp1;
  _ypn = ypn;
  errorCheck();
  solve();
}

void
BicubicSplineInterpolation::errorCheck()
{
  if (_x1.size() != _x2.size() != _y.size())
    std::perror("BicubicSplineInterpolation: vectors are not the same length");
}

void
BicubicSplineInterpolation::calcCoeffs(std::vector<Real> & y, std::vector<Real> & y1, std::vector<Real> & y2, std::vector<Real> & y12, Real & d1, Real & d2, std::vector<std::vector<Real> > & coeffs)
{
  static matrix Ainv = {
    { 1,  2,  3,  4,  5,  6,  7,  8,  9, 10, 11, 12, 13, 14, 15, 16},
    { 1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 2, -2,  0,  0,  1,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  0,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0, -3,  3,  0,  0, -2, -1,  0,  0},
    { 0,  0,  0,  0,  0,  0,  0,  0,  2, -2,  0,  0,  1,  1,  0,  0},
    {-3,  0,  3,  0,  0,  0,  0,  0, -2,  0, -1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0, -3,  0,  3,  0,  0,  0,  0,  0, -2,  0, -1,  0},
    { 9, -9, -9,  9,  6,  3, -6, -3,  6, -6,  3, -3,  4,  2,  2,  1},
    {-6,  6,  6, -6, -3, -3,  3,  3, -4,  4, -2,  2, -2, -2, -1, -1},
    { 2,  0, -2,  0,  0,  0,  0,  0,  1,  0,  1,  0,  0,  0,  0,  0},
    { 0,  0,  0,  0,  2,  0, -2,  0,  0,  0,  0,  0,  1,  0,  1,  0},
    {-6,  6,  6, -6, -4, -2,  4,  2, -3,  3, -3,  3, -2, -1, -2, -1},
    { 4, -4, -4,  4,  2,  2, -2, -2,  2, -2,  2, -2,  1,  1,  1,  1}};

  int i, j, k, l;
  Real xx, d1d2;
  std::vector<Real> c1(16, 0), x(16, 0);

  d1d2 = d1 * d2;
  for (i = 1; i <= 4; ++i)
  {
    x[i-1] = y[i];
    x[i+3] = y[i] * d1;
    x[i+7] = y2[i] * d2;
    x[i+11] = y12[i] * d1d2;
  }
}

void
BicubicSplineInterpolation::solve()
{}
