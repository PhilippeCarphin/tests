#include <stdlib.h>
#include <stdio.h>
#include "multiply.h"

int dot_product(int *a, size_t na, int *b, size_t nb, int *result){
    if(na != nb){
        return 1;
    }
    int res = 0;
    for(size_t i = 0; i < na; i++){
        int mult = multiply(a[i], b[i]);
        res += mult;
        fprintf(stderr, "a[%lu]=%d, b[%lu]=%d, mult=%d, res=%d\n", i, a[i], i, b[i], mult, res);
    }
    *result = res;
    return 0;
}

