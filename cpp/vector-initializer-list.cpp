#include <vector>
#include <iostream>

const unsigned int side_nodes_map[5][8] =
  {
    {0, 2, 1,  8,  7,  6, 99, 99}, // Side 0
    {0, 1, 4,  3,  6, 10, 12,  9}, // Side 1
    {1, 2, 5,  4,  7, 11, 13, 10}, // Side 2
    {2, 0, 3,  5,  8,  9, 14, 11}, // Side 3
    {3, 4, 5, 12, 13, 14, 99, 99}  // Side 4
  };

std::vector<unsigned>
nodes_on_side(const unsigned int s)
{
  return {side_nodes_map[s],
          side_nodes_map[s] + sizeof(side_nodes_map[s]) / sizeof(side_nodes_map[s][0])};
}

int main()
{
  auto nodes = nodes_on_side(0);
  for (auto & node : nodes)
    std::cout << node << "\n";
}
