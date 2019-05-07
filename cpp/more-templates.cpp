#include <string>

// There are two kinds of errors: compiler and linker errors. I am going to give my understanding
// based on gcc because gcc seems to adhere to the C++ standard much more closely than clang.
//
// So, explicit instantiation of a class template will generate code for all members of that
// template that have definitions within the translation unit, and hence if for a given
// instantiation there are compilatiom errors in method bodies, the compiler will error out.
//
// However, an implicit instantion of a class template (say through construction) will not lead to
// code generation of template class methods, and hence if for the given implicit instantiation
// there would be compilatiom errors in method bodies that go unused, the compiler will not error
// out.
//
// Note that if a method is declared and not defined, then there will be linker errors

template <typename T>
class A
{
public:
  A();

  void foo();
};

// Explicit instantiation generates code for constructor and foo
template class A<std::string>;

// Fails because we try to generate code for foo, and we can't compile the method body
// template class A<int>;

// We can instantiate individual methods of a template class, but we can't do it for this one
// because we get a compiler error in the method body
//
// template void A<int>::foo();

// This one works!
template void A<std::string>::foo();

// If this was uncommented, we would get a compile error because we have a full specialization of
// A<int>::A after instantiation
//
// template A<int>::A();

// Obviously with this full specialization, we can only instantiate A<int>
template <>
A<int>::A()
{
}

// Now we can instantiate here
template A<int>::A();

// Now we can instantiate anything
template <typename T>
A<T>::A()
{
}

template <typename T>
void
A<T>::foo()
{
  // You can't just put anything in this method. It has to be something that **might** be able to
  // compile depending on the template parameter T
  T("Do you think this will work for anything?");
}

int
main()
{
  // This is fine because implicit instantiation only does code generation for the methods that
  // are used, unlike explicit template class instantiation.
  A<int> a1;

  // Compiler error because we can't initialize an int with a string!
  // a1.foo();

  // We've already explicitly instantiated all the member functions of A through our explicit
  // instantiation above, so we can feel confident in using anything here
  A<std::string> a2;
  a2.foo();
}

template <typename T>
class B
{
  void foo() { T("Do you think this will work for anything?"); }
};

template class B<std::string>;

// We can only explicitly instantiate once!
// template class B<std::string>;

template <typename T>
class C
{
};

C<int> c;
template class C<int>;
C<int> c2;

void
foo()
{
  // Cant explicitly instantiate in a function
  // template class C<double>;
}

namespace mySpace
{
// Can't instantiate outside of the namespace of the class template definition
// template class C<double>;
}
