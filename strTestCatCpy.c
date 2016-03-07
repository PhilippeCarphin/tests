#include <string.h>
#include <stdio.h>

int main ( int argc, int argv )
{
   char buffer[80];

   strcpy(buffer,"I\'m singing in the rain");

   printf("BUFFER: %s\n", buffer);

   strcat(buffer, "what a wonderful feeling");

   
   printf("BUFFER: %s\n", buffer);


}
