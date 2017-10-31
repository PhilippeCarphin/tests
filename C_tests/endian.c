#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int a = 0xDEADBEEF;
	unsigned char *c = (unsigned char *)&a;
	for(int i = 0; i < sizeof(int); ++i){
		printf("c[%d] = %x\n", i, c[i]);
	}
	if(c[0] == 0xEF)
		printf("Little-endian\n");
	else
		printf("Big-endian\n");

	return 0;
}
