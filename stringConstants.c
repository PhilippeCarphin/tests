#include <stdlib.h>
#include <string.h>
#include <stdio.h>



int main ( int argc , char ** argv ) {
   char * string1 = "Hello my friend";
   printf( "Here is my string: %s -- at adress %p \n", string1, string1);

   string1 = "Now a new string";
   printf( "Here is my string: %s -- at adress %p \n", string1, string1);

   string1 = strdup( "Third heap string");
   printf( "Here is my string: %s -- at adress %p \n", string1, string1);

   return 0;
}
