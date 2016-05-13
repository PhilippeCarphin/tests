#include <stdlib.h>
#include <string.h>
#include <stdio.h>
char * SeqUtil_prePadString( char * string, size_t paddedLength, char paddingChar){
   char * paddedString = malloc( (paddedLength+1)*sizeof(char) );
   size_t i=0, padding = paddedLength-strlen(string);
   char *dst = paddedString+padding, *src = string;
   while( i < padding)
      paddedString[i++] = paddingChar;
   while(*src != '\0')
      *dst++ = *src++;
   *dst = '\0';
   return paddedString;
}

char * SeqUtil_postPadString( char * string, int paddedLength, char paddingChar){
   char * paddedString = malloc( (paddedLength+1)*sizeof(char) );
   int i = strlen(string);
   strcpy( paddedString, string);
   while( i < paddedLength )
      paddedString[i++] = paddingChar;
   paddedString[paddedLength] = '\0';
   return paddedString;
}
#define PAD 14
char * SeqDatesUtil_addTimeDelta( char * datestamp, char * timeDelta ){
   /* Because the timeDelta may not be 14 chars long, we have to go from the end */
   char * padded_delta = SeqUtil_prePadString(timeDelta,PAD,'0');
   char * p = padded_delta + PAD - 1;
   char second_string[3] = "00",
        minute_string[3] = "00",
        hour_string[3] = "00",
        day_string[3] = "00";
   int i = 1;
      for(i = 1; i >= 0;)
         second_string[i--] = *p--;
      for(i = 1; i >= 0;)
         minute_string[i--] = *p--;
      for(i = 1; i >= 0;)
         hour_string[i--] = *p--;
      for(i = 1; i >= 0;)
         day_string[i--] = *p--;

   free( padded_delta );
   return NULL;
}

int main ( int argc , char ** argv ) {

//   char * string = "bonjour";
//   printf("string has length %d\n", strlen(string));
//
//   char * paddedString = SeqUtil_prePadString(string, 10, 'X');
//   printf("prepadded string is : %s\n", paddedString);
//   paddedString = SeqUtil_prePadString(string, 30, 'X');
//   printf("prepadded string is : %s\n", paddedString);
//
//   paddedString = SeqUtil_postPadString(string, 10, 'X');
//   printf("postpadded string is : %s\n", paddedString);
//   paddedString = SeqUtil_postPadString(string, 30, 'X');
//   printf("postpadded string is : %s\n", paddedString);

   char * datestamp = "20160101001122";
   char * timeDelta = "11223344";
   SeqDatesUtil_addTimeDelta(datestamp,timeDelta);
   printf("HELLO\n");
   exit(0);
}
