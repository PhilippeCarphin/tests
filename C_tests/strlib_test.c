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

int copy_strcpy(struct Args *args)
{
   char * str = args->string;
   size_t len = strlen(str) + 1;
   char * newstr = malloc(len);
   strcpy(newstr,str);
   free(newstr);
   return 0;
}

int copy_memcpy(struct Args *args)
{
   char * str = args->string;
   size_t len = strlen(str)+1;
   char * newstr = malloc(len);
   memcpy(newstr,str,len);
   free(newstr);
   return 0;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
int main ( int argc , char ** argv ) {

   unsigned long time;
   function f;

   struct Args args;
   args.string = "TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version\
      TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version\
      TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version\
      TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version\
      TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version\
      TThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionThis is my string that I want to copy.  I think if I make it longer that will favor the memcpy versionhis is my string that I want to copy.  I think if I make it longer that will favor the memcpy version";

   f = copy_strcpy;
   time = time_lots_of(f,&args);
   printf("copy_strcpy : time = %ld\n",time);

   f = copy_memcpy;
   time = time_lots_of(f,&args);
   printf("copy_memcpy : time = %ld\n",time);
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
