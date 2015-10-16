#include <stdio.h>
#include <stdlib.h>
#include <iostream>

int main()
{
  std::string pPath = getenv("ZAPDIR");
  // const char * pPath;
  // pPath = getenv("ZAPDIR");
  std::string strPath = pPath;
  std::cout << pPath << std::endl;
  std::cout << strPath + "/src/materials/td_air.txt" << std::endl;
  
  // std::vector<Real> mean_energy;
  // std::vector<Real> alpha;
  // std::ifstream myfile ("/home/alexlindsay/zapdos/src/materials/td_air.txt");
  // Real value;

  // if (myfile.is_open())
  // {
  //   while ( myfile >> value )
  //   {
  //     EField.push_back(value);
  //     myfile >> value;
  //     mobility.push_back(value);
  //     myfile >> value;
  //     diffusivity.push_back(value);
  //     myfile >> value;
  //     alpha.push_back(value);
  //     myfile >> value;
  //     eta.push_back(value);
  //   }
  //   myfile.close();
  // }

  // else std::cout << "Unable to open file"; 

  return 0;
}
