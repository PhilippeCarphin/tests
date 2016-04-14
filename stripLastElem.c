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
      token = strtok(path,"/");
   }

   if ( strcmp (path, "/first/second/third" ) == 0 ||
        strcmp (path, "/first/second/third/" ) == 0  ){
      printf( "Test passed, ");
   } else {
      printf( "Test failed, ");
   }
   printf( "stripped path : %s\n", path );

   return 0;
}
