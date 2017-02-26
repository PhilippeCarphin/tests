#include <stdlib.h>
#include <string.h>
#include <stdio.h>


int main ( int argc , char ** argv ) {

   printf ( "Ternary: ( 1 == 1 ? \"True\" : \"False\") : %s \n", ( 1 == 1 ? "True" : "False" ));
   printf ( "Ternary: ( 1 == 0 ? \"True\" : \"False\") : %s \n", ( 1 == 0 ? "True" : "False" ));
   return 0;
}
