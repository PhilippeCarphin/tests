#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int isDelim(char c){
   switch(c){
      case '\0':
      case '\t':
      case ' ' :
         return 1;
         break; /* As a matter of style, put the 'break' anyway even if there is a return above it.*/
      default:
         return 0;
   }
}

int main ( int argc , char ** argv ) {

   if( argc <= 1 ) exit(1);
   char * input = strdup(argv[1]);

   char * current = NULL, * previous = NULL;

   int chars = 0;

   /* Find last word break with fewer than 80 chars */

   current = input;
   while( *current != '\0' ){
      while ( chars <= 15){
         previous = current - 1;
         while ( !isDelim( *current ) ) ++current, ++chars;
         if( *current != '\0' ) ++current;
      }
      *(previous) = '\n';
      chars = 0;
   }

   puts(input);
   free(input);



   return 0;
}
