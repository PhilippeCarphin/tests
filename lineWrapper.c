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

int printSection(const char * start, const char * end){
   const char * p = start;
   while ( p <= end ) putchar(*p++);
}

int main ( int argc , char ** argv ) {

   if( argc <= 2 ) exit(1);

   int wrapLength = atoi(argv[2]);

   /* if ( strlen(argv[1]) <= wrapLength ) {
      puts ( argv[1] );
      exit(0);
   }
   */


   char * lastDelim = NULL;
   char * input = strdup(argv[1]);

   char * current = NULL, * previous = NULL;

   int chars = 1;
   int totalChars = 0;

   /* Find last word break with fewer than 80 chars */

   current = input;
   while( *current != '\0' ){
      while ( chars <= wrapLength && *current != '\0'){
         while ( !isDelim( *current ) ) ++current, ++chars;
         if( chars <= wrapLength) lastDelim = current;
         current++, ++chars;
      }
      *(lastDelim) = '\n';
      current = lastDelim + 1;
      chars = 1;
   }

done:
   puts(input);
   free(input);

   char * start = argv[1];
   char * lastChar = argv[1];
   current = argv[1];

   while( *current != '\0' ){
      while( 1 ){
         while ( !isDelim( *current ) ) ++current, ++chars;
         if( chars <= wrapLength){
            lastChar = current-1; // lastDelim is actually the last non-delimiter
            current++,chars++;
         } else {
            goto here;
         }
      }
here:
      printSection(start,lastChar);
      putchar('\n');
      current = lastChar + 1;
      while(isDelim(*current))
         if( *current == '\0') return 0; else ++current;
      start = current;
      lastChar = current;
      chars = 1;
   }




   return 0;
}
