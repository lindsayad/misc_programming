#include <stdio.h>

int main () {
// This is used to select faces from a 20-sided hex element
  int hex20_faces[6][8] = {
    {0, 1, 5, 4, 12, 8,  13, 16},
    {1, 2, 6, 5, 13, 9,  14, 17},
    {3, 2, 6, 7, 15, 10, 14, 18},
    {0, 3, 7, 4, 12, 11, 15, 19},
    {4, 5, 6, 7, 19, 16, 17, 18},
    {0, 1, 2, 3, 11, 8,  9,  10}
  };

// This is used to select faces from a second-order tet element
  int tet10_faces[4][6] = {
    {0, 1, 3, 4, 8, 7},
    {2, 3, 1, 9, 8, 5},
    {0, 3, 2, 7, 9, 6},
    {0, 2, 1, 6, 5, 4}
  };

  int * faces;
  faces = hex20_faces;
  faces = tet10_faces;

  return 0;
}
