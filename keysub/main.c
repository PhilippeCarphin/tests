#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/********************************************************************************
 * Performs variable substitution on strings.  For example, with frontDelim =
 * "${" and endDelim = "}", the string str = "This ${word1} a ${word2}."  where
 * word1 is "is" and word2 is "string" would become "This is a string."
 * For testing purposes, the values of the variables are passed in an array of
 * strings and there is no actual lookup.  The first variable's value is
 * array[0] and the second variable's value is array[1].  But in real life, we
 * would make a 
 *    value = getValue(var_name);
 * function call.
********************************************************************************/
char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];     /* Char array into which we construct the output */
   char var_name[100];    /* Char array into which we copy the variable name */
   const char *src = str, /* Iterator on the characters of the input string */
              *value;     /* Value that will replace variable name */
   char * dst = output;   /* Iterator on output array */
   int i = 0;             /* Only used for testing */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */
   size_t len, fl = strlen(frontDelim), el = strlen(endDelim);

   /*
    * Example input: "this_${word1}_is_a_${word2}." with word1=is, and
    * word2=string.
    */
   while( *src != 0 ){
      /*
       * find the next occurrence of startDelim. If none is found, copy
       * until the end of the string, and exit the loop.
       */
      stopPoint = strstr(src,frontDelim); /* strstr(string, substring) returns a
                                             pointer to the first occurence of
                                             substring in string */
      /*
       *   this_${word1}_is_a_${word2}.
       *   ^    ^
       *   src stopPoint
       */
      if(stopPoint != NULL){
         /*
          * Copy src-stopPoint bytes into dst, note that the '$' is not included
          * because src-stopPoint=5.
          */
         memcpy(dst,src,len = stopPoint - src);
         /*
          *   this_
          *   ^
          *   output == dst
          */

         /*
          * we advance the pointers: src advances by the length of what was
          * copied
          */
         src+=len;
         dst+=len;

         /* this_${word1}_is_a_${word2}.
          *      ^
          *     src
          * this_
          * ^    ^
          * |   dst
          * output
          */

         /*
          * Then we advance src by the length of the delimiter string
          * Of course, these two moves for src would be done in one line by
          * doing src += len + fl;
          */
         src += fl;
         /* this_${word1}_is_a_${word2}.
          *        ^
          *       src
          */
      } else {
         /*
          * If there are no more starting delimiters, copy to the end of the
          * string, then get out
          */
         memcpy(dst,src,len=strlen(src));
         dst += len;
         break;
      }

      /*
       * Then we find the next end delimiter
       */
      stopPoint = strstr(src,endDelim);
      /*
       * this_${word1}_is_a_${word2}.
       *        ^    ^
       *       src   endDelim
       */
      if(stopPoint != NULL){
         /*
          * copy from src to endDelim ("word1") into the var_name
          */
         memcpy(var_name,src,len = stopPoint-src);var_name[len] = 0;
         /*
          * Advance the src pointer
          */
         src += len + el;
         /*
          * this_${word1}_is_a_${word2}.
          *              ^
          *             src
          */
      }else{
         /*
          * If we found a starting delimiter, then there should be an ending
          * delimiter to match.
          */
         goto delim_mismatch;
      }


      /*
       * find value of variable, for the purposes of this test, the values are
       * kind of artificial, but in a real situation, you would have something
       * like
       * value = getValue(var_name);
       */
      value = values[i++];

      /*
       * Copy value ("is") into destination string.
       */
      memcpy(dst,value,len=strlen(value));
      dst += len;

      /*
       * this_is
       * ^      ^
       * |      dst
       * output
       */
   }

   /*
    * We are done, mark the end of the return string with a nul byte
    */
   *dst = '\0';
   return strdup(output);

delim_mismatch:
   printf("Front variable token %s must be accompanied by matching ending variable token %s\n",
                                                         frontDelim, endDelim);
   return NULL;
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
   input = "This %*&$((((word1)))) a %*&$((((wor2)))).";
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
