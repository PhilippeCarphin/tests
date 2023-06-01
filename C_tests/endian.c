#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	unsigned int a = 0xAABBCCDD;

	unsigned char *bytes = (unsigned char *)&a;

	for(unsigned int i = 0; i < sizeof(a); ++i){
		printf("bytes[%d] = %x\n", i, bytes[i]);
	}
	if(bytes[0] == 0xDD)
		printf("Little-endian\n");
	else
		printf("Big-endian\n");

    printf("a << 8 = %08x\n", (a << 8));
    printf("a >> 8 = %08x\n", (a >> 8));
	return 0;
}
