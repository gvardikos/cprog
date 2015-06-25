#include <stdio.h>

double* biggest_double(double*,double*);

int main (){
  double *p1;
  double *p2;
  double x=1.1232123, y=9.73458734;
  p1=&x;
  p2=&y;
  
  double *b = biggest_double(p1,p2);
  printf("%g\n", *b);
  
  return 0;
}

double * biggest_double(double *pfloa1, double *pfloa2){
  double * biggest;
  
  if (*pfloa1 > *pfloa2){
    biggest = pfloa1;
  }
  else{
    biggest = pfloa2;
  }
  return biggest;
}



