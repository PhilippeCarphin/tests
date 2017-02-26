#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#define NS_PER_SEC 1000000000
#define MS_PER_NS 1000000
#define MAX 5000000

struct Args{
   char * string;
};
typedef int (* function)(struct Args *);

void SeqUtil_stringAppend( char** source,const char* data )
{
   char* newDataPtr = NULL;
   /*do not change source if data is null*/
   if (data != NULL) {
      if ( *source != NULL ) {
         if( ! (newDataPtr = malloc( strlen(*source) + strlen( data ) + 1 )  )) {
	    return;
         }
         strcpy( newDataPtr, *source );
         strcat( newDataPtr, data );
      } else {
         if( ! (newDataPtr = malloc( strlen( data ) + 1 ) ) ) {
   	    return;
         }
         strcpy( newDataPtr, data );
      }

      free( *source );
      *source = newDataPtr;
  }
}

/* remove ^last from extension if it's in there */
char* SeqUtil_striplast( const char* str ) {
  char *noLast=NULL;
  int stringLength;

  stringLength = strlen( str );
  if (strstr( str, "^last" )){
    stringLength -= 5;
  }
  noLast = malloc( stringLength+1 ); 
  memset( noLast,'\0', stringLength+1 );
  strncpy( noLast, str, stringLength ); 
  SeqUtil_stringAppend( &noLast, "" );
  return( noLast );
}

char * phil_stripLast( const char *str)
{
#define STATIC_BUFFER
   static const char *last = "^last";
#ifdef STATIC_BUFFER
   static char noLast[100];
#else
   char *noLast;
#endif
   static size_t len;

   if( strstr(str,last) == NULL ){
#ifdef STATIC_BUFFER
      return str;
#else
      noLast = strdup(str);
#endif
      goto out;
   }

#ifdef STATIC_BUFFER
   memcpy(noLast,str,len = strlen(str)-5);
   noLast[len] = 0;
#else
   len = strlen(str) - strlen(last);
   noLast = malloc(len + 1);
   memcpy(noLast,str,len);
   noLast[len] = '\0';
#endif
out:
   return noLast;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
typedef int word;
int main ( int argc , char ** argv ) {

   unsigned long time;
   char * arg = "asdfasf^last";

   time = time_lots_of(phil_stripLast,arg);
   printf("PHIL Time = %lu\n",time);

   time = time_lots_of(SeqUtil_striplast,arg);
   printf("RON  Time = %lu\n",time);
   return 0;
}










unsigned long getCurrentTime(void)
{
   unsigned long ms;
   time_t s;
   struct timespec spec;

   clock_gettime(CLOCK_MONOTONIC, &spec);

   return NS_PER_SEC * spec.tv_sec + spec.tv_nsec;
}


unsigned long time_lots_of(function f, struct Args * args)
{
   unsigned long start_time = getCurrentTime(); 
   int i;
   for (i = 0; i < MAX; ++i){
      f(args);
   }
   return getCurrentTime() - start_time;
}
