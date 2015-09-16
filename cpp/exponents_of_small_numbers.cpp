#include <iostream>
#include <cmath>
using namespace std;

int main()
{

  float i;
  float Eiz = 12.78;
  float u = 18.0;
  float em = 38;
  
  // for (i = 25.0; i > -25.0; i+=-1.0) {
  //   cout << "i = " << i << "; exp(i) = " << exp(i) << "; exp(-Eiz/exp(i)) = " << exp(-Eiz/exp(i)) << endl;
  // }

  cout << std::exp(-Eiz/(2.0/3*std::exp(u-em)))*std::exp(em-u)*std::exp(em)*-Eiz << endl;
}
