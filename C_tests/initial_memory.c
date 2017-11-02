#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main(void)
{
	uint8_t *phil = malloc(256);
	printf("strlen(phil) = %lu\n", strlen(phil));
	for(int i = 0; i < 1000; ++i){
		printf("%d-", phil[i]);
		if(i % 16 == 0)
			putchar('\n');
	}
	return 0;
}
