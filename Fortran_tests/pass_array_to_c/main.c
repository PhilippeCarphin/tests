#include "cprintarray.h"

int main(void){
    int ni = 8;
    int nj = 4;

    float carray[nj][ni];

    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            carray[j][i] = (i+1) + (j+1)/10.0;
        }
    }

    print_array_2d(&carray[0][0], ni, nj);

    float *elem_ptr = &carray[0][0];
    for(int e = 0; e < ni*nj; e++){
        *elem_ptr++ = e+1;
    }

    print_array_2d(&carray[0][0], ni, nj);
    return 0;
}



