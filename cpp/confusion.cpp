#include <iostream>
using namespace std;

int main() {
    int x = 42;
    int y& = x;
    cout << x << endl;
    cout << y << endl;
}
