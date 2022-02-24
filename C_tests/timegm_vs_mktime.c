/*
 * This test demonstrates the time difference between timegm and mktime.
 *
 * Both produce a 1900-based epoch time from a struct tm.
 *
 * timegm interprets the struct tm as a GMT time and mktime interprets it as a
 * local time.
 *
 * The test shows that timegm is about ten times faster (on the machine where I
 * tried it of course) than mktime
 *
 * We should also note that the time for the first call is really long, and that
 * the first call to mktime is a bit long too.  Whether I switch the order or
 * not, it's always the first call that is really long.  Which means that there
 * is some kind of global memory that needs to be initialized the first time.
 *
 * NOTE: Tried on a linux machine where mktime was about 800 ns after the first
 * two calls, then timegm at about 100ns including the first call.
 *
 * On MacOS, it was about 8000-9000 per call for both timegm and mktime so the
 * implementation is clearly different.
 */

#include <time.h>
#include <stdlib.h>
#include <stdio.h>

char *datestamps[] = {
   "2018-03-06 13:49:50",
   "2018-03-06 13:46:38",
   "2018-03-06 11:23:00",
   "2018-03-06 12:05:16"
};

static unsigned long getCurrentTime(void);
int main(void)
{
   struct tm t;
   t.tm_year = 2018;
   t.tm_mon = 6;
   t.tm_mday = 12;
   t.tm_hour = 8;
   t.tm_min = 42;
   t.tm_sec = 37;


   long unsigned int t0, t1;


   for(int i = 0; i < 10; ++i){
      t0 = getCurrentTime();
      mktime(&t);
      t1 = getCurrentTime();
      printf("mktime %lu nanoseconds\n",t1-t0);
   }

   for(int i = 0; i < 10; ++i){
      t0 = getCurrentTime();
      timegm(&t);
      t1 = getCurrentTime();
      printf("timegm %lu nanoseconds\n",t1-t0);
   }
}

#define MS_PER_SEC 1000
#define US_PER_SEC 1000000
#define NS_PER_SEC 1000000000
static unsigned long getCurrentTime(void)
{
   struct timespec spec;

   clock_gettime(CLOCK_MONOTONIC, &spec);

   return NS_PER_SEC * spec.tv_sec + spec.tv_nsec;
}
