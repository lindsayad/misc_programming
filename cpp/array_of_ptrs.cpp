#include <iostream>
#include <stdlib.h>
#include <memory>

int main()
{
  std::unique_ptr<int []> john (new int [5]);
  // int * i = (int *) malloc (sizeof(int));
  // *i = 4;
  // // int i = 4;
  // for (int j = 0; j < 5; j++)
  //   // john[j] = &i;
  //   john[j] = i;
  // for (int j = 0; j < 5; j++)
  //   std::cout << *(john[j]) << std::endl;
  // free (john[0]);
}
