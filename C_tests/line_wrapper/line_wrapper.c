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
   return 0;
}

int main ( int argc , char ** argv ) {

   if( argc <= 2 ) exit(1);

   char * start = argv[1];
   char * lastDelim = argv[1];
   char * current = argv[1];
   int wrapLength = atoi(argv[2]);
   char c = *current;

   int chars = 1;

   /* Go to 80 chars */
   while(c != 0){
      lastDelim = start;
      while((c = *current++) != 0 && chars++ <= wrapLength ){
         if( isDelim(c) )
            lastDelim = current - 1;
      }
      printLine(start,lastDelim);
      start = current;
      chars = 1;
   }



   return 0;
}
