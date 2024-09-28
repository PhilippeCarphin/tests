#include <stdio.h>
/*******************************************************************************
 * Print the memory inserting a newline after every n_cols elements
*******************************************************************************/
void cprint_array_2d_memory(float *array, int n_rows, int n_cols)
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %dx%d\n", __func__, array, n_rows, n_cols);
    fprintf(stderr, "Simply printing memory contiguous elements and inserting a newline every %d elements\n", n_cols);
    float *elem_ptr = array;
    for(int row = 0; row < n_rows; row++){
        for(int col = 0; col < n_cols; col++){
            float elem = *elem_ptr++;
            fprintf(stderr, "%.1f  ", elem);
        }
        fputc('\n', stderr);
    }
}

/*******************************************************************************
 * Print the memory as a single line
*******************************************************************************/
void cprint_array_1d_memory(float *array, int n)
{
    fprintf(stderr, "Printing array at %p with dimension %d\n", array, n);
    float *elem_ptr = array;
    for(int row = 0; row < n; row++){
        // float elem = array[col*n_rows + row];
        // fprintf(stderr, "%f ", elem);
        fprintf(stderr, "%.1f  ", *elem_ptr++);
    }
    fputc('\n', stderr);
}

/*******************************************************************************
 * Print the array using row-major index computations
*******************************************************************************/
void cprint_array_2d_row_major_indexing(float *array, int n_rows, int n_cols)
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %dx%d\n", __func__, array, n_rows, n_cols);
    int row_size = n_cols;
    for(int row = 0; row < n_rows; row++){
        for(int col = 0; col < n_cols; col++){
            float elem = array[row*row_size + col];
            fprintf(stderr, "%.1f  ", elem);
        }
        fputc('\n', stderr);
    }
}

/*******************************************************************************
 * Print the array using column-major index computations
*******************************************************************************/
void cprint_array_2d_column_major_indexing(float *array, int n_rows, int n_cols)
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %dx%d\n", __func__, array, n_rows, n_cols);
    int col_size = n_rows;
    for(int row = 0; row < n_rows; row++){
        for(int col = 0; col < n_cols; col++){
            // skip col columns to get to the top of the col-th column
            // then go down row elements to get to the row-th element of
            // the col-th column, AKA element (row,col)
            fprintf(stderr, "%.1f  ", array[col*col_size + row]);
        }
        fputc('\n', stderr);
    }
}

/*******************************************************************************
 * Use the forbidden syntax of C multidimensionnal array indexing to print
 * a column major array
*******************************************************************************/
void cprint_array_2d_column_major_forbidden_syntax(int n_rows, int n_cols, float array[n_cols][n_rows])
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %dx%d\n", __func__, array, n_rows, n_cols);
    for(int row = 0; row < n_rows; row++){
        for(int col = 0; col < n_cols; col++){
            float elem = array[col][row];
            fprintf(stderr, "%.1f  ", elem);
        }
        fputc('\n', stderr);
    }
}

/*******************************************************************************
 * Use the forbidden syntax of C multidimensionnal array indexing to print
 * a row major array
*******************************************************************************/
void cprint_array_2d_row_major_forbidden_syntax(int n_rows, int n_cols, float array[n_rows][n_cols])
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %dx%d\n", __func__, array, n_rows, n_cols);
    for(int row = 0; row < n_rows; row++){
        for(int col = 0; col < n_cols; col++){
            float elem = array[row][col];
            fprintf(stderr, "%.1f  ", elem);
        }
        fputc('\n', stderr);
    }
}
