#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {


   char * my_string = strdup("$((campagnolo))");
   char * p1 = strstr(my_string, "$((");
   printf( "p1 = strstr(my_string,\"$((\") is non-null and only serves to indicate the presence of $((, p1:%s\n",p1);
   char * p2 = strstr(p1,"))");
   printf( "p2 = strstr(p1,\"))\"), p2:%s\n", p2);
   char * p3 = strstr(my_string, "zzz");
   if( p3 == NULL ) 
      printf("p3 = strstr(\"zzz\") is NULL as expected\n");

   printf("\
$((campagnolo))\n\
^            ^\n\
p1           p2\n\
\n\
then we move p1 forward by 3 and do *p2 = '\\0'\n");

   p1 += 3;
   *p2 = '\0';

   printf( "the result is that p1:%s\n",p1);

   return 0;
}
