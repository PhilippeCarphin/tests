#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {

   fprintf(stderr, "Sizeof(char)=%lu\n", sizeof(char));
   fprintf(stderr, "Sizeof(int)=%lu\n", sizeof(int));
   fprintf(stderr, "Sizeof(char*)=%lu\n", sizeof(char*));

   return 0;
}
