#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void concat(char * str1, char * str2){
   char concatenated[strlen(str1) + strlen(str2) + 1];
   sprintf(concatenated, "%s%s", str1,str2);
   printf("concatenated: %s\n", concatenated);
}
void concat2(char * str1, char *str2){
   char concatenated[1000];
   sprintf(concatenated, "%s%s", str1,str2);
   printf("concatenated: %s\n", concatenated);
}

void m_concat(char * str1, char *str2){
   char *concatenated = (char*) malloc( strlen(str1) + strlen(str2) + 1);
   sprintf(concatenated, "%s%s", str1,str2);
   printf("concatenated: %s\n", concatenated);
}

int main ( int argc , char ** argv ) {
   char *str1 = "first string.",
        *str2 = "second string.";
   goto after_printf;
   printf("HELLO");
after_printf:
   concat (str1,str2);
   concat2 (str1,str2);
   m_concat (str1,str2);

   

   return 0;
}
