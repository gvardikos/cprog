#include <stdio.h>
#include <stdlib.h>


int *integerHope(void);

int main () {
  
  int x = 10;
  
  printf("Integet x value: %d\n",x);
  
  int *ppint;// = integerHope();
  *ppint = 16;
  *ppint = 18;
  
  //the only way to properly assign a value to a pointer is to allocate through malloc memmory first.
  double *pdouble = (double *) malloc(sizeof(double));
  *pdouble = 12.2;
  
  printf("The value of the pointer ppint is: %d\n", *ppint);
  printf("The value of he pointer pdouble is : %f\n",*pdouble);
  return 0;
}

int *integerHope(void){
  int *pint = malloc(sizeof(*pint));
  return pint;
}
