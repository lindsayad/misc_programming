#include <iostream>

// int *
// return_pointer()
// {
//   return int(1);
// }

// class A
// {
// public:
//   A(int x) {_a = x;}
// };

// using buildPtr = A (*) (int);

// int main()
// {
//   // int * j = return_pointer();
//   // std::cout << *j << std::endl;
//   A a(2);
//   buildPtr ptr = a;

//   A *b = (*a)(i);
//   std::cout << b->_a << std::endl;
//   std::cout << a->_a << std::endl;
// }

// using func = void(*)(int);
void (*func)(int);

void act_func(int arg) {arg +=1;}

func = &act_func;

int main()
{
}
