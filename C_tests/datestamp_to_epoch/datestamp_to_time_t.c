/*
 * This test shows how to convert a datestamp received as a string and turn it
 * into a struct tm then into a time_t
 */

/*
 * _BSD_SOURCE is so that I can have the timegm() function from time.h
 * Also, I put it at the top because it seems like stdlib.h defines it.
 * You would think that if stdlib.h defines it, then all I have to do is put the
 * include of time.h below but if I do that, I still get an implicit declaration
 * warning for timegm
 */
#define _BSD_SOURCE
#define _POSIX_C_SOURCE 200809L
#include <time.h>

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define PHIL_DEBUG
#include "../debug.h"


// https://en.wikipedia.org/wiki/Epoch_(reference_date)
// https://www.tutorialspoint.com/c_standard_library/c_function_mktime.htm // (Parameters section)
const int EPOCH_START_YEAR = 1900;

const int SUCCESS = 0;
const int FAILURE = -1;

int sql_datestamp_to_epoch(const char *datestamp, time_t *e);
int epoch_to_sql_datestamp(time_t *e, char *buff);

int sql_datestamp_to_tm(const char *datestamp, struct tm *t);
int tm_to_sql_datestamp(struct tm *t, char *buff);

int gmt_tm_to_epoch(struct tm* t, time_t *e);
int epoch_to_tm_gmt(time_t *e, struct tm *t);

int local_tm_to_epoch(struct tm* t, time_t *e);
int epoch_to_tm_local(time_t *e, struct tm *t);

/*******************************************************************************
 * Convert between sql datestamp and epoch time
*******************************************************************************/
int sql_datestamp_to_epoch(const char *datestamp, time_t *e)
{
   int retval = 0;
   struct tm t;
   if((retval = sql_datestamp_to_tm(datestamp, &t)) != SUCCESS){
      DBG_PRINT("error: sql_datestamp_to_tm() failure\n");
      goto err;
   }

   if((retval = gmt_tm_to_epoch(&t, e)) != SUCCESS){
      DBG_PRINT("error: tm_to_epoch() failure\n");
      goto err;
   }

   return retval;
err:
   *e = 0;
   return retval;
}
int epoch_to_sql_datestamp(time_t *e, char *buff)
{
   int retval = SUCCESS;
   struct tm t;

   if((retval = epoch_to_tm_local(e, &t)) != SUCCESS){
      DBG_PRINT("error: epoch_to_tm() failure\n");
      goto err;
   }

   if((retval = tm_to_sql_datestamp(&t, buff)) != SUCCESS){
      DBG_PRINT("error: tm_to_sql_datestamp() failure\n");
      goto err;
   }

   return retval;
err:
   *buff = 0;
   return retval;
}

/*******************************************************************************
 * Convert between sql_datestamp and struct tm
*******************************************************************************/
int sql_datestamp_to_tm(const char *datestamp, struct tm *t)
{
   int retval = SUCCESS;

   retval = sscanf(datestamp, "%d-%d-%d %d:%d:%d",
         &t->tm_year, &t->tm_mon, &t->tm_mday,
         &t->tm_hour, &t->tm_min, &t->tm_sec
   );
   t->tm_mon -= 1; // Months are 0-11

   if(retval == EOF){
      DBG_PRINT("error: sscanf() failure\n");
      goto err;
   } else if( retval != 6){
      DBG_PRINT("error: sscanf() could not find 6 (yyyy-mm-dd HH:MM:SS) elements in datestamp %s\n", datestamp);
      goto err;
   }

   if(t->tm_year < 0 || (t->tm_mon < 0 || 12 <= t->tm_mon ) || t->tm_mday < 0
      || t->tm_hour < 0 || t->tm_min < 0 || t->tm_sec < 0){
      DBG_PRINT("error: Invalid values found in datestamp %s\n", datestamp);
      goto err;
   }

   t->tm_year -= EPOCH_START_YEAR; // year 0 is 1900

   return SUCCESS;
err:
   memset(t, 0, sizeof *t);
   return FAILURE;
}
int tm_to_sql_datestamp(struct tm *t, char *buff)
{
   if(strftime(buff, 100, "%Y-%m-%d %H:%M:%S", t) <= 0){
      DBG_PRINT("error: strftime() failure\n");
      goto err;
   }
   return SUCCESS;
err:
   *buff = 0;
   return FAILURE;
}

/*******************************************************************************
 * Conversion between struct tm and time_t.  Local and GMT versions.
*******************************************************************************/
int gmt_tm_to_epoch(struct tm* t, time_t *e)
{
   *e = timegm(t); // Considers local time
   return SUCCESS;
}
int epoch_to_tm_gmt(time_t *e, struct tm *t)
{
   *t = *gmtime(e); // considers local time
   return SUCCESS;
}

int local_tm_to_epoch(struct tm* t, time_t *e)
{
   *e = mktime(t); // Considers local time
   return SUCCESS;
}
int epoch_to_tm_local(time_t *e, struct tm *t)
{
   *t = *localtime(e); // considers local time
   return SUCCESS;
}

#ifdef __MAIN__
/*******************************************************************************
 * Run tests on the arguments of the program
*******************************************************************************/
static unsigned long getCurrentTime(void);
void test_conversion(const char *datestamp);
char *datestamps[] = {
   "2018-03-06 13:49:50",
   "2018-03-06 13:46:38",
   "2018-03-06 11:23:00",
   "2018-03-06 12:05:16",
   "2018-03-06 14:15:00",
   "2018-03-06 10:33:00",
   "2018-03-06 13:06:00",
   "2018-03-06 13:24:00",
   "2018-03-06 -11:14:00",
   "2018-77-06 14:10:00",
   "2018-06- 22:54:30"
};

int main(int argc, char **argv)
{
   for(int i = 0; i < sizeof(datestamps)/sizeof(*datestamps) ; i++){
      const char *datestamp = datestamps[i];
      test_conversion(datestamp);
   }
   struct tm time;
   memset(&time, 0, sizeof(struct tm));
}

void test_conversion(const char *datestamp)
{
   time_t epoch_time;
   if(sql_datestamp_to_epoch(datestamp, &epoch_time)){
      DBG_PRINT("Error converting from datestamp=%s to epoch\n", datestamp);
      // exit(-1);
   }

#if 0
   char re_datestamp[100];
   if(epoch_to_sql_datestamp(&epoch_time, re_datestamp)){
      DBG_PRINT("Error converting from epoch to datestamp\n");
      // exit(-2);
   }

   fprintf(stderr, "datestamp=%s -> time_t=%ld -> ctime=%s\n", datestamp, epoch_time, re_datestamp);

   if(strcmp(datestamp, re_datestamp) != 0){
      fprintf(stderr, "TEST FAILED: %s -> %s\n", datestamp, re_datestamp);
   }
#endif

   long unsigned int t0, t1;
   time_t ep;
   struct tm t;
   sql_datestamp_to_tm(datestamps[3], &t);
   t0 = getCurrentTime();
   ep = timegm(&t);
   t1 = getCurrentTime();
   printf("It took %lu nanoseconds\n",t1-t0);
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

#endif
