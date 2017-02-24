#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* #include "systime.h" */
#include <time.h>
#include <sys/time.h>
#include <mach/clock.h>
#include <mach/mach.h>
struct timespec TS;
void current_utc_time(struct timespec *ts) {

#ifdef __MACH__ // OS X does not have clock_gettime, use clock_get_time
  clock_serv_t cclock;
  mach_timespec_t mts;
  host_get_clock_service(mach_host_self(), CALENDAR_CLOCK, &cclock);
  clock_get_time(cclock, &mts);
  mach_port_deallocate(mach_task_self(), cclock);
  ts->tv_sec = mts.tv_sec;
  ts->tv_nsec = mts.tv_nsec;
#else
  clock_gettime(CLOCK_REALTIME, ts);
#endif
}

char *input, *output;
const char *values[2] = {"is","string"};
long int seconds()
{
   current_utc_time(&TS);
   return 1000*(TS.tv_sec % 100) + TS.tv_nsec /1000000;
}
long int MSEC;
/* #define VERBOSE */
char* SeqUtil_keysub( const char* _str, const char **values, const char*frontDelim ,const char* endDelim)
{
  char *strtmp=NULL,*substr=NULL,*var=NULL,*env=NULL,*post=NULL,*source=NULL;
  char *saveptr1,*saveptr2;
  static char newstr[1000];
  int start,isvar;
  int i = 0;

  strtmp = (char *) malloc( strlen(_str) + 1 ) ;
  strcpy(strtmp,_str);
  substr = strtok_r(strtmp,frontDelim,&saveptr1);
  start=0;
  while (substr != NULL){
    isvar = (strstr(substr,endDelim) == NULL) ? 0 : 1;
#ifdef VERBOSE
    printf("substr: %s\n", substr);
    printf("strstr(substr,endDelim) : %s\n", strstr(substr,endDelim));
#endif
    var = strtok_r(substr,endDelim,&saveptr2);
#ifdef VERBOSE
    printf("var : %s\n", var);
#endif

    env = getenv(var);
    post = strtok_r(NULL,"\0",&saveptr2);
    if (env == NULL){
      if (isvar > 0){
         printf("Variable %s referenced in string %s is not set in environment\n",env,_str);
         exit(1);
      } else{
	      strncpy(newstr+start,var,strlen(var));
	      start += strlen(var);
      }
    } else {
#ifdef VERBOSE
      printf("XmlUtils_resolve(): replacing %s with %s value \"%s\"\n",var,source,env);
#endif
      strncpy(newstr+start,env,strlen(env));
      start += strlen(env);
    }
    if (post != NULL){
      strncpy(newstr+start,post,strlen(post));
      start += strlen(post);
    }
    newstr[start]=0;
    substr = strtok_r(NULL,"${",&saveptr1);
#ifdef VERBOSE
    printf("end first iteration\n");
    getchar();
#endif
  }
  free(source);
  free(strtmp);
#ifdef VERBOSE
  printf("SeqUtil_keysub() result : %s\n",newstr);
#endif
  return newstr;
}

#define MAX 5000000
char * keysub_o(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];   /* Char array in which we construct the output */
   char variable[100];  /* Array into which we copy the variable name */
   register const char *src = str; /* Iterator on the characters of the input string */
   const char *value,   /* Value that will replace variable name */
              *val;     /* Iterator on value of variable */
   char * dst = output; /* Iterator on output array */
   char * var;
   int i = 0;           /* Only used for testing */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */
   register char c;
   int fdl = strlen(frontDelim),
       edl = strlen(endDelim);
   size_t len;

   while( *src != 0 ){
      /*
       * Copy until the first occurrence of startDelim. If none is found, copy
       * the whole string, and exit the loop.
       */
#if 0
      while( (c = *src++) != '$' && c != '\0' )
         *dst++ = c;
      if(c == '\0')
         break;
#else
      stopPoint = strstr(src,frontDelim);
      if(stopPoint != NULL){
         memcpy(dst,src,len=stopPoint-src);
         /* while( src < stopPoint ) *dst++ = *src++; */
         printf("src:%s\n",src);
         printf("stopPoint:%s\n",stopPoint);
         printf("len:%d\n",len);
         src+=len+fdl;
         printf("src is %s\n",src);

         dst+=len;
         *dst = '\0'; printf("output%s\n",output);getchar();
      } else {
         memcpy(dst,src,len=strlen(src));
         /* while(*src != 0) *dst++ = *src++; */
         break;
      }
#endif

      /*
       * Now *src points on the start of the front delimiter string.  Check that
       * the delimiter string is valid, and advance by the length of said
       * delimiter. We know that we can safely advance by strlen(frontDelim)
       * because we would have broken out of the loop if we couldn't
       */
      /* src += strlen(frontDelim); */

      /*
       * Copy until the first occurrence of endDelim.  We must be able to find
       * endDelim or else it means that we got invalid input. The pointer src
       * might point to the end of the string but we don't use it until the next
       * iteration, so this case will be caught when we test to start the next
       * iteration.
       */
#if 0
      var = variable;
      while( (c = *src++) != '}' )
         *var = c;
#else
      stopPoint = strstr(src,endDelim);
      if(stopPoint != NULL){
         /* char *var = variable; */
         /* while( src < stopPoint) *var++ = *src++; */
         memcpy(variable,src,len=stopPoint-src);variable[len] = 0;
         src+=edl;
      }else{
         goto delim_mismatch;
      }
#endif

      /*
       * find value of variable
       * Calling getdef, and have getdef either look in the deffile or in the
       * environment.  Everyone does his job, this functions job is to change
       * "${variable_name}" for "value".  And it's getdef's job to find the
       * value corresponding to "variable_name".
       */
      /* value = values[i++]; val = value; */
      val = getenv(variable);

      /*
       * Copy value into destination string
       */
      if( val == NULL ){
         printf("Variable %s referenced in string %s is not set in environment\n",var,str);
         return NULL;
      }
      while( (c = *val++) != '\0' )
         *dst++ = c;
   }

   /*
    * We are done, mark the end of the return string with a nul byte
    */
   *dst = '\0';

   return strdup(output);

delim_mismatch:
   printf("Front variable token %s must be accompanied by matching ending variable token %s\n",
                                                         frontDelim, endDelim);
   return NULL;
}
char * keysub(const char *str, const char ** values, const char *frontDelim, const char *endDelim)
{
   char output[1000];   /* Char array in which we construct the output */
   char variable[100];  /* Array into which we copy the variable name */
   const char *p = str; /* Iterator on the characters of the input string */
   const char *var,     /* Iterator on the characters of variable char array */
              *value,   /* Value that will replace variable name */
              *val;     /* Iterator on value of variable */
   char * dst = output; /* Iterator on output array */
   int i = 0;           /* Only used for testing */
   char *stopPoint;     /* Used to locate occurrence of delimiter string */
   size_t len;

   while( *p != 0 ){
      /*
       * Copy until the first occurrence of startDelim. If none is found, copy
       * the whole string, and exit the loop.
       */
      stopPoint = strstr(p,frontDelim);
      if(stopPoint != NULL){
         while( p < stopPoint ) *dst++ = *p++;
      } else {
         while(*p != 0) *dst++ = *p++;
         break;
      }

      /*
       * Now *p points on the start of the front delimiter string.  Check that
       * the delimiter string is valid, and advance by the length of said
       * delimiter. We know that we can safely advance by strlen(frontDelim)
       * because we would have broken out of the loop if we couldn't
       */
      p += strlen(frontDelim);

      /*
       * Copy until the first occurrence of endDelim.  We must be able to find
       * endDelim or else it means that we got invalid input. The pointer p
       * might point to the end of the string but we don't use it until the next
       * iteration, so this case will be caught when we test to start the next
       * iteration.
       */
      stopPoint = strstr(p,endDelim);
      if(stopPoint != NULL){
         char *var = variable;
         while( p < stopPoint) *var++ = *p++;
         p += strlen(endDelim);
      }else{
         goto delim_mismatch;
      }

      /*
       * find value of variable
       * Calling getdef, and have getdef either look in the deffile or in the
       * environment.  Everyone does his job, this functions job is to change
       * "${variable_name}" for "value".  And it's getdef's job to find the
       * value corresponding to "variable_name".
       */
      /* value = values[i++]; val = value; */
      val = getenv(variable);

      /*
       * Copy value into destination string
       */
      while( *val != '\0' )
         *dst++ = *val++;
   }

   /*
    * We are done, mark the end of the return string with a nul byte
    */
   *dst = '\0';

   return strdup(output);

delim_mismatch:
   printf("Front variable token %s must be accompanied by matching ending variable token %s\n",
                                                         frontDelim, endDelim);
   return NULL;
}
int test_keysub();
int test_keysub_o();
int test_SeqUtil();
int test_timing();

int main ( int argc , char ** argv )
{
   putenv("word1=is");
   putenv("word2=string");
   printf("main: putting word1=is and word2=string in environment, but not putting word3=is\n");
   test_keysub();
   test_keysub_o();
   test_SeqUtil();
   /* test_timing(); */
   return 0;
}

int test_keysub()
{
   input = "This ${word1} a ${word2}.";
   printf("\n==========test_keysub, input:%s\n ",input);
   output = keysub(input,values,"${","}");
   if( strcmp(output,"This is a string.") != 0)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This %*&$((((word1)))) a %*&$((((word2)))).";
   printf("\n==========test_keysub, input:%s\n ",input);
   output = keysub(input,values,"%*&$((((","))))");
   printf("test_keysub ");
   if( strcmp(output,"This is a string.") != 0)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   input = "This Dominicword1Racette a Dominicword2Racette.";
   printf("\n==========test_keysub, input:%s\n ",input);
   output = keysub(input,values,"Dominic","Racette");
   printf("test_keysub ");
   if( strcmp(output,"This is a string.") != 0)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);

   printf("===================================================\n");
   return 0;
}

int test_keysub_o()
{
   input = "This ${word1} a ${word2}.";
   printf("\n==========test_keysub_o, input:%s\n ",input);
   printf("===================================================\n");
   output = keysub_o(input,values,"${","}");
   printf("test_keysub_o ");
   if( strcmp(output,"This is a string.") != 0)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);
   printf("===================================================\n");
   input = "This ${word3} a ${word2}.";
   output = keysub_o(input,values,"${","}");
   printf("test_keysub_o ");
   if(output != NULL)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);
   printf("===================================================\n");
   input = "This ${word3 a ${word2.";
   output = keysub_o(input,values,"${","}");
   printf("test_keysub_o ");
   if(output != NULL)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);
   printf("===================================================\n");
   
   return 0;
}

int test_SeqUtil()
{
   printf("===================================================\n");
   input = "This ${word1} a ${word2}.";
   output = SeqUtil_keysub(input,values,"${","}");
   printf("test_SeqUtil ");
   if( strcmp(output,"This is a string.") != 0)
      printf("FAILED. ");
   else
      printf("PASSED. ");
   printf("output : %s\n",output);
   printf("===================================================\n");
   return 0;
}

int test_timing()
{
   int i;
   input = "This ${word1} a ${word2}.";
   printf("================= Timing test: original\n");
   MSEC = seconds();
   for (i = 0; i<MAX; ++i){
      output = keysub(input,values,"${","}");
   }
   MSEC = seconds() - MSEC;
   printf("Time taken is %ld msec\n", MSEC);
   
   printf("================= Timing test: using register keyword\n");
   MSEC = seconds();
   for (i = 0; i<MAX; ++i){
      output = keysub_o(input,values,"${","}");
   }
   MSEC = seconds() - MSEC;
   printf("Time taken is %ld msec\n", MSEC);
   printf("================= Timing test: SeqUtil_keysub()\n");
   MSEC = seconds();
   for (i = 0; i<MAX; ++i){
      output = SeqUtil_keysub(input,values,"${","}");
   }
   MSEC = seconds() - MSEC;
   printf("Time taken is %ld msec\n", MSEC);
   return 0;
}
