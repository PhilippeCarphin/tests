#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
	int a = 0xAABBCCDD;
	unsigned char *bytes = (unsigned char *)&a;
   printf("The bytes in memory of %x are\n", a);
	for(unsigned int i = 0; i < sizeof(int); ++i){
		printf("bytes[%d] = %x\n", i, bytes[i]);
	}
	if(bytes[0] == 0xDD)
		printf("Little-endian\n");
	else
		printf("Big-endian\n");

	return 0;
}
