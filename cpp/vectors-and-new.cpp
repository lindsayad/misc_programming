#include <vector>

class A {
public:
  A(const A &) = default;
  A(A &&) = default;
  A() = default;

  A &operator=(const A &) = default;
  A &operator=(A &&) = default;
};

int main() {
  std::vector<A> perm;

  {
    std::vector<A *> temp;

    temp.push_back(new A);

    perm.push_back(std::move(*temp[0]));
  }

  perm[0];
}
