#include <stdlib.h>
#include <string.h>
#include <stdio.h>


#define padded 14
int main ( int argc , char ** argv ) {
   char * src = "ALLO";
   char * bines = NULL;
   
   bines = malloc(40 * sizeof(char));
   strcpy(bines, src);
   printf( "strlen(src) = %d\n", strlen(src));
   printf( "%s\n", bines);
   int i = strlen(bines);
   while ( i < padded ){
      bines[i++] = '0';
   }
   bines[padded] = '\0';
   printf ( "%s\n",bines );
   return 0;
}
