#include "Moose.h"
#include "MonotoneCubicInterpolation.h"
#include <iostream>

PerfLog Moose::perf_log("monotone");

int main()
{
  std::vector<double> x(11);
  std::vector<double> y(11);

  x[0] = 0;
  y[0] = 5;
  x[1] = 2;
  y[1] = 1;
  x[2] = 4;
  y[2] = 5;
  x[3] = 6;
  y[3] = 17;
  x[4] = 8;
  y[4] = 37;
  x[5] = 10;
  y[5] = 65;
  x[6] = 12;
  y[6] = 65;
  x[7] = 14;
  y[7] = 65;
  x[8] = 16;
  y[8] = 100;
  x[9] = 20;
  y[9] = 80;
  x[10] = 23;
  y[10] = 110;

  MonotoneCubicInterpolation interp2(x, y);

  std::vector<double> xnew;
  for (double z = 0; z < 23.1; z += .1)
    xnew.push_back(z);
  interp2.dumpCSV("output.csv", xnew);

}
