#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int i = 1234;

int is_divisible_by(int n, int modulus)
{
   return n % modulus;
}

int fizzbuzz(int n){
   for(int i = 88; i < 100; i++){
      printf("%d\n", i);
   }
   if(n % 3 == 0){
      puts("fizz");
   }
   if(n % 5 == 0){
      puts("buzz");
   } else if (n % 3 != 0){
      printf("%d", n);
   }
   putchar('\n');
   return 88;
}

int main(int argc, char **argv)
{
   fizzbuzz(8);
   is_divisible_by(45, 3);
	return 0x77;
}
