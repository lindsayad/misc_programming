#include <cmath>
#include <Kokkos_Core.hpp>

class A
{
public:
  KOKKOS_INLINE_FUNCTION static int foo() { return 5; }
  KOKKOS_INLINE_FUNCTION int operator()(unsigned int) const { return A::foo(); }
};

int
main()
{
  Kokkos::initialize();
  {
    Kokkos::parallel_for(Kokkos::RangePolicy(0, 1), A{});
  }
  Kokkos::finalize();
}
