#include <iostream>

int
main()
{
  unsigned i = 5;
  unsigned j = 6;

  switch (i)
  {
    case 5:
    {
      if (j == 6)
      {
        std::cout << "output 1\n";
        break;
      }
      std::cout << "output 2\n";
      break;
    }

    default:
      std::cout << "output 3\n";
  }
}
