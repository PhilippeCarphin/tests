#include "cprintarray.h"
#include <stdio.h>

// only one of ni,nj are used in both but requiring them
// both makes it more consistent
#define rm_index(ni,nj,i,j) ((i)*(nj) + (j))
#define cm_index(ni,nj,i,j) ((j)*(ni) + (i))

int main(void){
    int ni = 8;
    int nj = 4;

    fprintf(stderr, "C doesn't have multidimensionnal arrays.  Some people might\n");
    fprintf(stderr, "say that you can declare `int 2d_array[n][m]` but I choose\n");
    fprintf(stderr, "to pretend that this type of array doesn't exist because I don't like it.\n");
    fprintf(stderr, "In C there are only 1D arrays with index computations\n");
    fprintf(stderr, "and for this reason I say that C is row-column-fluid\n");
    fprintf(stderr, "or pan-major.  Of course, we have to keep things consistent\n");

    fprintf(stderr, "Here is a column major array, lets print it...\n");
    float *column_major_array = malloc(ni*nj * sizeof(*column_major_array));
    for(int i = 0; i < ni; i++){
        for(int j = 0; j < nj; j++){
            column_major_array[cm_index(ni,nj,i,j)] = (1+i) + (1+j)/10.0;
        }
    }
    cprint_array_2d_column_major_indexing(column_major_array, ni, nj);

    fprintf(stderr, "Here is the same array (conceptually) stored in row major, lets print it ...\n");
    float *row_major_array = malloc(ni*nj * sizeof(*row_major_array));
    for(int i = 0; i < ni; i++){
        for(int j = 0; j < nj; j++){
            row_major_array[rm_index(ni,nj,i,j)] = (1+i) + (1+j)/10.0;
        }
    }
    cprint_array_2d_row_major_indexing(row_major_array, ni, nj);

    fprintf(stderr, "There is no preferred way to do 2D arrays in C (because thing[i][j] shouldn't be used to access contiguous memory, it is only good for arrays of arrays, not doing indexing calculation), we just have to be consistent, and if we aren't, then we won't be accessing the right elements of our arrays\n");

    fprintf(stderr, "Lets use row-major index calculations to access elemnts of a column-major array\n");
    cprint_array_2d_row_major_indexing(column_major_array, ni, nj);

    fprintf(stderr, "Lets use column-major index calculations to access elemnts of a row-major array\n");
    cprint_array_2d_column_major_indexing(row_major_array, ni, nj);

    fprintf(stderr, "Watch me use the forbidden 2D array syntax just to show that\n");
    fprintf(stderr, "the reason I don't like it is not that I don't know how to\n");
    fprintf(stderr, "use it even for passing arrays to functions.  I know how to\n");
    fprintf(stderr, "use it and I don't like it\n");
    float array_2d[ni][nj];
    for(int i = 0; i < ni; i++){
        // The fact that we can do this:
        float *row = array_2d[i];
        // is why C has to be a row major language.
        for(int j = 0; j < nj; j++){
            row[j] = (i+1) + (j+1)/10.0;
        }
    }
    cprint_array_2d_row_major_forbidden_syntax(ni, nj, array_2d);

    fprintf(stderr, "Let me print a column-major array with this syntax\n");
    cprint_array_2d_column_major_forbidden_syntax(ni, nj, (float (*)[ni])column_major_array);

    fprintf(stderr, "If we want to be efficient, we have to consider the order\n");
    fprintf(stderr, "of our loops, the best order is the one where we can do\n");
    float *p = row_major_array;
    for(int i = 0; i < ni; i++){
        for(int j = 0; j < nj; j++){
            *p++ = (i+1) + (j+2)/10.0;
        }
    }
    cprint_array_2d_row_major_indexing(row_major_array, ni, nj);
    return 0;
}



