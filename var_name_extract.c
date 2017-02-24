#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

const char* getVarName(const char *src, const char *startDelim,
                                        const char *endDelim)
{
   static char var_name[256];

   char *start = NULL;
   char *end = NULL;
   size_t len = 0;

   if(start = strstr(src,startDelim))
      start += strlen(startDelim);
   else
      return NULL;

   if(!(end = strstr(start,endDelim))){
      fprintf(stderr, "ERROR: delimitor mismatch in *function name*");
   }

   memcpy(var_name,start,len=end-start);

   var_name[len] = '\0';
   return var_name;
}




int main ( int argc , char ** argv ) {

   char *input = "$((varname))";
   fprintf(stderr, "Result: %s\n",getVarName(input, "$((", "))"));

   input = "dominicvarnameracette";
   fprintf(stderr, "Result: %s\n",getVarName(input, "$((", "))"));
   return 0;
}

