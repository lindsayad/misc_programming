#include <iostream>
using namespace std;

class Dummy {
    public:
        bool isitme (Dummy&);
};

bool Dummy::isitme (Dummy& param) {
    if (&param == this) return true;
    else return false;
}

int main() {
    Dummy a;
    Dummy * b = &a;
    if (a.isitme(a)) cout << "yes, &a is b\n";
    return 0;
}
