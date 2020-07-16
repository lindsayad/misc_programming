#include <memory>
#include "libmesh/auto_ptr.h"

using namespace libMesh;

int main()
{
  std::unique_ptr<int> up = make_unique<int>(42);
}
