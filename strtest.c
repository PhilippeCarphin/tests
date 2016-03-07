#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main( int argc , char** argv )
{
  extern char etext, edata, end;

  printf("etext : %lX \n", (unsigned long int)&etext);
  printf("edata : %lX \n", (unsigned long int)&edata);
  printf("end : %lX \n", (unsigned long int)&end);

  return 0;
}
