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

int copy_lib(struct Args *args)
{
   char buffer[1000];
   size_t l = strlen(args->string);
   memcpy(buffer,args->string,l);
   buffer[l] = 0;
   /* printf("%s\n",buffer); */
   return 0;
}

int copy_phil(struct Args *args)
{
   char buffer[1000];
   register const char *src = args->string;
   register       char *dst = buffer;
   register char c;
   while((c = *src++)) *dst++ = c;
   *dst = 0;
   return 0;
}

unsigned long getCurrentTime(void);
unsigned long time_lots_of(function f, struct Args *);
typedef int word;
int main ( int argc , char ** argv ) {

   unsigned long int time;
   function f = copy_lib;
   struct Args args = { "This is a string to copy"};

   time = time_lots_of(f,&args);
   printf(" time lots of copy_lib : %lu\n",time);
   f = copy_phil;
   time = time_lots_of(f,&args);
   printf("time lots of copy_phil : %lu\n",time);
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
   for ( int i = 0; i < MAX; ++i){
      f(args);
   }
   return getCurrentTime() - start_time;
}
