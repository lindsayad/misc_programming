namespace Foo
{
void
foof(float)
{
}
}
namespace Alex
{
using Foo::foof;
}

int
main()
{
  float x = 5;
  Alex::foo(x);
}
