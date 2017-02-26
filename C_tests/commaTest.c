#include <string.h>
#include <stdio.h>


int main ( int argc, char* argv[]){

   int a;
   printf ("Commas are wack: %d \n", (a=4, a+=3));

   return 0;
}
