#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main ( int argc , char ** argv ) {

   char * line = "   KEY\t\t = \t\t value \t\t  ";
   char defval[100];
   char defkey[100];

   sscanf( line, " %[^= \t] = %[^\n \t]", defkey, defval );

   printf("line=%s--\n",line);
   printf("Defkey=%s--\n",defkey);
   printf("Defval=%s--\n",defval);
   return 0;
}
