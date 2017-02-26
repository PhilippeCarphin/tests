#define _POSIX_C_SOURCE 200809L

#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <math.h>
#include <time.h>

#define NS_PER_SEC 1000000000
#define MS_PER_NS 1000000
#define MAX 8000000

struct Args{
   char * string;
};
typedef int (* function)(struct Args *);

int with_memset(struct Args *args)
{
   char buf[2000];
   memset(buf,'\0',sizeof(buf));
   strcpy(buf, "this is a string that I'm copying");
   strcpy(buf, "this is a string that I'm copying");
   strcpy(buf, "this is a string that I'm copying");
   char * p = malloc(1000);
   free(p);
   p = malloc(1000);
   free(p);
   p = malloc(1000);
   free(p);
   return 0;
}

int no_memset(struct Args *args)
{
   char buf[2000];
   strcpy(buf, "this is a string that I'm copying");
   strcpy(buf, "this is a string that I'm copying");
   strcpy(buf, "this is a string that I'm copying");
   char * p = malloc(1000);
   free(p);
   p = malloc(1000);
   free(p);
   p = malloc(1000);
   free(p);
   return 0;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
typedef int word;
int main ( int argc , char ** argv ) {

   unsigned long int time;
   function f;
   struct Args args = { "This is a string to copy"};

   f = with_memset;
   time = time_lots_of(f,&args);
   printf("time lots of with_memset : %lu\n",time);
   f = no_memset;
   time = time_lots_of(f,&args);
   printf("  time lots of no_memset : %lu\n",time);
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
