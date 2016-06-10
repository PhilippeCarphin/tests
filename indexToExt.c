#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define EXT_TOKEN '+'
#define isDigit(a) ( '0' <= (a) && (a) <= '9' )
char * indexToExt(const char * index)
{
   const char * src = index;

   char ext[strlen(index)];
   char * dst = ext;

   while (*src != '\0'){

      /* get to after '=' sign */
      while (*src != '=') ++src;
      ++src;

      /* copy a '+' and everything till the ',' */
      *dst++ = EXT_TOKEN;
      while( isDigit(*src) ) *dst++ = *src++;
   }
   *dst = '\0';
   return strdup(ext);
}

int main ( int argc , char ** argv ) {

   char * index = "loop1=4,loop5=6,loop6=1729";
   char * ext = NULL;

   ext = indexToExt(index);

   if( strcmp(ext,"+4+6+1729") == 0)
      printf("TEST PASSED, ext=%s\n",ext);
   else
      printf("TEST FAILED, ext=%s\n",ext);

   return 0;
}
