#include <stdarg.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#define SEQ_MAXFIELD 1000

void SeqUtil_TRACE (char * fmt, ...) {

	/* Decide whether or not to output a message */
	int output = 0;
	/* Compare level argument or type argument with type flags
	 * to decide on the value of output */
	output = 1;
	if(!output)
		return;

	/* Construct initial message */
	char message[SEQ_MAXFIELD];
	va_list ap;
	va_start (ap, fmt);
	vsprintf(message,fmt,ap); 
	va_end (ap);
	int i = 0;	
	/* Add info to message 
	if(traceFlags.full == 1){
		Add datestamp 
	} */
	if(0 /*otherFlag*/){
		i++;/* Add other thing */
	}
	/* ... */
	
	printf("%s",message);
	// while(message[i] != '\0')
	// 	printf("%c", message[i++]);

}
int main( int argc, char** argv)
{
	char *message;
	message = strdup("BONJOUR");
	int number = 2048;
	SeqUtil_TRACE ("This is number: %d : This is my message : %s \n",number, message);
	printf("\n\n\nThis is number: %d : This is my message : %s \n",number, message);
}


