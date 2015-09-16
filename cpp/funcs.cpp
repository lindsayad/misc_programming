#include <iostream>
using namespace std;

void odd (int x);
void even (int x);

int main()
{
	int i;
	do {
		cout << "please, enter number (0 to exit); ";
		cin >> i;
		odd(i);
	} while (i!=0);
}

void odd (int x)
{
	if ((x%2)!=0) cout << "it is odd.\n";
	else even (x);
}

void even (int x)
{
	if ((x%2)==0) cout << "it is even.\n";
	else cout << "You didn't enter an integer you dumbo";
}
