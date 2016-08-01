#define _XOPEN_SOURCE
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];      /* Char array in which we construct the output */
   char * dst = output;    /* Iterator on output array */
   char var_name[100];     /* Array into which we copy the variable name */
   const char *src=str,    /* Iterator on the characters of the input string */
              *value,      /* Value that will replace variable name */
              *stopPoint;  /* Used to locate occurrence of delimiter string */
#define GET_FROM_ENV
#ifndef GET_FROM_ENV
   int i = 0;              /* Only used for testing */
#else
   int getFromEnv = 1;     /* getFromEnv = (_deffile == NULL) */
#endif
   size_t len, fl = strlen(frontDelim), el = strlen(endDelim);

   while( *src != 0 ){
   /* PART 1 : COPY UNTIL NEXT VARIABLE */
      stopPoint = strstr(src,frontDelim);
      if(stopPoint != NULL){
         memcpy(dst,src,len=stopPoint-src);
         src+=len+fl; dst+=len;
      } else {
         memcpy(dst,src,len=strlen(src));
         dst += len;
         goto done; /* I don't like breaks because it's less obvious where it goes */
      }

   /* PART 2 : COPY THE VARIABLE NAME */
      stopPoint = strstr(src,endDelim);
      if(stopPoint != NULL){
         memcpy(var_name,src,len=stopPoint-src);var_name[len] = '\0';
         src += len + el;
      }else{
         goto delim_mismatch;
      }

   /* PART 3 : GET THE VALUE OF THE VARIABLE */
#ifndef GET_FROM_ENV
      value = values[i++];
#else
      if( getFromEnv ){
         value = getenv(var_name);
      } else {
         ;
         /* value = SeqUtil_getdef(...); */
      }
      if( value == NULL ){
         fprintf(stderr,"ERROR: Variable %s is referenced but no value was found\n",var_name);
         exit(1);
      }
#endif

   /* PART 4 : COPY THE VARIABLE'S VALUE IN THE OUTPUT STRING */
      /* Possible error: value may not have been found */
      memcpy(dst,value,len=strlen(value));
      dst += len;
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
#ifdef GET_FROM_ENV
   printf("Putting word1=is and word2=string in environment\n\n");
   putenv("word1=is");
   putenv("word2=string");
#endif
   
   const char *input = "This ${word1} a ${word2}.";
   printf("input:%s\n",input);
   char * output = keysub(input,values,"${","}");
   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This %*&$((((word1)))) a %*&$((((word2)))).";
   printf("input:%s\n",input);
   output = keysub(input,values,"%*&$((((","))))");
   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This Dominicword1Racette a Dominicword2Racette.";
   printf("input:%s\n",input);
   output = keysub(input,values,"Dominic","Racette");
   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This Dominicword1Racette a Dominicwor2Racette.";
   printf("input:%s\n",input);
   output = keysub(input,values,"Dominic","Racette");
   if( strcmp(output,"This is a string.") != 0)
      printf("Test failed. ");
   else
      printf("Test passed. ");

   printf("output : %s\n",output);
   return 0;
}
