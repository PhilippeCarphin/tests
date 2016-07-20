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
   char *val;
   int i = 0;
   char *tmp = NULL;

   while( *p != 0 ){

      
      tmp = strstr(p,frontDelim);
      printf("tmp is %s\n",tmp);
      /* Copy until the start of front delim is encountered.*/
#if 0
      while(*p != *frontDelim && *p != '\0')
         *dst++ = *p++;
#else
      if(tmp != NULL){
         while( p < tmp )
            *dst++ = *p++;
      } else {
         while(*p != 0)
            *dst++ = *p++;
         break;
      }
#endif

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

      /* Copy into variable name until a '}' is encountered*/
      while(*p != *endDelim && *p != '\0')
         *var++ = *p++;
      *var = '\0'; printf("Variable name is %s\n",variable);

      if( p != strstr(p,endDelim)) printf("Front variable token %s must be accompanied by matching ending variable token %s\n", frontDelim, endDelim);
      p += strlen(endDelim);

      /* find value of variable */
      /* Calling getdef, and have getdef either look in the deffile or in the
       * environment.  Everyone does his job, this functions job is to change
       * "${variable_name}" for "value".  And it's getdef's job to find the
       * value corresponding to "variable_name". */
      value = values[i++];
      printf("variable value is %s\n",value);

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

   return 0;
}
