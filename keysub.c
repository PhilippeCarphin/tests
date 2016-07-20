#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];   /* Char array in which we construct the output */
   char variable[100];  /* Array into which we copy the variable name */
   const char *p = str, /* Iterator on the characters of the input string */
              *var,     /* Iterator on the characters of variable char array */
              *value,   /* Value that will replace variable name */
              *val;     /* Iterator on value of variable */
   char * dst = output; /* Iterator on output array */
   int i = 0;           /* Only used for testing */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */

   while( *p != 0 ){
      /*
       * Copy until the first occurrence of startDelim. If none is found, copy
       * the whole string, and exit the loop.
       */
      stopPoint = strstr(p,frontDelim);
      if(stopPoint != NULL){
         while( p < stopPoint ) *dst++ = *p++;
      } else {
         while(*p != 0) *dst++ = *p++;
         break;
      }

      /*
       * Now *p points on the start of the front delimiter string.  Check that
       * the delimiter string is valid, and advance by the length of said
       * delimiter. We know that we can safely advance by strlen(frontDelim)
       * because we would have broken out of the loop if we couldn't
       */
      p += strlen(frontDelim);

      /*
       * Copy until the first occurrence of endDelim.  We must be able to find
       * endDelim or else it means that we got invalid input. The pointer p
       * might point to the end of the string but we don't use it until the next
       * iteration, so this case will be caught when we test to start the next
       * iteration.
       */
      stopPoint = strstr(p,endDelim);
      if(stopPoint != NULL){
         char *var = variable;
         while( p < stopPoint) *var++ = *p++;
         p += strlen(endDelim);
      }else{
         goto delim_mismatch;
      }

      /*
       * find value of variable
       * Calling getdef, and have getdef either look in the deffile or in the
       * environment.  Everyone does his job, this functions job is to change
       * "${variable_name}" for "value".  And it's getdef's job to find the
       * value corresponding to "variable_name".
       */
      value = values[i++];

      /*
       * Copy value into destination string
       */
      val = value;
      while( *val != '\0' )
         *dst++ = *val++;
   }

   /*
    * We are done, mark the end of the return string with a nul byte
    */
   *dst = '\0';

   return strdup(output);

delim_mismatch:
   printf("Front variable token %s must be accompanied by matching ending variable token %s\n",
                                                         frontDelim, endDelim);
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
