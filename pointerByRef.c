#include <stdio.h>
#include <stdlib.h>

void changep(int &i)
{
  i++;
}
int main(int argc, char** argv)
{
  int *p;
  p = (int*)malloc(3*sizeof(int));
  p[0] = 0;
  p[1] = 1;
  p[2] = 2;
  int i = 0; 
  printf("Printing p[i]: %d \n", p[i]);
  changep(i);
  printf("Printing p[i] after calling changep(p) : %d \n", p[i]);
  return 0;
}
