#include <stdio.h>
#include <stdlib.h>
/*
 * This test shows how the compiler deals with a weird char litteral.
 * This comes from when I as a total beginner trying to understand how to
 * configure a microcontroller.
 *
 * PIND is a byte containing the values of the 8 pins on the D port of the
 * controller.
 *
 * The expression PIND & 0x05 is used when one wants to check pin 2 on that port
 * and is equivalent to the more expressive PIND & (1 << 2).
 *
 * What I was supposed to do was to set a certain bit in the EICRA register by
 * doing
 * EICRA |= (1 << n);
 * but we were so confused about what we even wanted to do and nothing was
 * working so we started trying retarded stuff.
 *
 * We were trying to enable interuptions on pin 2 of the D port which we check
 * by doing 
 * if(PIND & 0x04){...}
 *
 * This test is to investigate why our thing actually worked. This test shows
 * that the compiler actually takes the last character as the value.  So c = ')'
 * and if we look at the ASCII value of ')', it has a 1 in the place where we
 * wanted to put a 1.  It has 1s in all sorts of other places but that didn't do
 * anything bad that I know of.
 */
int main()
{
   char c = '(PIND & 0x04)';
   printf("The weird char is %c\n", c);
   return 0;
}

