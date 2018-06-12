#include <stdlib.h>
#include <stdio.h>

int fizzbuzz(int n){
   int fizzed = (n % 3 == 0);
   int buzzed = (n % 5 == 0);

   if( fizzed )
      printf("fizz");

   if ( buzzed )
      printf("buzz");

   if ( !( fizzed || buzzed) )
      printf("%d", n);

   putchar('\n');
   return 0;
}


int main(void){

   for(int i = 1; i < 16; i++){
      fizzbuzz(i);
   }
   return 0;
}

