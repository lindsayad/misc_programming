#include "libmesh/replicated_mesh.h"

// C++ include files that we need
#include <iostream>
#include <algorithm>
#include <math.h>

// Basic include file needed for the mesh functionality.
#include "libmesh/libmesh.h"
#include "libmesh/mesh.h"
#include "libmesh/mesh_generation.h"
#include "libmesh/exodusII_io.h"
#include "libmesh/fe.h"

using namespace libMesh;

int main(int argc, char ** argv)
{
  LibMeshInit init(argc, argv);

  Mesh mesh(init.comm());
  mesh.read("bn3_15_mesh.e");

  mesh.all_first_order();
  mesh.write("bn3_15_mesh.e");
}
