#include <iostream>

namespace Moose
{
namespace Kokkos
{
template <typename T, unsigned int dim>
struct Array
{
  T data[dim];
};
}
} // namespace Moose::Kokkos

// Specialized overload in the global namespace (declared BEFORE call site)
template <typename T, unsigned int dim>
void
dataStore(std::ostream & stream, Moose::Kokkos::Array<T, dim> &, void *)
{
  stream << "✅ Specialized overload for Moose::Kokkos::Array used\n";
}

// Fallback (generic) overload
template <typename T>
void
dataStore(std::ostream & stream, T &, void *)
{
  stream << "❌ Fallback generic overload used\n";
}

int
main()
{
  Moose::Kokkos::Array<int, 3> arr;
  dataStore(std::cout, arr, nullptr); // Will use the specialized overload
  return 0;
}
