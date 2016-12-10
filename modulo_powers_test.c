#include <stdio.h>
#include <stdlib.h>

/*
 * This test shows the obsious, that integers have a maximum value in C and that
 * when we pass this value, an overflow occurs.  Therefore, in when calculating
 * the value of (2^311)%1000, for example, we must take the modulo at the same
 * time as we take powers since (a*b) == (a%n)(b%n) mod n;
 *
 * There is also a python version of this experiment that shows that python can
 * haver arbitrarily large integers.
 */


/*******************************************************************************
 * This function gives an incorrect value since it calculates a^e, and then
 * takes the modulo. And when the exponent e is large enough, the working value
 * retval overflows.
*******************************************************************************/
unsigned long int exponentiate1(unsigned long int a, unsigned long int e, unsigned long int n)
{
   unsigned long int i = 0;
   unsigned long int retval = 1;
   for(i = 0; i < e; ++i)
   {
      retval *= a;
   }
   retval = retval %n;

   return retval;
}

/*******************************************************************************
 * This function gives correct results because overflow is avoided by taking the
 * remainder at each multiplication.  
*******************************************************************************/
unsigned long int exponentiate2(unsigned long int a, unsigned long int e, unsigned long int n)
{
   unsigned long int retval = 1;
   unsigned long int i = 0;

   for(i = 0; i < e; ++i)
   {
      retval *= a;
      retval %= n;
   }

   return retval;
}

int main(void)
{
   printf("First  exp: 2^311 mod 1000 : %lu\n", exponentiate1(3,311,1000));
   printf("Second exp: 2^311 mod 1000 : %lu\n", exponentiate2(3,311,1000));
   return 0;
}
