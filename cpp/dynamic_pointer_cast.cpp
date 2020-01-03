#include <memory>

int main() {
  std::unique_ptr<int> a(new int(5));
  // Compilation error
  // auto result = std::dynamic_pointer_cast<int>(a);

  // This works
  auto result = dynamic_pointer_cast<int>(a);
}
