#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>


void someFunc(char * str)
{
   fprintf(stderr, "Debug: in function %s(): (file %s:%d)\n",__func__,__FILE__,__LINE__);
   fprintf(stderr, "My arg = %s\n",str);
}

int main ( int argc , char ** argv ) {

   someFunc("Hello");
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   someFunc("Goodbye");
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   fprintf(stderr, "In file %s, line %d.\n",__FILE__,__LINE__);
   return 0;
}


