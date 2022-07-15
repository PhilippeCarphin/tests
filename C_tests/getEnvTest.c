#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char** argv)
{
   char* myVar = getenv("VAR");
   printf("getenv(\"VAR\")        : %s\n", getenv("VAR"));
   printf("getenv(\"VAR\") addr   : %.16p\n",getenv("VAR"));
   printf("myVar string         : %s\n",myVar);
   printf("myVar addr           : %.16p\n",myVar);

   if(myVar == NULL){
       printf("Cannot strdup(NULL)\n");
       return 0;
   }
   char *secondVar = strdup(myVar);

   printf("secondVar string     : %s\n",secondVar);
   printf("secondVar addr       : %.16p\n",secondVar);

   return 0;
}
