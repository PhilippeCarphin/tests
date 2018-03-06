#include <stdlib.h>
#include <unistd.h> // for sleep function
#include <stdio.h>
#include <string.h>
/*
 * This test was meant to demonstrate the evils of calling certain functions on
 * unallocated memory.
 *
 * In an infinite for loop, we allocate 1MiB of memory, then we call strlen() on
 * it.  The intention is for this to cause a segfault.
 *
 * RESULT: Interestingly, the memory seems to be 0-initialized. I'm getting all
 * output is 0.
 *
 * This answer on stack overflow points out that although malloc() doesn not
 * initialize memory, memory given to us by the OS is cleared for security
 * reasons.
 *
 * https://stackoverflow.com/a/8029624/5795941
 */

int main (void)
{
	for(;;){
		const size_t SIZE = 1024*1024;
		char *s = malloc(SIZE);
		printf("strlen(s) = %lu\n" , strlen(s));
		sleep(1);
	}

	return 0;
}

