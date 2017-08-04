#include <stdio.h>
#include <stdlib.h>
#include <cstring>

#define BUFFERSIZE 500
                      
typedef struct person {
  char *name;
} Person;

int main (int argc, char* argv[]){
  Person *person = NULL;
  char buffer[BUFFERSIZE];
  printf("Enter name\n");
  fgets(buffer, BUFFERSIZE, stdin);
  {
    char *name; 
    person = malloc(sizeof(Person));
    name = malloc(strlen(buffer)+1);
    strcpy (name,buffer);
    person->name = name;
  }
  free(person->name);
  free(person); 
  return 0;
}
