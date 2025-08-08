#include <stdlib.h>
#include <stdio.h>

int average(float *array, int ni, int nj, float *average){
    if(array == NULL){
        fprintf(stderr, "%s(): Array pointer is NULL\n", __func__);
        return 1;
    }
    float sum = 0;
    float *p = array;
    for(int i = 0; i < ni; i++){
        for(int j = 0; j < nj; j++){
            sum += *p++;
        }
    }
    *average = sum/(ni*nj);
    return 0;
}
