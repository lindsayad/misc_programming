#include "explicit_instantiation.hh"

template<typename T>
Jimmy<T>::Jimmy() {}

template<typename T>
Jimmy<T>::~Jimmy() {}

template<typename T>
template<typename U>
std::complex<U> Jimmy<T>::fp_erf(const std::complex<U> x)
{
  return 0;
}

template<typename T>
template<typename U>
U Jimmy<T>::fp_erf(const U x)
{
  return 0;
}

template class Jimmy<float>;
template class Jimmy<std::complex<float>>;
template float Jimmy<float>::fp_erf(float);
template std::complex<float> Jimmy<std::complex<float>>::fp_erf(std::complex<float>);
