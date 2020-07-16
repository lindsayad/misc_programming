template <typename T> class Side {};

template <typename T> class Quad8Templ;

void foo() { Side<Quad8Templ<double>> side; }

template <typename T> class Quad8Templ {};

int main() { foo(); }
