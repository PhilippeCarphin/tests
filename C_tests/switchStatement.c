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


int char_to_number(char c){return (int) c;}
/*******************************************************************************
 * Silly switch statement based on input char
*******************************************************************************/
int what_char( char c ){

   switch ( c )
   {
      case 'A':
         return char_to_number('A');
      case 'B':
         return char_to_number('B');
         break;
      case 'C':
         return char_to_number('C');
         break;
      default:
         return char_to_number('X');
   }
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
