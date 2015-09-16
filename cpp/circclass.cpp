#include <iostream>
using namespace std;

class Circle {
        double radius;
    public:
        Circle() { radius = 5; }
        Circle(double r) { radius = r; }
        double circum() {return 2*radius*3.14159265;}
};

int main () {
    Circle foo (10.0);
    Circle bar = 20.0;
    Circle baz {30.0};
    Circle qux = {40.0};
    Circle qip {};

    cout <<  "foo's circum: " << foo.circum() << endl;
    cout <<  "bar's circum: " << bar.circum() << endl;
    cout <<  "baz's circum: " << baz.circum() << endl;
    cout <<  "qux's circum: " << qux.circum() << endl;
    cout <<  "qip's circum: " << qip.circum() << endl;
    return 0;
}
