#include <iostream>

using namespace std;

int main()
{
  cout << sizeof(1) << endl;
  cout << sizeof(1.) << endl;
  long double a;
  cout << sizeof(a) << endl;
  cout << sizeof(unsigned(1)) << endl;
}
