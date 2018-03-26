#include <stdlib.h>
#include <stdio.h>

int var_glob = 1998;

// Function implemented in sum_s.s
int sum_s(int n);

int mult(int a, int b)
{
	return a * b;
}

int mat_transpose_s(const int *in, int *out, int size);

int mat_transpose(const int * in, int * out, int size)
{

	int sum = 0;
	for(int i = 0; i < size; ++i){
		for(int j = 0; j < size; ++j)
		{
			
		}
	}
	return 42;
}

/*******************************************************************************
 *
*******************************************************************************/
int sum_c(int n)
{
	int sum = 0;
	for(int i = 0; i < n; ++i){
		sum = i*i + sum;
	}
	return sum;
}

/*******************************************************************************
 *
*******************************************************************************/
int main()
{
	int *a, *b, c;
	int res_c = mat_transpose(a,b,c);
	int res_s = mat_transpose_s(a,b,8);

	printf("mat_transpose(a,b,c) = %d\n", res_c);
	printf("mat_transpose_s(a,b,c) = %d\n", res_s);
	return 0;
}
