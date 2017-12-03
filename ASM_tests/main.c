#include <stdlib.h>
#include <stdio.h>

int add(int a, int b);

int test_add()
{
	if(add(77,88) == 165){
		printf("Correct answer\n");
		return 0;
	}else{
		printf("Wrong answer\n");
		return 1;
	}
}

int sum(int a, int b, int c, int d, int e, int f, int g, int h, int i);

int main(void)
{
	printf("Calling my assembler add function : %d\n", add(77,88));
	printf("sum(1,2,3,4,5,6,7,8,9) = %d\n", sum(1,2,3,4,5,6,7,8,9));
	return 0;
}
