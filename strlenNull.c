#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {
#if 0
   char * my_null_ptr = NULL;
   int len = strlen( my_null_ptr );

   printf( "Then lenght of a string which is NULL is : %d\n", len);
   printf( "this is probably because NULL == '\\0' is %s\n", ( NULL == '\0' ? "true" : "false" ));
#else
   printf( "this is probably because NULL == '\\0' is %s\n", ( NULL == '\0' ? "true" : "false" ));
#endif
   /* Never mind this test.  It shows that strlen(NULL) causes a segmentation
    * fault */
   return 0;
}
