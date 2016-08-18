#include <stdlib.h>
#include <string.h>
#include <stdio.h>

typedef int (* function)(struct args *);
struct Args{
   int arg1;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *)

int main ( int argc , char ** argv ) {

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
   for ( int i = 0; i < MAX; ++i){
      tc(args);
   }
   return getCurrentTime() - start_time;
}
