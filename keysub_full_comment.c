#define _XOPEN_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000], var_name[100];
   const char *src = str, *value;
   char * dst = output, *stopPoint;
   int i = 0, getFromEnv = 1;
   size_t l, fl = strlen(frontDelim), el = strlen(endDelim);

   while( *src != 0 ){
      if((stopPoint = strstr(src,frontDelim)) != NULL){
         memcpy(dst,src,l = stopPoint - src);
         src+=l+fl;
         dst+=l;
      } else {
         memcpy(dst,src,l=strlen(src));
         dst+=l;
         break;
      }
      if((stopPoint = strstr(src,endDelim)) != NULL){
         memcpy(var_name,src,l = stopPoint-src);var_name[l] = 0;
         src += l + el;
      }else{
         return NULL;
      }
      if( getFromEnv )
         value = getenv(var_name);
      else
         ;/* value = SeqUtil_getdef(...); */
      memcpy(dst,value,l=strlen(value));
      dst+=l;
   }
   *dst = '\0';
   return strdup(output);
}



int main ( int argc , char ** argv ) {

   const char *values[2] = {"is","string"};
   const char *input = "This ${word1} a ${word2}.";
   putenv("word1=is");
   putenv("word2=string");

   char * output = keysub(input,values,"${","}");

   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This %*&$((((word1)))) a %*&$((((word2)))).";
   output = keysub(input,values,"%*&$((((","))))");

   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");

   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This Dominicword1Racette a Dominicword2Racette.";
   output = keysub(input,values,"Dominic","Racette");

   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");

   printf("output : %s\n",output);
   return 0;
}
