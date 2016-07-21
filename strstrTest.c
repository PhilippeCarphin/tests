#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {


   char * my_string = strdup("$((campagnolo))");
   char * p1 = strstr(my_string, "$((");
   printf( "p1:%s\n", p1);
   char * p2 = strstr(p1,"))");
   printf( "p2:%s\n", p2);

   p1 += 3;
   *p2 = '\0';

   printf( "p1:%s\n",p1);

   return 0;
}
