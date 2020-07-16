#include "templ.h"
#include <iostream>

template <> void A<double>::foo() { std::cout << "Im the spec\n"; }
