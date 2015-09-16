#include <iostream>
using namespace std;

long factorial (long a);

int main()
{
	long number;
	do {
		cout << "Please, enter positive integer (0 to exit): ";
		cin >> number;
		factorial(number);
		cout << number << " factorial is: " << factorial(number) << endl;
	} while (number != 0);
	return 0;
}

long factorial (long a)
{
	if (a > 1)
		return (a * factorial(a-1));
	else
		return 1;
}

