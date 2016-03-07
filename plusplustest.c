#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
  int arr[3] = {1,2,3};
  int i = 1;
  printf("avec i = 1 avant, affichons arr[++i]: %d \n", arr[++i]);
  i = 1;
  printf("avec i = 1 avant, affichons arr[i++]: %d \n", arr[i++]);
}
