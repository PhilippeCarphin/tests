#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (void)
{
	for(int i = 0;;++i){
		char *s = malloc(1024*1024);
		printf("strlen(s) = %lu\n" , strlen(s));
		sleep(1);
	}
	return 0;
}

