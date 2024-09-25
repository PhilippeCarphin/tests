#include <stdlib.h>

void cprint_array_2d_memory(float *array, int n_rows, int n_cols);
void cprint_array_1d_memory(float *array, int n);
void cprint_array_2d_row_major_indexing(float *array, int n_rows, int n_cols);
void cprint_array_2d_column_major_indexing(float *array, int n_rows, int n_cols);
void cprint_array_2d_column_major_forbidden_syntax(int n_rows, int n_cols, float array[n_cols][n_rows]);
void cprint_array_2d_row_major_forbidden_syntax(int n_rows, int n_cols, float array[n_rows][n_cols]);
