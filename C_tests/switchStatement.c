#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/*
 * I made this to look at how the compiler creates assembler code for switch
 * statements and compare it to an if-else structure
 *
 * The switch statement takes 68 lines of assembler code and the if takes 63
 * lines.
 *
 * I have not done timing tests which would actually be much better than just
 * counting assembler lines.
 */


/*******************************************************************************
 * Silly switch statement based on input char
*******************************************************************************/
void what_char( char c ){

   switch ( c )
   {
      case 'A':
         printf("A");
         break;
      case 'B':
         printf("B");
         break;
      case 'C':
         printf("C");
         break;
      default:
         printf("default");
   }
   printf("END\n");
}

/*******************************************************************************
 * Silly if-else-if structur based on input char.
*******************************************************************************/
void what_char_if(char c)
{
	if(c == 'A'){
		printf("A");
	} else if (c == 'B'){
		printf("B");
	} else if (c == 'C'){
		printf("C");
	} else {
		printf("Default");
	}
	printf("END\n");
}



int main ( int argc , char ** argv ) {


   what_char('C');
   what_char('A');
   what_char_if('A');
   what_char_if('C');
   return 0;
}
