/* #include <iostream> */

/* typedef struct { */
/* } PyModuleObject; */

/* void shut_it() { */
/*   std::cout << "shut it" << std::endl; */
/* } */

/* class Dodo */
/* { */
/*   int _a; */
/*   float _b; */
/*   void setter(int x, float y); */
/* }; */

/* void */
/* Dodo::setter(int x, float y) */
/* { */
/*   _a = x; */
/*   _b = y; */
/* } */

/* Dodo dodo; */

/* double bar(int x); */

// Declare an external function
extern double bar(double x);

// Define a public function
double foo(int count)
{
    double  sum = 0.0;

    // Sum all the values bar(1) to bar(count)
    for (int i = 1;  i <= count;  i++)
        sum += bar((double) i);
    return sum;
}
