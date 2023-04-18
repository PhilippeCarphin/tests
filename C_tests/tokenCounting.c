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

int isDelim( char c, const char * delim){
   const char * d = delim;
   while ( *d != '\0')
      if ( c == *d++)
         return 1;
   return 0;
}

int phil_tokenCount( const char* source, const char* tokenSeparator )
{
   int count = 0;
   char * p = strdup(source);
   while ( *p != '\0' ){

      /* Skip delimiters */
      while ( isDelim(*p,tokenSeparator) ) p++;

      /* If *p == 0, we are done, otherwise we found the start of a new token */
      if( *p == '\0' ) return count;
      else count++;

      /* go to the end of the token. */
      while ( !isDelim(*p,tokenSeparator) && *p != '\0' ) p++;
   }
   return count;
}

/********************************************************************************
 * Based on the implementation of strtok from Apple open source:
 * http://opensource.apple.com//source/Libc/Libc-167/string.subproj/strtok.c
********************************************************************************/
int strtok_style__tokenCount(
   register const char * s,
   register const char * delim)
{
   register const char * dp;
   register int c, dc;
   int count = 0;
   register const char * p = s;
   /* if( s == NULL || *s == 0 ) return count; */

cont:
   /*
    * With the goto, this is like two nested loops but the condition for
    * advancing is to go through the entire for loop without going in the if.
    *
    * If we make the for loop into a function, then it becomes easy:
    *   while ( isDelim(*p, delim) ) p++;
    * but if we want to do it without the overhead of a function call
    * for either performance reasons or because we feel like we should
    * be able to just write two nested loops, it becomes a bit clunky:
    * 
    *   is_delim = 1;
    *   while(is_delim){
    *     c = *s++;
    *     is_delim = 0;
    *     for(dp = delim; (dc = *dp++) != 0;){
    *        if( c == dc )
    *           is_delim = 1;
    *        }
    *     }
    *   }
    *
    * but this is_delim state variable is kind of ugly whereas the goto
    * version makes it very clear that the condition for advancing passed
    * this step is going through the whole for loop without going through
    * the if. I.E. we checked 'c' against every delim character and none
    * of them matched.
    */
   c = *s++;
   for(dp = delim; (dc = *dp++) != 0;){
      if( c == dc )
         goto cont;
   }

   /* If we're at the end of the string we are done, otherwise, we've found the
    * start of a token */
   if( c == 0 ) return count;
   else count++;

   /* Skip non-delimiters until the end of the string or until we find a
    * delimiter ('/0' included */
   for(;;){
      c = *s++;
      dp = (char *)delim;
      do{
         if((dc = *dp++) == c){
            if( c == 0 )
               return count;
            else
               goto cont;
         }
      }while(dc != 0);
   }
}

#define tokenCount strtok_style__tokenCount

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
