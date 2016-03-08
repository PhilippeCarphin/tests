#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main( int argc, char** argv)
{
   char* myVar = getenv("VAR");
   char* secondVar = strdup(getenv("VAR"));
   printf("getenv()        : %s\n", getenv("VAR"));
   printf("getenv() addr   : %.16p\n",getenv("VAR"));
   printf("myVar string    : %s\n",myVar);
   printf("myVar addr      : %.16p\n",myVar);
   myVar = strdup(myVar); 
   printf("myVar string    : %s\n",myVar);
   printf("myVar addr      : %.16p\n",myVar);
   printf("secondVar string: %s\n",secondVar);
   printf("secondVar addr  : %.16p\n",secondVar);
}
