#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/* I made this to look at how the compiler creates assembler code for switch
 * statements */
void what_char( char c ){

   printf("HELLO\n");
   switch ( c )
   {
      case 'a':
      case 'A':
         printf("A");
         break;
      case 'b':
      case 'B':
         printf("B");
         break;
      case 'c':
      case 'C':
         printf("C");
         break;
      default:
         printf("default");
   }
   printf("END\n");
}

int main ( int argc , char ** argv ) {


   what_char('c');
   what_char('a');
   return 0;
}
