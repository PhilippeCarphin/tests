#define _POSIX_C_SOURCE 200809L
#define _XOPEN_SOURCE
#define _SVID_SOURCE

#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>
#include <stdlib.h>

#define NS_PER_SEC 1000000000
#define MS_PER_NS 1000000
#define MAX 50000

struct Args{
   char * string;
};
typedef int (* function)(struct Args *);

int with_dup(struct Args *args)
{
   free(strdup(getenv("SEQ_EXP_HOME")));
   /* strdup(getenv("SEQ_EXP_HOME")); */
   return 0;
}

int no_dup(struct Args *args)
{
   getenv("SEQ_EXP_HOME");
   return 0;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
typedef int word;
int main ( int argc , char ** argv ) {
   putenv("SEQ_EXP_HOME=/users/dor/afsi/phc/Documents/sample");


   unsigned long int time = 0;
   function f;
   struct Args args = { "This is a string to copy"};

   f = with_dup;
   time = time_lots_of(f,&args);
   printf("with_dup : %lu\n",time);
   f = no_dup;
   time = time_lots_of(f,&args);
   printf("   no_dup: %lu\n",time);
   /* f(&args); */
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
