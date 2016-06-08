#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int SeqUtil_tokenCount( const char* source, const char* tokenSeparator )
{
   // hello
   int count = 0;
   char *tmpSource = NULL, *tmpstrtok = NULL; 

   tmpSource = strdup(source);
   tmpstrtok = (char*) strtok( tmpSource, tokenSeparator );

   while ( tmpstrtok != NULL ) {
        count++;
        tmpstrtok = (char*) strtok(NULL, tokenSeparator);
   }

   free(tmpSource);
   return count;
}
int isDelim( char c, char * delim){
   char * d = delim;
   while ( *d != '\0')
      if ( c == *d++)
         return 1;
   return 0;
}
int phil_tokenCount( const char* source, const char* tokenSeparator )
{
   int count = 0;
   char * p = (char *)source;
   while ( *p != '\0' ){
      while ( isDelim(*p,tokenSeparator) ) p++;
      if( *p == '\0' ) return count;
      else count++;
      while ( !isDelim(*p,tokenSeparator) && *p != '\0' ) p++;
   }
   return count;
}

#define tokenCount SeqUtil_tokenCount

int main ( int argc , char ** argv ) {

   char * path1 = "/this/is/a/path/it/has/how/many/tokens";
   char * path2 = "this/is/a/path/it/has/how/many/tokens";
   char * path3 = "/this/is/a/path/it///has/how/many/tokens";
   char * path4 = "/this/is/a/path/it///has/how/many/tokens/";

   printf("the path %s has %d tokens\n",path1,tokenCount(path1,"/"));
   printf("the path %s has %d tokens\n",path2,tokenCount(path2,"/"));
   printf("the path %s has %d tokens\n",path3,tokenCount(path3,"/"));
   printf("the path %s has %d tokens\n",path4,tokenCount(path4,"/"));

   char * tmpPath = strdup( path1 );
   char * pathToken = NULL;
   int count = 0;
   int totalCount = SeqUtil_tokenCount(path1,"/");

   pathToken = strtok(tmpPath, "/");count++;
   while ( pathToken != NULL ){
      printf("This is the current token:%s, it is token number %d\n",pathToken,count);
      if( count == totalCount )
         printf("   This is the last token.  Do something special with it\n");
      pathToken = strtok( NULL, "/" ); count++;
   }


   return 0;
}
