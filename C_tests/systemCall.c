#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/wait.h>
int main ( int argc , char ** argv ) {

   /* Simple script that just does exit with what you give it */
   /* int code = system ( "exiter.sh 4" ); */
   int code = system ( "exit 4" );
   printf ( "Code = %d\n" ,code);
   printf ( "Correct code = %d\n" , WEXITSTATUS(code));

   return 0;
}
