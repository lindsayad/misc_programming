#include <iostream>
using namespace std;

int main () {
  int a = 10;
  const int b = 10;
  const int c = 20;

  switch ( a ) {
  case b:
    cout << a << endl;
    break;
  case c:
    cout << a << endl;
    break;
  default:
    cout << a << endl;
    break;
  }

  return 0;
}
