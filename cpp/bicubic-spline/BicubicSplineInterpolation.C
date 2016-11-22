#include "BicubicSplineInterpolation.h"
#include <assert.h>

int BicubicSplineInterpolation::_file_number = 0;

BicubicSplineInterpolation::BicubicSplineInterpolation()
{
}

BicubicSplineInterpolation::BicubicSplineInterpolation(const std::vector<Real> & x1, const std::vector<Real> & x2, const std::vector<std::vector<Real> > & y, Real yp1/* = 1e30*/, Real ypn/* = 1e30*/) :
    SplineInterpolationBase(),
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
BicubicSplineInterpolation::setData(const std::vector<Real> & x1, const std::vector<Real> & x2, const std::vector<std::vector<Real> > & y, Real yp1/* = 1e30*/, Real ypn/* = 1e30*/)
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

  Real xx, d1d2;
  std::vector<Real> cl(16, 0), x(16, 0);

  d1d2 = d1 * d2;
  for (int i = 1; i <= 4; ++i)
  {
    x[i-1] = y[i];
    x[i+3] = y[i] * d1;
    x[i+7] = y2[i] * d2;
    x[i+11] = y12[i] * d1d2;
  }

  for (int i = 0; i <= 15; ++i)
  {
    xx = 0;
    for (int j = 0; j <= 15; ++j)
      xx += Ainv[i][j] * x[j];
    cl[i] = xx;
  }

  int k = 0;
  for (int i = 1; i <= 4; ++i)
    for (int j = 1; j <= 4; ++j)
      coeffs[i][j] = cl[++k];
}

void
BicubicSplineInterpolation::interpolate(std::vector<Real> & y, std::vector<Real> & y1, std::vector<Real> & y2, std::vector<Real> & y12, Real & x1l, Real & x1u, Real & x2l, Real & x2u, Real & x1, Real & x2, Real & ansy, Real & ansy1, Real & ansy2)
{
  Real t, u, d1, d2;
  std::vector<std::vector<Real> > coeffs(4, std::vector<Real>(4));
  d1 = x1u - x1l;
  d2 = x2u - x2l;

  if (d1 <= 0 || d2 <= 0)
    std::perror("x1u and x2u must be greater than x1l and x2l respectively.");

  calcCoeffs(y, y1, y2, y12, d1, d2, coeffs);

  t = (x1 - x1l) / d1;
  u = (x2 - x2l) / d2;
  ansy = ansy1 = ansy2 = 0;
  for (int i = 4; i >=1; --i)
  {
    ansy = t * ansy + ((coeffs[i][4] * u + coeffs[i][3]) * u + coeffs[i][2]) * u + coeffs[i][1];
    ansy1 = u * ansy1 + (3. * coeffs[4][i] * t + 2. * coeffs[3][i]) * t + coeffs[2][i];
    ansy2 = t * ansy2 + (3. * coeffs[i][4] * u + 2. * coeffs[i][3]) * u + coeffs[i][2];
  }
  ansy1 /= d1;
  ansy2 /= d2;
}

// void
// BicubicSplineInterpolation::computeDerivatives(std::vector<Real> & y, std::vector<Real> & x1, std::vector<Real> & x2)
// {


// }

void
BicubicSplineInterpolation::precomputeAuxSecondDerivativeTable()
{
  int m = _x1.size();
  _y2.resize(m);

  for (int j = 1; j <= m; ++j)
    spline(_x2, _y[j], _y2[j], _yp1, _ypn);
}

void
BicubicSplineInterpolation::solve()
{
  precomputeAuxSecondDerivativeTable();
}
