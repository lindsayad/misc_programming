#include <iostream>
using namespace std;

int main()
{
	int firstvalue = 5, secondvalue = 15;
	int * p1, * p2;

	p1 = &firstvalue;
	p2 = &secondvalue;
	*p1 = 10;
	*p2 = *p1;
	p1 = p2;
	*p1 = 20;
	p1 = &firstvalue;

	cout << "firstvalue is " << firstvalue << endl;
	cout << "secondvalue is " << secondvalue << endl;
	cout << "pointer 1 points to address " << p1 << endl;
	cout << "pointer 2 points to address " << p2 << endl;
	return 0;
}
