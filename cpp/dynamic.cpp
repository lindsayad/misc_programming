#include <cassert>
#include <iostream>
#include <new>

using namespace std;

int main() {
  int i, n;
  int *p;
  cout << "How many numbers would you like to type? ";
  cin >> i;
  p = new int[i];
  /*	if (p == nullptr)
                  cout << "Error: memory could not be allocated";
          else
          { */
  for (n = 0; n < i; n++) {
    cout << "Enter number: ";
    cin >> p[n];
  }
  cout << "You have entered: ";
  for (n = 0; n < i; n++)
    cout << p[n] << ", ";
  cout << endl;
  delete[] p;
  //	}

  int *q = new int[i * i];
  assert(q);

  delete[] q;

  int *s = nullptr;
  assert(s);

  return 0;
}
