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
  if (_x1.size() != _y.size())
    std::perror("y row dimension does not match the size of x1.");
  else
    for (int i = 0; i < _y.size(); ++i)
      if (_y[i].size() != _x2.size())
        std::perror("y column dimension does not match the size of x2.");
}

void
BicubicSplineInterpolation::precomputeAuxSecondDerivativeTable()
{
  int m = _x1.size();
  _y2.resize(m);

  for (int j = 1; j <= m; ++j)
    spline(_x2, _y[j], _y2[j]);
}

void
BicubicSplineInterpolation::solve()
{
  precomputeAuxSecondDerivativeTable();
}

Real
BicubicSplineInterpolation::sample(Real x1, Real x2)
{
  int n = _x2.size();
  int m = _x1.size();
  std::vector<Real> column_spline_second_derivs(m), row_spline_eval(m);

  // Evaluate m row-splines to get y-values for column spline construction
  for (int j = 1; j <= m; ++j)
    row_spline_eval[j] = SplineInterpolationBase::sample(_x2, _y[j], _y2[j], x2);

  // Construct single column spline; get back the second derivatives
  spline(_x1, row_spline_eval, column_spline_second_derivs);

  // Evaluate newly constructed column spline
  return SplineInterpolationBase::sample(_x1, row_spline_eval, column_spline_second_derivs, x1);
}
