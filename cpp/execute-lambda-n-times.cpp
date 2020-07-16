#include <vector>

int main() {
  std::vector<int> my_vec;
  unsigned int num_vec_entries = 5;
  unsigned int counter = 0;

  num_vec_entries *[&] { my_vec.push_back(counter++); };
}
