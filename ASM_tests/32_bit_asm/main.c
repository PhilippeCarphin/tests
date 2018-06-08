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
		for(int j = 0; j < i; ++j)
		{
			sum += in[i * size + j];
			out[i * size + j] = in[j*size + i];
			out[j * size + i] = in[i*size + j];
		}
		out[i * size + i] = in[i*size +i];
	}
	return sum;
}
int print_matrix(const int *mat, const int size)
{
	for(int i = 0; i < size; ++i){
		printf("  ");
		for(int j = 0; j < size; ++j){
			printf("%d ", mat[i * size + j]);
		}
		printf("\n");
	}
	return 0;
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
	int *in, *out, c;

	int mat_in[] = {1,2,3,4};
	int mat_out[sizeof(mat_in)];
	int mat_out_s[sizeof(mat_in)];
	int size = 2;

	printf("mat_transpose(in,out,c) = \n");
	mat_transpose(mat_in, mat_out, size);
	print_matrix(mat_out, size);

	printf("mat_transpose_s(in,out,c) = \n");
	mat_transpose_s(mat_in, mat_out_s, size);
	print_matrix(mat_out_s, size);
	// sum_s(3);
	return 0;
}
