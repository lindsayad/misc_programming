#include <stdlib.h>

struct Jam {
  char * name;
};

int main()
{
  int count = 0;
  Jam * grape = (Jam *) malloc(count * sizeof(Jam));
  if (sizeof(grape) > 0)
    grape->name = (char *) malloc(sizeof(char));
  // int * p = (int *) malloc(sizeof(int));
  // p = NULL;
  if (grape->name != NULL)
    free (grape->name);
  free (grape);
}
