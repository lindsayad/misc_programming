#include <iostream>
#include <string>
using namespace std;

class Example3 {
  string data;

public:
  Example3(const string &str) : data(str) {}
  Example3() {}
  const string &content() const { return data; }
};

class A {
public:
  A() {}
};

class B {
protected:
  B() {}
};

class ContainsB {
public:
  ContainsB() {}

private:
  B b;
};

class ContainsArrayB {
public:
  ContainsArrayB() {}

private:
  B b[10];
};

int main() {
  Example3 foo;
  Example3 bar("Example");

  cout << "bar's content: " << bar.content() << endl;

  ContainsB fox;
  ContainsArrayB trot;
}
