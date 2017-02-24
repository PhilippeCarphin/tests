#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

int main ( int argc , char ** argv ) {

   const char * nullPtr = NULL;
   const char * emptyStr = "";
   const char * dynamicEmpty = strdup("");
first:

   /*
	 * cmpq	$0, -16(%rbp)
	 * jne	.L3
    */
   if ( nullPtr == NULL )
      puts("Is NULL\n");

second:
   /*
	 * movq	-8(%rbp), %rax
	 * movzbl	(%rax), %eax
	 * testb	%al, %al
	 * je 	.L4
    */
   if ( strlen(emptyStr) > 0 )
      puts("Is not empty\n");

third:
   /*
	 * movq	-8(%rbp), %rax
	 * movzbl	(%rax), %eax
	 * testb	%al, %al
	 * je 	.L5
    */
   if ( emptyStr[0] != '\0' )
      puts("First char is not NUL byte");

fourth:
   if( strlen(dynamicEmpty) > 0)
      puts("dynamic is non-empty\n");
fifth:
   if( strlen(dynamicEmpty) > 80)
      puts("dynamic is non-empty\n");
sixth:
   if( strlen(emptyStr) > 80)
      puts("static empty is non-empty\n");

   return 0;
}

/* CONCLUSION: testing for empty string is two machine instructions more than
 * checking for NULL. Therefore, it is acceptable to have the unset values in
 * the string be empty strings.
 */
