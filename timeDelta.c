#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/********************************************************************************
 * SeqDatesUtil_addTimeDelta()
 * Adds increment to datestamp specified by a timeDelta of the form -123d45j7m2s
 * but this parsing will work on more general forms: As long as each number is
 * immediately followed by d,h,m,s and the first character is +-.  For example
 * -123days,20hours,5seconds,10minutes.  There can be no spaces between the
 * number and the type specifier.
********************************************************************************/
#define MAX_DIGITS 9
char* SeqDatesUtil_addTimeDelta(char * datestamp, char * timeDelta){
   printf( "\n=================================== SeqDatesUtil_addTimeDelta ==============\n");
   char * p = timeDelta, buffer[MAX_DIGITS], * dst = buffer, type;
   int sign = (timeDelta[0] == '-' ? -1 : 1);
   int days = 0, hours = 0, minutes = 0, seconds = 0, digitCounter = 0;
   /* Skip non-numeric characters */
   while(*p != '\0' && !('0' <= *p && *p <= '9')) p++;

   while( *p != '\0' ){
      /* Read number into buffer */
      while( '0' <= *p && *p <= '9' && digitCounter < MAX_DIGITS )
         buffer[digitCounter++] = *p++;
      /* Read buffer into the right integer */
      type = *p++;
      switch(type){
         case 'd':
            days = sign*atoi(buffer); break;
         case 'h':
            hours = sign*atoi(buffer); break;
         case 'm':
            minutes = sign*atoi(buffer); break;
         case 's':
            seconds = sign*atoi(buffer); break;
         default:
            printf("SeqDatesUtil_addTimeDelta(): Encountered unknown type specifier '%c' after number %s\n", type, buffer);
      }
      /* Skip non-numeric characters */
      while(*p != '\0' && !('0' <= *p && *p <= '9')) p++;
      memset(buffer, '\0', sizeof(buffer));
      digitCounter = 0;
   }

   printf ( "TimeDelta=%s : Days=%d, hours=%d, minutes=%d, seconds=%d\n",timeDelta, days,hours,minutes,seconds);
   return NULL;
}
#undef MAX_DIGITS

int main ( int argc , char ** argv ) {
   char* timeDelta= "+1d2h3m4s";
   char * timeDelta2 = "-123d480s";
   char * nosign = "1234d480s";
   char * fuckedUpDelta = "--123hj567d";
   char * weirdDelta = "-+-+123h456h";
   char * outOfOrder = "-1s2h3d4m";
   char * too_many_type_specifiers = "-123dd";
   char * words_instead_of_chars = "-123days,25min,40sec,32hIdon't even see the code, All I see is blonde brunette redhead";
   char * random_stuff_at_the_start = "-I don't even see the code, all I see is blonde brunette redhead. 123days";
   char * come_at_me_bro = "-I don't even see the code, all I see is 1blonde, 2brunettes 3redheads. 123days";
   char * bad_type_after_num = "-HELLO123j";
   char * this_one_wont_work = "After 123days, I saw a lady with 2doubleDs. she was hot";
   char * oversize_number = "oversize 1234123412341days";
   char * giant_numbers = "bigNumbers 12345678901123412341234123412341234123412341234123412341341234123412341234124312423days";

   SeqDatesUtil_addTimeDelta("bla", timeDelta);
   SeqDatesUtil_addTimeDelta("bla", timeDelta2);
   SeqDatesUtil_addTimeDelta("bla", nosign);
   SeqDatesUtil_addTimeDelta("bla", too_many_type_specifiers);
   SeqDatesUtil_addTimeDelta("bla", words_instead_of_chars);
   SeqDatesUtil_addTimeDelta("bla", random_stuff_at_the_start);
   SeqDatesUtil_addTimeDelta("bla", bad_type_after_num);

   SeqDatesUtil_addTimeDelta("bla", outOfOrder);
   SeqDatesUtil_addTimeDelta("bla", fuckedUpDelta);
   SeqDatesUtil_addTimeDelta("bla", weirdDelta);
   SeqDatesUtil_addTimeDelta("bla", come_at_me_bro);
   SeqDatesUtil_addTimeDelta("bla", this_one_wont_work);
   SeqDatesUtil_addTimeDelta("bla", oversize_number);
   SeqDatesUtil_addTimeDelta("bla", giant_numbers);

   return 0;
}
