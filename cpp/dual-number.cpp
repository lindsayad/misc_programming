#include <Kokkos_Core.hpp>
#include <cmath>
#include <iostream>

// Minimal, header-only Dual Number type that is safe for Kokkos device code.
// - Fixed derivative dimension N for predictable layout/perf on GPU
// - POD-like, trivially copyable; no host-only features, no heap alloc
// - KOKKOS_INLINE_FUNCTION on all code paths used in device kernels
// - Implements basic arithmetic and a few math intrinsics
//
// Usage sketch (see bottom comment block):
//   using AD = Dual<double, NDIM>;               // NDIM = number of active DOFs per thread
//   AD x = AD::variable(3, 2.0);                 // value=2.0, d/dx3=1
//   AD y = sin(x) + 3.0 * x * x;                 // works in device code
//   double f = y.val; double d3 = y.dx(3);
//
// Notes
// * Choose NDIM appropriate to your local AD indexing (e.g., element-local dof count).
// * For dynamic derivative sizes, prefer templating on a max and track active range externally.
// * This is a minimal starting point—extend with more intrinsics as needed.

namespace adk
{

// Fixed-size Dual Number with N derivatives.
// T must be arithmetic (float/double); N > 0

template <typename T, int N>
struct Dual
{
  T val;
  Kokkos::Array<T, N> d; // derivative components

  // --- ctors ---
  KOKKOS_INLINE_FUNCTION
  Dual() : val(T(0))
  {
    for (int i = 0; i < N; ++i)
      d[i] = T(0);
  }

  KOKKOS_INLINE_FUNCTION
  explicit Dual(const T & v) : val(v)
  {
    for (int i = 0; i < N; ++i)
      d[i] = T(0);
  }

  // Construct a variable: value v, derivative 1 at index idx
  KOKKOS_INLINE_FUNCTION
  static Dual variable(int idx, const T & v)
  {
    Dual a(v);
    if (idx >= 0 && idx < N)
      a.d[idx] = T(1);
    return a;
  }

  // Access derivative (const)
  KOKKOS_INLINE_FUNCTION
  T dx(int i) const { return d[i]; }

  // zero derivatives
  KOKKOS_INLINE_FUNCTION
  void zero()
  {
    for (int i = 0; i < N; ++i)
      d[i] = T(0);
  }

  // --- unary ops ---
  KOKKOS_INLINE_FUNCTION
  Dual operator+() const { return *this; }

  KOKKOS_INLINE_FUNCTION
  Dual operator-() const
  {
    Dual z;
    z.val = -val;
    for (int i = 0; i < N; ++i)
      z.d[i] = -d[i];
    return z;
  }

  // --- compound ops with Dual ---
  KOKKOS_INLINE_FUNCTION Dual & operator+=(const Dual & b)
  {
    val += b.val;
    for (int i = 0; i < N; ++i)
      d[i] += b.d[i];
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator-=(const Dual & b)
  {
    val -= b.val;
    for (int i = 0; i < N; ++i)
      d[i] -= b.d[i];
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator*=(const Dual & b)
  {
    // (a*b)' = a'*b + a*b'
    T v = val * b.val;
    for (int i = 0; i < N; ++i)
      d[i] = d[i] * b.val + val * b.d[i];
    val = v;
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator/=(const Dual & b)
  {
    // (a/b)' = (a' b - a b')/b^2
    T inv = T(1) / (b.val);
    T v = val * inv;
    for (int i = 0; i < N; ++i)
      d[i] = (d[i] * b.val - val * b.d[i]) * (inv * inv);
    val = v;
    return *this;
  }

  // --- compound ops with scalar ---
  KOKKOS_INLINE_FUNCTION Dual & operator+=(const T & s)
  {
    val += s;
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator-=(const T & s)
  {
    val -= s;
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator*=(const T & s)
  {
    val *= s;
    for (int i = 0; i < N; ++i)
      d[i] *= s;
    return *this;
  }
  KOKKOS_INLINE_FUNCTION Dual & operator/=(const T & s)
  {
    T inv = T(1) / s;
    val *= inv;
    for (int i = 0; i < N; ++i)
      d[i] *= inv;
    return *this;
  }
};

// --- binary ops Dual op Dual ---

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator+(Dual<T, N> a, const Dual<T, N> & b)
{
  a += b;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator-(Dual<T, N> a, const Dual<T, N> & b)
{
  a -= b;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator*(Dual<T, N> a, const Dual<T, N> & b)
{
  a *= b;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator/(Dual<T, N> a, const Dual<T, N> & b)
{
  a /= b;
  return a;
}

// --- binary ops Dual op scalar ---

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator+(Dual<T, N> a, const T & s)
{
  a += s;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator-(Dual<T, N> a, const T & s)
{
  a -= s;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator*(Dual<T, N> a, const T & s)
{
  a *= s;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator/(Dual<T, N> a, const T & s)
{
  a /= s;
  return a;
}

// --- binary ops scalar op Dual ---

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator+(const T & s, Dual<T, N> a)
{
  a += s;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator-(const T & s, const Dual<T, N> & a)
{
  Dual<T, N> z(s);
  return z - a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator*(const T & s, Dual<T, N> a)
{
  a *= s;
  return a;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
operator/(const T & s, const Dual<T, N> & a)
{
  Dual<T, N> z(s);
  return z / a;
}

// --- math intrinsics ---

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
sin(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::sin(a.val);
  T c = ::cos(a.val);
  for (int i = 0; i < N; ++i)
    z.d[i] = c * a.d[i];
  return z;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
cos(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::cos(a.val);
  T s = -::sin(a.val);
  for (int i = 0; i < N; ++i)
    z.d[i] = s * a.d[i];
  return z;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
exp(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::exp(a.val);
  for (int i = 0; i < N; ++i)
    z.d[i] = z.val * a.d[i];
  return z;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
log(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::log(a.val);
  T inv = T(1) / a.val;
  for (int i = 0; i < N; ++i)
    z.d[i] = inv * a.d[i];
  return z;
}

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
sqrt(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::sqrt(a.val);
  T g = T(0.5) / z.val; // (sqrt x)' = 1/(2 sqrt x)
  for (int i = 0; i < N; ++i)
    z.d[i] = g * a.d[i];
  return z;
}

// pow(a, s) with scalar exponent s

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
pow(const Dual<T, N> & a, const T & s)
{
  Dual<T, N> z;
  z.val = ::pow(a.val, s);
  T g = (s == T(0)) ? T(0) : (s * ::pow(a.val, s - T(1)));
  for (int i = 0; i < N; ++i)
    z.d[i] = g * a.d[i];
  return z;
}

// tanh

template <typename T, int N>
KOKKOS_INLINE_FUNCTION Dual<T, N>
tanh(const Dual<T, N> & a)
{
  Dual<T, N> z;
  z.val = ::tanh(a.val);
  T g = T(1) - z.val * z.val;
  for (int i = 0; i < N; ++i)
    z.d[i] = g * a.d[i];
  return z;
}

} // namespace adk

using AD = adk::Dual<double, 3>; // 3 local DOFs active

struct Functor
{
  Kokkos::View<double *> f_val;
  Kokkos::View<double * [3]> f_grad; // store gradients per point

  Functor(Kokkos::View<double *> v, Kokkos::View<double * [3]> g) : f_val(v), f_grad(g) {}

  KOKKOS_INLINE_FUNCTION
  void operator()(const int i) const
  {
    // Define variables x0,x1,x2 with seed 1 at respective indices
    AD x0 = AD::variable(0, 1.0 + 0.01 * i);
    AD x1 = AD::variable(1, 2.0 - 0.02 * i);
    AD x2 = AD::variable(2, 0.5 + 0.03 * i);

    AD y = adk::sin(x0) + 3.0 * x1 * x1 + adk::exp(x2);

    f_val(i) = y.val;
    for (int k = 0; k < 3; ++k)
      f_grad(i, k) = y.d[k];
  }
};

int
main(int argc, char ** argv)
{
  Kokkos::initialize(argc, argv);
  std::cout << "DefaultExecutionSpace: " << Kokkos::DefaultExecutionSpace::name() << "\n";
  std::cout << "DefaultHostExecutionSpace: " << Kokkos::DefaultHostExecutionSpace::name() << "\n\n";
  // Detailed config (devices, threads, NUMA, etc.)
  Kokkos::print_configuration(std::cout);
  {
    int N = 128;
    Kokkos::View<double *> f_val("f_val", N);
    Kokkos::View<double * [3]> f_grad("f_grad", N);
    Kokkos::parallel_for("ad-demo", N, Functor{f_val, f_grad});
    Kokkos::fence();
  }
  Kokkos::finalize();
}
