#include <stdio.h>
int quadruple_by_ref(double *x){
    fprintf(stderr, "%s: x = %f\n", __func__, *x);
    *x *= 4;
    return 0;
}
