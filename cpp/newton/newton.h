#include "metaphysicl/dualsemidynamicsparsenumberarray.h"
#include "Eigen/Dense"

#include <vector>
#include <cmath>
#include <iostream>

using MetaPhysicL::DualNumber;
using MetaPhysicL::NWrapper;
using MetaPhysicL::SemiDynamicSparseNumberArray;

using namespace Eigen;

typedef double Real;
namespace libMesh
{
typedef unsigned int dof_id_type;
}

typedef SemiDynamicSparseNumberArray<Real,
                                     libMesh::dof_id_type,
                                     NWrapper<20>>
    DNDerivativeType;

template <std::size_t N>
using DNDerivativeSize = SemiDynamicSparseNumberArray<Real, libMesh::dof_id_type, NWrapper<N>>;

typedef DualNumber<Real, DNDerivativeType, /*allow_skiping_derivatives=*/true> ADReal;

template <typename ResidualFunctor>
inline
void
newton(ResidualFunctor residual_functor, std::vector<double> & u, const double rel_tol = 1e-12,
  const unsigned int max_it = 50)
{
  const auto rank = u.size();
  std::vector<ADReal> residuals(rank);
  residual_functor(residuals, u);

  double initial_residual_norm = 0;
  double residual_norm;
  for (const auto & resid : residuals)
    initial_residual_norm += resid.value() * resid.value();
  residual_norm = initial_residual_norm = std::sqrt(initial_residual_norm);
  unsigned int it = 0;

  while (residual_norm / initial_residual_norm > rel_tol)
  {
    MatrixXf A(rank, rank);
    VectorXf b(rank);
    for (std::size_t i = 0; i < rank; ++i)
    {
      b(i) = -residuals[i].value();
      for (std::size_t j = 0; j < rank; ++j)
        A(i, j) = residuals[i].derivatives()[j];
    }

    VectorXf x = A.colPivHouseholderQr().solve(b);

    for (std::size_t i = 0; i < rank; ++i)
      u[i] = u[i] + x(i);

    residual_functor(residuals, u);
    residual_norm = 0;
    for (const auto & resid : residuals)
      residual_norm += resid.value() * resid.value();
    residual_norm = std::sqrt(residual_norm);

    ++it;
    if (it == max_it)
    {
      std::cout << "Reached the maximum  number of iterations" << std::endl;
      break;
    }
  }
}
