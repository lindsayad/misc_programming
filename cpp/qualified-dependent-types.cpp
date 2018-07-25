#include <vector>

using namespace std;

template <class T> class MyClass {
  int i;
  vector<int> vi;
  vector<int>::iterator vitr;

  T t;
  vector<T> vt;
  typename vector<T>::iterator viter;
};

int main() { MyClass<int>; }
