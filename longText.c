#include <stdlib.h>
#include <stdio.h>


int main ( int argc, char * argv[]){
   char* longstring = "\
      This is a \n\n\
      multi\n\
      line\n\
      \n\
      string\n\
      You just gotta escape the linebreaks in the code.\n\
      and make sure that there is no space after the \"\\\"\n";
   printf("%s",longstring);
   return 0;
}
