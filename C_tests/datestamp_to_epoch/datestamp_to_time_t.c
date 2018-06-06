/*
 * This test shows how to convert a datestamp received as a string and turn it
 * into a struct tm then into a time_t
 */
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
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

int tm_to_epoch(struct tm* t, time_t *e);
int epoch_to_tm(time_t *e, struct tm *t);

/*******************************************************************************
 * Convert between sql datestamp and epoch time
*******************************************************************************/
int sql_datestamp_to_epoch(const char *datestamp, time_t *e)
{
   int retval = 0;
   struct tm t;
   if((retval = sql_datestamp_to_tm(datestamp, &t)) != SUCCESS){
      DBG_PRINT("sql_datestamp_to_tm() failure\n");
      return retval;
   }

   if((retval = tm_to_epoch(&t, e)) != SUCCESS){
      DBG_PRINT("tm_to_epoch() failure\n");
      return retval;
   }

   return retval;
}
int epoch_to_sql_datestamp(time_t *e, char *buff)
{
   int retval = SUCCESS;
   struct tm t;

   if((retval = epoch_to_tm(e, &t)) != SUCCESS){
      DBG_PRINT("epoch_to_tm() failure\n");
      return retval;
   }

   if((retval = tm_to_sql_datestamp(&t, buff)) != SUCCESS){
      DBG_PRINT("tm_to_sql_datestamp() failure\n");
      return retval;
   }

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

   if(retval == EOF){
      DBG_PRINT("sscanf() failure\n");
      return FAILURE;
   } else if( retval != 6){
      DBG_PRINT("sscanf() could not find 6 elements in datestamp %s\n", datestamp);
      return FAILURE;
   }

   t->tm_year -= EPOCH_START_YEAR; // year 0 is 1900
   t->tm_mon -= 1; // Months are 0-11

   return SUCCESS;
}
int tm_to_sql_datestamp(struct tm *t, char *buffer)
{
   if(strftime(buffer, 100, "%Y-%m-%d %H:%M:%S", t) <= 0){
      DBG_PRINT("strftime() failure\n");
      return FAILURE;
   }
   return SUCCESS;
}

/*******************************************************************************
 * Be careful about local time.  Localtime says it, it considers localtime, and
 * so does mktime().  See
 * https://www.tutorialspoint.com/c_standard_library/c_function_mktime.htm
*******************************************************************************/
int tm_to_epoch(struct tm* t, time_t *e)
{
   *e = mktime(t); // Considers local time
   return SUCCESS;
}
int epoch_to_tm(time_t *e, struct tm *t)
{
   *t = *localtime(e); // considers local time
   return SUCCESS;
}

#ifdef __MAIN__
/*******************************************************************************
 * Run tests on the arguments of the program
*******************************************************************************/
void test_conversion(const char *datestamp);
int main(int argc, char **argv)
{
   for(int i = 1; i < argc; i++){
      const char *datestamp = argv[i];
      test_conversion(datestamp);
   }
   struct tm time;
   memset(&time, 0, sizeof(struct tm));
}

void test_conversion(const char *datestamp)
{
   time_t epoch_time;
   if(sql_datestamp_to_epoch(datestamp, &epoch_time)){
      DBG_PRINT("Error converting from datestamp to epoch\n");
      exit(-1);
   }

   char re_datestamp[100];
   if(epoch_to_sql_datestamp(&epoch_time, re_datestamp)){
      DBG_PRINT("Error converting from epoch to datestamp\n");
      exit(-2);
   }

   printf("datestamp=%s -> time_t=%ld -> ctime=%s\n", datestamp, epoch_time, re_datestamp);

   if(strcmp(datestamp, re_datestamp) != 0){
      printf("TEST FAILED: %s -> %s\n", datestamp, re_datestamp);
   }
}

#endif
