#include <iostream>
#include <string>
using namespace std;

int main()
{
	string mystring = "This is a string";
	cout << mystring << endl;
	mystring = "This is a" " different string"	" obviously"
". How about this new line?"			" This makes the code look pretty messy doesn't it?";
	cout << "strings expressed in \
two lines" << endl;
	return 0;
}
