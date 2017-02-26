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

int strlen_lib(struct Args *args)
{
   return 0;
}

int strlen_phil(struct Args *args)
{
   return 0;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
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
   int i;
   for (i = 0; i < MAX; ++i){
      f(args);
   }
   return getCurrentTime() - start_time;
}
