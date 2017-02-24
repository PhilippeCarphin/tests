char **getTokens(const char *src, const char *delim);

/* 
 * Test used to verify
#include "splitTokens.h"

   int main(void)
   {
      char *request = "GET /test1 field3\nFeild_name: Value1";
      char **tokens = getTokens(request,"\n ");
      int i = 0;

      while(tokens[i] != NULL){
         printf("%s\n", token[i]);
         i++;
      }

      return 0;
   }
*/

