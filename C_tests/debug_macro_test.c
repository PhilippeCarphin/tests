#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#define DEBUG
#include "debug.h"

void test_debug_h()
{
   FUNCBEGIN

   DBG_PRINT("This is a test of DBG_PRINT\n");

   int i = 7;
   int my_int = 8;
   char *my_string = "hello world!";
   float my_float = 3.1415;
   IVAL(i);
   IVAL(my_int);
   SVAL(my_string);
   VARVALUE(my_float, %f);

   FUNCEND
}


void someFunc(char * str)
{
   fprintf(stderr, "Debug: in function %s(): (file %s:%d)\n",__func__,__FILE__,__LINE__);
   fprintf(stderr, "My arg = %s\n",str);
}

int main ( int argc , char ** argv ) {

   test_debug_h();

   return 0;
}


