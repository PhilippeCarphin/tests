#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#define MAX 10000000
#define NS_PER_SEC 1000000000
#define MS_PER_NS 1000000



typedef int (* TokenCounter)(const char * s, const char * delim);

/********************************************************************************
 * The one that does unnecessary copying
********************************************************************************/
int SeqUtil_tokenCount( const char* source, const char* tokenSeparator )
{
   int count = 0;
   char *tmpSource = NULL, *tmpstrtok = NULL; 

   tmpSource = (char*) malloc( strlen( source ) + 1 );
   strcpy( tmpSource, source );
   tmpstrtok = (char*) strtok( tmpSource, tokenSeparator );

   while ( tmpstrtok != NULL ) {
        count++;
        tmpstrtok = (char*) strtok(NULL, tokenSeparator);
   }

   free(tmpSource);
   return count;
}

/********************************************************************************
 * Part of phil_tokenCount
********************************************************************************/
int isDelim(const char c,const char * delim){
   const char * d = delim;
   while ( *d != '\0')
      if ( c == *d++)
         return 1;
   return 0;
}

/********************************************************************************
 * The one that I coded in a natural way
********************************************************************************/
int natural_tokenCount( const char* source, const char* tokenSeparator )
{
   int count = 0;
   char * p = (char *)source;
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
 * Weird old-school C declaration of parameters
********************************************************************************/
int strtok_style_tokenCount( s, delim )
   register const char * s;
   register const char * delim;
{
   register char * spanp;
   register int c, sc; /* c is the current character of the string, sc is the
                          current delimiter */
   int count = 0;

   /* if( s == NULL || *s == 0 ) return count; */

cont:
   /* Skip delimiters */
   c = *s++;
   for( spanp = (char *) delim; (sc = *spanp++) != 0;){
      if( c == sc )
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
      spanp = (char *)delim;
      do{
         if((sc = *spanp++) == c){
            if( c == 0 )
               return count;
            else
               goto cont;
         }
      }while(sc != 0);
   }
}

unsigned long getCurrentTime(void)
{
   unsigned long ms;
   time_t s;
   struct timespec spec;

   clock_gettime(CLOCK_MONOTONIC, &spec);

   return NS_PER_SEC * spec.tv_sec + spec.tv_nsec;
}


unsigned long time_lots_of(TokenCounter tc, const char * s, const char * delim)
{
   unsigned long start_time = getCurrentTime(); 
   for ( int i = 0; i < MAX; ++i){
      tc(s,delim);
   }
   return getCurrentTime() - start_time;
}


#define SEQ_UTIL 0
#define NATURAL 1
#define STRTOK_STYLE 2

int main ( int argc , char ** argv ) {

   TokenCounter tokenCounters[3] = { SeqUtil_tokenCount, natural_tokenCount, strtok_style_tokenCount};
   const char * names[3] = { "SeqUtil_tokenCount", "natural_tokenCount", "strtok_style_tokenCount"};
   const char * path1 = "/this/is/a/path/it/has/how/many/tokens";
   const char * path2 = "this/is/a/path/it/has/how/many/tokens";
   const char * path3 = "/this/is/a/path/it///has/how/many/tokens";
   const char * path4 = "/this/is/a/path/it///has/how/many/tokens/";

#if 0
   if ( argc == 1 )
   {

      for (int i = 3; i--;){
         printf("\n\nTesting %s()\n",names[i]);
         printf("the path %s has %d tokens\n",path1,tokenCounters[i](path1,"/"));
         printf("the path %s has %d tokens\n",path2,tokenCounters[i](path2,"/"));
         printf("the path %s has %d tokens\n",path3,tokenCounters[i](path3,"/"));
         printf("the path %s has %d tokens\n",path4,tokenCounters[i](path4,"/"));
      }
   }
#endif

   unsigned long times[3];

   for ( int i = 3; i--;)
      times[i] = time_lots_of(tokenCounters[i], path1, "/");

   for( int i = 3; i--;)
      printf("Function %s() took %lu milliseconds\n", names[i], times[i]/MS_PER_NS);

   if ( times[STRTOK_STYLE] < times[NATURAL] && times[STRTOK_STYLE] < times[SEQ_UTIL] )
      printf("\nstrtokStyle is the fastest, as it should be\n");
   else
      printf("\nWhy the hell is Strtok_style not the fastest\n");

   if ( times[NATURAL] < times[SEQ_UTIL] )
      printf("\nPhil is faster than Seq_util, as it should be\n");
   else
      printf("\nSeqUtil is faster than natural!!! how can this be,\ndoes doing strlen(), malloc(), strcpy() and free()\nmake us go back in time or something\n");

   return 0;
}
