#include <stdlib.h>
#include <string.h>
#include <stdio.h>

static char * EXT_TOKEN = "+";
char * indexToExt(const char * index)
{
   const char * src = index;
   char ext[strlen(index)];
   char * dst = ext;
   while (*src != '\0'){
      /* Skip the left hand side of the '=' */
      while (*src != '=') ++src; ++src;

      /* copy EXT_TOKEN */
      const char * tok = EXT_TOKEN;
      while ( *tok != '\0' ) *dst++ = *tok++;

      /* copy the right hand side of the '=' */
      while( *src != ',' && *src != '\0') *dst++ = *src++;
   }
   *dst = '\0';
   return strdup(ext);
}

int main ( int argc , char ** argv ) {

   char * index = "loop1=4,loop5=6,loop6=1729";
   char * expected = "+4+6+1729";
   char * ext = NULL;

   ext = indexToExt(index);

   if( strcmp(ext,expected) == 0)
      printf("TEST PASSED, ext=%s\n",ext);
   else
      printf("TEST FAILED, ext=%s\n",ext);


   index = "loop1=phil,loop2=dominic,loop3=vincent";
   expected = "+phil+dominic+vincent";
   ext = indexToExt(index);

   if( strcmp(ext,expected) == 0)
      printf("TEST PASSED, ext=%s\n",ext);
   else
      printf("TEST FAILED, ext=%s\n",ext);


   return 0;
}
