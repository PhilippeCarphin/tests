#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Phil {
	int a;
	int b;
	int c;
	int d;
};
char *int_to_string(int i);
int phil_struct_func(struct Phil param)
{
    return param.a + param.b + param.c + param.d;
}
int phil_struct_func_s(struct Phil param)
{
    return param.a + param.b + param.c + param.d;
}

int module(int a, int b)
{
    int d = a % b;
    return '0' + d;
}


int main(int argc, char **argv)
{
	struct Phil p = {1,2,3,4};
	int input;
#if 0
	if(argc < 2){
		printf("need one argument\n");
		return 8;
	}

	if(sscanf(argv[1],"%d", &input) != 1){
		puts("Need an integer argument");
		return 9;
	}
	printf("input is %d\n", input);
#else
    input = 1337;
#endif
	char *output = int_to_string(input);
	printf("int_to_string(input) == %s\n", output);
	if(input) puts( " ");
	char *str = malloc(1234);
	*str++ = '0';
	*str++ = 'B';
	*str = 0;
	int a = input;
	int q = a / 10;
	int r = a % 99;
	printf(" %d = %d * 10 + %d\n", a, q, r);

	if( a != q + 10 + r )
		printf("a != qb + r\n");

	printf("phil_struct_func(p) = %d\n", phil_struct_func(p));
	return 0;
}

