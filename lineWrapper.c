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

int printLine(const char * start, const char * end){
   const char * p = start;
   while ( p <= end ) putchar(*p++);
   putchar('\n');
}

int main ( int argc , char ** argv ) {

   if( argc <= 2 ) exit(1);

   char * start = argv[1];
   char * lastChar = argv[1];
   char * current = argv[1];
   int wrapLength = atoi(argv[2]);

   int chars = 1;
   while( *current != '\0' ){
      while( chars <= wrapLength ){
         while ( !isDelim( *current ) ) ++current, ++chars;
         if( chars <= wrapLength){
            if(*current == '\0'){
               puts(start);
               return 0;
            }
            lastChar = current-1;
            current++,chars++;
         }
      }

      printLine(start,lastChar);
      current = lastChar + 1;
      while(isDelim(*current)){
         if( *current == '\0')
            return 0;
         else
            ++current;
      }
      start = current;
      lastChar = current;
      chars = 1;
   }

   return 0;
}
