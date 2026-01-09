#include <iostream>
#include <vector>

template <typename T, typename A>
std::ostream &
operator<<(std::ostream & os, const std::vector<T, A> & vec)
{
  os << "[";
  for (size_t i = 0; i < vec.size(); ++i)
  {
    os << vec[i];
    if (i != vec.size() - 1)
    {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

// Define the custom namespace
namespace libMesh
{

// Overload the operator<< to handle std::vector within the custom namespace
template <typename T, typename A>
std::ostream &
operator<<(std::ostream & os, const std::vector<T, A> & vec)
{
  os << "[";
  for (size_t i = 0; i < vec.size(); ++i)
  {
    os << vec[i];
    if (i != vec.size() - 1)
    {
      os << ", ";
    }
  }
  os << "]";
  return os;
}

}

int
main()
{
  std::vector<int> v = {1, 2, 3, 4, 5};

  using namespace libMesh;
  std::cout << v << std::endl;

  return 0;
}
