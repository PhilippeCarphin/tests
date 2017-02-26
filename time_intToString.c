#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/********************************************************************************
 * Converts an integer number of seconds into a string in the format hh:mm:ss.
 * A char buffur of 9 mytes must be allocated to hold the 8 chars of the string
 * and the terminating NUL byte.
 * Time must be less than or equal to 99:59:59.
********************************************************************************/
static int time_int_to_string(int total_seconds, char *time_str)
{

   // Calculate the three fields of the time string
   int hours = total_seconds / 3600;
   int minutes = (total_seconds / 60) % 60;
   int seconds = total_seconds % 60;

   printf("time integers : hours:%d, minutes:%d, seconds:%d\n",hours, minutes,seconds);
   // Change them to characters.
   char *p = time_str;
   *p++ = '0' + hours/10;
   *p++ = '0' + hours%10;
   *p++ = ':';

   *p++ = '0' + minutes/10;
   *p++ = '0' + minutes%10;
   *p++ = ':';

   *p++ = '0' + seconds/10;
   *p++ = '0' + seconds%10;

   *p = 0;

   return 0;
}

int main(int argc, char **argv)
{
	int time_in_seconds;
	if(argc < 2){
		printf("%s ERROR:Must provide time in seconds as argument\n",argv[0]);
		exit(1);
	}

	printf("argv[1] is %s\n", argv[1]);
	time_in_seconds = atoi(argv[1]);

	char time_str[25];
	time_int_to_string(time_in_seconds, time_str);

	printf("Time in seconds : %d\nTime in hh:mm:ss : %s\n", time_in_seconds, time_str);

	return 0;
}


