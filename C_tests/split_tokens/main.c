#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "splitTokens.h"





int main(void)
{
   char *request = "GET /test1 field3\nFeild_name: Value1";
   char **tokens = getTokens(request,"\n ");
   char **ptr = tokens;

   while(*ptr != NULL){
      printf("%s\n", *ptr); ptr++;
   }

   return 0;
}

   
