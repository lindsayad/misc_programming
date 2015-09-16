#include <iostream>
using namespace std;

template <class T>
class mycontainer {
        T element;
    public:
        mycontainer (T arg) {element=arg;}
        T increase () {return ++element;}
};

template <>
class mycontainer <char> {
        char element;
    public:
        mycontainer (char arg) {element=arg;}
        char increase () {
            if ((element>='a')&&(element<='z'))
                element+='A'-'a';
            return element;
        }
};

int main() {
    mycontainer<int> myint (7);
    mycontainer<double> mydouble(17.5);
    mycontainer<char> mychar ('j');
    cout << mydouble.increase() << endl;
    cout << myint.increase() << endl;
    cout << mychar.increase() << endl;
    return 0;
}
