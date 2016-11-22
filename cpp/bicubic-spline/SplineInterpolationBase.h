#ifndef SPLINEINTERPOLATIONBASE_H
#define SPLINEINTERPOLATIONBASE_H

#include <vector>

typedef double Real;

class SplineInterpolationBase
{
public:
  SplineInterpolationBase();

  virtual ~SplineInterpolationBase() = default;

  Real sample(const std::vector<Real> & x, const std::vector<Real> & y, const std::vector<Real> & y2, Real x_int) const;
  Real sampleDerivative(const std::vector<Real> & x, const std::vector<Real> & y, const std::vector<Real> & y2, Real x_int) const;
  Real sample2ndDerivative(const std::vector<Real> & x, const std::vector<Real> & y, const std::vector<Real> & y2, Real x_int) const;

protected:

  /**
   * This function calculates the second derivatives based on supplied x and y-vectors
   */
  void spline(const std::vector<Real> & x, const std::vector<Real> & y, std::vector<Real> & y2, Real yp1 = 1e30, Real ypn = 1e30);

  void findInterval(const std::vector<Real> & x, Real x_int, unsigned int & klo, unsigned int & khi) const;
  void computeCoeffs(const std::vector<Real> & x, unsigned int klo, unsigned int khi, Real x_int, Real & h, Real & a, Real & b) const;

};

#endif
