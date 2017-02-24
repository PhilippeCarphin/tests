#include <stdlib.h>
#include <string.h>
#include <stdio.h>

char *reverse_string(const char *str)
{
   size_t len = strlen(str);
   const char *p = str + len - 1;
   char *output = malloc(len + 1);
   char *q = output;
   while( p != str-1){
      printf("%s(): *p:%c\n",__func__,*p);
      *q++ = *p--;
   }
   *q = '\0';
   return output;
}


int main(void){
   const char *input = "This is my input";

   printf("output: %s\n",reverse_string(input));
   return 0;
}

   
