#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *removeDuplicates(char *str)
{
   if(!str)
      return NULL;

   char *src = str;
   char *dst = str;
   char c = *src;
   *dst++ = *src++;

   while( c != 0 ){
      if( *src != c ){
         c = *src;
         *dst++ = *src++;
      } else {
         while( *src == c ){
            src++;
         }
      }
   }
   return str;
}


int main(void){
   char *input = strdup("This   is myy iiinput");

   printf("output: %s\n",removeDuplicates(input));

   input = strdup("");
   printf("output: %s\n",removeDuplicates(input));

   input = NULL;
   printf("output: %s\n",removeDuplicates(input));
   /* printf("output: %s\n",removeDuplicates(input)); */
   /* printf("output: %s\n",removeDuplicates(input)); */
   /* printf("output: %s\n",removeDuplicates(input)); */


   return 0;
}

   
