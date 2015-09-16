// reading a text file
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main () {
  ifstream myfile ("example.txt");
  vector<double> EField;
  vector<double> alpha;
  double value;

  if (myfile.is_open())
  {
    while ( myfile >> value )
    {
      EField.push_back(value);
      myfile >> value;
      alpha.push_back(value);
    }
    myfile.close();
  }

  else cout << "Unable to open file"; 

  for (vector<double>::iterator it_E = EField.begin(), it_alpha = alpha.begin() ; it_E != EField.end() && it_alpha != alpha.end(); ++it_E, ++it_alpha)
    cout << ' ' << *it_E << ' ' << *it_alpha << endl;

  return 0;
}
