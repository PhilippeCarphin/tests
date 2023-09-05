#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

/*
 * This test demonstrates that printing to 'stderr' after having closed it
 * does nothing.
 */

int main ( int argc , char ** argv ) {

   // fclose(stderr);
   close(STDERR_FILENO);

   fprintf(stderr, "HELLO STDERR\n");

   fprintf(stdout, "HELLO STDOUT\n");

   return 0;
}
