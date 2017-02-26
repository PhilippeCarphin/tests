#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {
   printf("ALLO LES AMIS");
   if ( argc > 1 ){
      exit(argc);
   } else {
      return argc;
   }
   return 0;
}
