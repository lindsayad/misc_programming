#include <iostream>
using namespace std;

class MyClass {
        int x;
    public:
        MyClass(int val) : x(val) {}
        const int& get() const {return x;}
        int& get() {return x;}
};

int main() {
    MyClass foo(10);
    const MyClass bar(20);
    foo.get() = 15;
// bar.get() = 25;
    cout << foo.get() << endl;
    cout << bar.get() << endl;
    return 0;
}
