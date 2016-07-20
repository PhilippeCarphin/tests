#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   const char *p = str;
   char retval[1000] = {'\0'};
   char * dst = retval;
   char variable[100];
   char *var = variable;
   const char *value;
   const char *val;
   int i = 0;
   char *stopPoint = NULL;

   while( *p != 0 ){

      stopPoint = strstr(p,frontDelim);
      if(stopPoint != NULL){
         while( p < stopPoint )
            *dst++ = *p++;
      } else {
         while(*p != 0)
            *dst++ = *p++;
         break;
      }

      /* If *p == 0 we're done */
      if( *p == '\0' )
         break;

      /* Now *p points on the start of the front delimiter string.  Check that
       * the delimiter string is valid, and advance by the length of said
       * delimiter. */
      if( p != strstr(p,frontDelim) ){
         printf("ERROR:Incorect variable name front delimiter\n");
         exit(1);
      }
      p += strlen(frontDelim);

      /* Copy into variable name until a endDelim is encountered*/
      stopPoint = strstr(p,endDelim);
      if(stopPoint != NULL){
         while( p < stopPoint)
            *var++ = *p++;
         p += strlen(endDelim);
      }else{ 
         printf("Front variable token %s must be accompanied by matching ending variable token %s\n", frontDelim, endDelim);
      }

      /* find value of variable */
      /* Calling getdef, and have getdef either look in the deffile or in the
       * environment.  Everyone does his job, this functions job is to change
       * "${variable_name}" for "value".  And it's getdef's job to find the
       * value corresponding to "variable_name". */
      value = values[i++];

      /* Copy value into destination string */
      val = value;
      while( *val != '\0' )
         *dst++ = *val++;

      var = variable;
   }
   *dst = '\0';
   return strdup(retval);
}
int main ( int argc , char ** argv ) {

   const char *values[2] = {"is","string"};
   const char *input = "This ${word1} a ${word2}.";
   
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
