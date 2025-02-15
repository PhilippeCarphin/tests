#include <stdio.h>
#include "subroutines.h"

int main(int argc, char **argv){

  for(int i = 0; i < argc ; i++){
    fprintf(stderr, "arg[%d]='%s'\n", i, argv[i]);
  }
  say_hello();
  return 0;
}
