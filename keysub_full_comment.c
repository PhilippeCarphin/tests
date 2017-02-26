#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];   /* Char array in which we construct the output */
   char var_name[100];  /* Array into which we copy the variable name */
   const char *src = str, /* Iterator on the characters of the input string */
              *value,   /* Value that will replace variable name */
              *val;     /* Iterator on value of variable */
   char * dst = output; /* Iterator on output array */
   int i = 0;           /* Only used for testing */
   /* int getFromEnv = (strcmp(source,"environment") == 0); */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */
   size_t len, fl = strlen(frontDelim), el = strlen(endDelim);
   register char c;

   /*
    * Example input: "this_${word1}_is_a_${word2}." with word1=is, and
    * word2=string.
    */
   while( *src != 0 ){
      /*
       * find the next occurrence of startDelim. If none is found, copy
       * until the end of the string, and exit the loop.
       */
      stopPoint = strstr(src,frontDelim);
      /*
       *   this_${word1}_is_a_${word2}.
       *   ^    ^
       *   src stopPoint
       */
      if(stopPoint != NULL){
         /*
          * Copy src-stopPoint bytes into dst
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
         printf("src:%s\n",src);
         printf("stopPoint:%s\n",stopPoint);
         printf("len:%d\n",len);
         src+=len+fl;
         printf("src is %s\n",src);

          printf("output%s\n",output);getchar();
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
          * Of course, these to moves for src would be done in one line
          * src += len + fl;
          */
         /* src += fl; */
         /* this_${word1}_is_a_${word2}.
          *        ^
          *       src
          */
      } else {
         /*
          * If there are no more starting delimiters, copy to the end of the
          * string, then get out
          */
         while((c=*src++) != 0) *dst++ = c;
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
       * if( getFromEnv )
       *    value = getenv(var_name);
       * else
       *    value = SeqUtil_getdef(...);
       */

      /*
       * Copy value into destination string.  The dst pointer advances as we
       * copy.
       */
      val = value;
      while( (c = *val++) != '\0' )
         *dst++ = c;
      /*
       * this_is
       * ^      ^
       * |      dst
       * output
       */
      /* if( !getFromEnv ) */
         /* free(value); */

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
