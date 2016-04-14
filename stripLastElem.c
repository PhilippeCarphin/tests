#include <stdlib.h>
#include <stdio.h>
#include <string.h>

extern char * strdup( char *);

int main ( int argc , char ** argv ) {
   char * path = strdup("/first/second/third/last"); 
   char * c = path;
   char * lastSlash;

   while ( *c != '\0' ){
      printf("%c\n",*c);
      if ( *c == '/')
         lastSlash = c;
      ++c;
   }
   printf("*lastSlash = %c\n",*lastSlash);
   *lastSlash = '\0';

   char * token = strtok(path,"/");
   while ( token != NULL ){
      printf ( "token = %s\n", token);
      token = strtok(NULL,"/");
   }

   if ( strcmp (path, "/first/second/third" ) == 0 ||
        strcmp (path, "/first/second/third/" ) == 0  ){
      printf( "Test passed, ");
   } else {
      printf( "Test failed, ");
   }
   printf( "stripped path : %s\n", path );

   /* I had fun doing this but I ended up finding out that there was already a
    * thing called _nodeDataPtr->container
    *
    * Possibly after putting lastSlash = '\0', I could strdup the string and
    * free the initial one.
    *
    * Also note the strdup at the definition of path.  Since the string litteral
    * gets put in the .data segment, it is un modifiable.  And as we know,
    * strtok changes the thing you use it on.
    *
    * Also, the test fails because the slashes were replaced by NULL == '\0'*/

   return 0;
}
