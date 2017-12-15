#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv)
{
	puts("hello world\n");
	char a = getchar();
	if(a == 'a'){
		puts("got an 'a'\n");
	} else {
		puts("didn't get an 'a'\n");
	}
	return 0x77;
}
