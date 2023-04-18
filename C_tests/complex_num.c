#include <complex.h>
#include <stdio.h>

int main(void){

    double complex z = 0.5 + 0.5I;
    double complex w = 0.5 - 0.5I;
    double complex s = z + w;
    double complex p = z * w;
    double complex q = z / w;

    fprintf(stderr, " z  = %f + %fi\n", creal(z), cimag(z));
    fprintf(stderr, "|z| = %f\n", cabs(z));
    fprintf(stderr, " w  = %f + %fi\n", creal(w), cimag(w));
    fprintf(stderr, " s  = %f + %fi\n", creal(s), cimag(s));
    fprintf(stderr, " p  = %f + %fi\n", creal(p), cimag(p));
    fprintf(stderr, " q  = %f + %fi\n", creal(q), cimag(q));

    return 0;
}
