#include <iostream>
#include <vector>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <typeinfo>

typedef float Real;

#define PRINT(var) #var

int main()
{
  using namespace std;
  int i, j, k;
  Real value;

  int _num_groups = 2;
  std::string property_tables_root = "/home/lindsayad/serpent/core/examples/serpent-input/msre/msr2g_enrU_mod_953_fuel_interp_";
  std::vector<std::string> xsec_names {"FLUX", "REMXS", "FISSXS", "NUBAR", "NSF", "FISSE", "DIFFCOEF", "CHI"};
  std::map<std::string, std::vector<std::vector<Real> > > xsec_map;

  for (j = 0; j < xsec_names.size(); j++)
  {
    std::string file_name = property_tables_root + xsec_names[j] + ".txt";
    const std::string & file_name_ref = file_name;
    cout << file_name << endl;
    std::ifstream myfile (file_name_ref.c_str());
    std::cout << xsec_names[j] << endl;
    xsec_map[xsec_names[j]].resize(_num_groups);
    if (myfile.is_open())
    {
      while (myfile >> value)
      {
        for (k = 0; k < _num_groups; k++)
        {
          myfile >> value;
          xsec_map[xsec_names[j]][k].push_back(value);
        }
      }
      myfile.close();
    }
  }
  std::vector<Real> temperature;
  std::string file_name = property_tables_root + "DIFFCOEF.txt";
  const std::string & file_name_ref = file_name;
  std::ifstream myfile (file_name_ref.c_str());
  if (myfile.is_open())
  {
    while (myfile >> value)
    {
      temperature.push_back(value);
      for (k = 0; k < _num_groups; k++)
        myfile >> value;
    }
    myfile.close();
  }
  for (const auto & it : xsec_map)
  {
    std::cout << it.first << endl;
    for (const auto & j : it.second)
      for (const auto & k : j)
        std::cout << k << std::endl;
  }
}
