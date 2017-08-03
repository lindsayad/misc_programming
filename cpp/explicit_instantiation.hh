#include <complex>

template<typename T>
class Jimmy
{
public:
  Jimmy();
  virtual ~Jimmy();

  template<typename U>
  U fp_erf(const U x);

  template<typename U>
  std::complex<U> fp_erf(const std::complex<U> x);
};

extern template class Jimmy<float>;
extern template class Jimmy<std::complex<float>>;
