#include <iostream>
using namespace std;

class CVector {
    public:
        int x,y;
        CVector () {};
        CVector (int a, int b) : x(a), y(b) {}
        CVector operator  + (const  CVector&);
};

CVector CVector::operator + (const CVector& param) {
    CVector temp;
    temp.x = x + param.x;
    temp.y = y + param.y;
  //  x *= 2;
  //  y *= 2;
  //  param.x *= 2;
  //  param.y *= 2;
  //  cout << "x = " << x << endl;
  //  cout << "y = " << y << endl;
  //  cout << "param.x = " << param.x << endl;
  //  cout << "param.y = " << param.y << endl;
  //  cout << "temp.x = " << temp.x << endl;
  //  cout << "temp.y = " << temp.y << endl;
    return temp;
}

int main() {
    CVector foo (3,1);
    CVector bar (1,2);
    CVector result;
  //  cout << "bar.x within main = " << bar.x << endl;
  //  cout << "bar.y within main = " << bar.y << endl;
    result = foo.operator+ (bar);
  //  cout << "foo.x within main = " << foo.x << endl;
  //  cout << "foo.y within main = " << foo.y << endl;
    cout << result.x << ", " << result.y << endl;
    return 0;
}
