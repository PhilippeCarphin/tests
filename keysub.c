#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];   /* Char array in which we construct the output */
   char var_name[100];  /* Array into which we copy the variable name */
   const char *src=str, /* Iterator on the characters of the input string */
              *value;   /* Value that will replace variable name */
   char * dst = output; /* Iterator on output array */
   int i = 0;           /* Only used for testing */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */
   size_t l, fl = strlen(frontDelim), el = strlen(endDelim);
   register char c;

   while( *src != 0 ){

   /* PART 1 : COPY UNTIL NEXT VARIABLE */
      /* find the next occurrence of startDelim. If none is found, copy */
      stopPoint = strstr(src,frontDelim);
      if(stopPoint != NULL){
         /* Copy src-stopPoint bytes into dst */
         memcpy(dst,src,l = stopPoint - src);
         /* we advance the pointers */
         src+=l+fl;
         dst+=l;
      } else {
         while((c=*src++) != 0) *dst++ = c;
         goto done; /* I don't like breaks because it's less obvious where it goes */
      }

   /* PART 2 : COPY THE VARIABLE NAME */
      /* Then we find the next end delimiter */
      stopPoint = strstr(src,endDelim);
      if(stopPoint != NULL){
         /* copy from src to endDelim ("word1") into the var_name */
         memcpy(var_name,src,l = stopPoint-src);var_name[l] = '\0';
         /* Advance the src pointer */
         src += l + el;
      }else{
         goto delim_mismatch;
      }

   /* PART 3 : GET THE VALUE OF THE VARIABLE */
      /* find value of variable */
      value = values[i++];
      /*
       * if( getFromEnv )
       *    value = getenv(var_name);
       * else
       *    value = SeqUtil_getdef(...);
       */

   /* PART 4 : COPY THE VARIABLE'S VALUE IN THE OUTPUT STRING */
      /* Copy value into destination string.  The dst pointer advances as we copy. */
      l = strlen(value);
      memcpy(dst,value,l);
      dst += l;

      /*
       * if( !getFromEnv )
       *    free(value);
       */
   }

done:
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
