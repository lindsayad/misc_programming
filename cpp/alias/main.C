#include "node.h"
#include "using_templ.h"

int main() {
  Node node;
  foo(node);

  Node node2(node);
}
