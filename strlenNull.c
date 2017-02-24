#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/*
 * This test shows that strlen(NULL) causes a segmentation fault.
 */
int main ( int argc , char ** argv ) {
   char * my_null_ptr = NULL;
   int len = strlen( my_null_ptr );

   printf( "Then lenght of a string which is NULL is : %d\n", len);
   return 0;
}
