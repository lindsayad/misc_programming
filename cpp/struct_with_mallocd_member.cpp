#include <stdio.h>
#include <stdlib.h>

struct sigaltstack {
    void *ss_sp;
    int ss_flags;
} ss;

int main()
{
  ss.ss_sp = (char *) malloc (sizeof(char));
  ss.ss_flags = 1;
  // int i = 2;
  // int * j = &i
  void * i = ss.ss_sp;
  free(i);
  // ss.ss_sp = j;
}

