#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct Person {
  char* name;
};


int main(){
  struct Person person1;
  char * name = (char*)calloc(sizeof(char), 15);

  char string[10000];
  for (int i = 0; i<10000; i++) string[i] = 'A';

  name = string;
  printf("%ld\n", strlen(name));
  printf("%ld\n", sizeof(name));

  return 0;
}
