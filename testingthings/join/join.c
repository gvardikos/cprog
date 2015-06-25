#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char stringara[]="sdafadf";
char *p ="This is the pointer";

int main (int a, char *b[]){
  
  printf("PRINTS A CHAR ARRAY:\n");
  char *stringara = malloc(100);
  strcpy(stringara,"some text");
  printf("%s\n",stringara);
  free(stringara);
  
  

  p++;
  p = p + 1;
  p = &p[1];

  printf("%s\n",p);
  
  

  

}
