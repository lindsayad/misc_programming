#include <iostream>
using namespace std;

/* const double pi = 3.14159;
const char newline = '\n'; */

#define pi 3.1459
#define newline '\n'

int main ()
{
	double r=5.0;	//radius
	double circum;	//circumference

	circum = 2 * pi * r;
	cout << circum << newline;
}
