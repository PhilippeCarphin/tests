#include "cprintarray.h"

int main(void){
    int ni = 8;
    int nj = 4;

    float carray[nj][ni];
    float *carray_ptr = &carray[0][0];

    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            /*
             * That this syntax is like that makes sense but the syntax
             * isn't something I use
             *
             * It's because you could have int *rows[nj] and that way
             * rows[j] is a pointer to the j-th row of a pseudo array
             * and rows[j][i] is the i-th element of the j-th row.
             *
             * The syntax for 2D contiguous memory arrays is consistent
             * with the syntax used for pseudo arrays.
             */
            carray[j][i] = (i+1) + (j+1)/10.0;
            /*
             * But I greatly prefer not worrying about this stuff
             * since you can only rely on it in the function where the
             * array was declared and it's not that hard to just do
             */
            int move_down = ni;
            int move_right = 1;
            carray_ptr[j*move_down + i*move_right] = (i+1) + (j+1)/10.0;
        }
    }

    cprint_array_2d(&carray[0][0], ni, nj);

    float *elem_ptr = &carray[0][0];
    for(int e = 0; e < ni*nj; e++){
        *elem_ptr++ = e+1;
    }

    cprint_array_2d(&carray[0][0], ni, nj);
    return 0;
}



