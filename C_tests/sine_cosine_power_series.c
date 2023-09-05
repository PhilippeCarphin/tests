#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

int main (int argc, char **argv) {

    double original_x;
    /*
     * Obtain original_x from argv[1]
     */
    if(argc <= 1 || sscanf(argv[1], "%lf", &original_x) != 1){
        fprintf(stderr, "ERROR first argument must be doubleing point value\n");
        return 1;
    }

    /*
     * Bring x into the interval [0, tau]
     */
    double tau = 2*3.14159265359;
    double x = original_x;
    if(x > 0){ while (x >  tau){ x -= tau; } }
    else     { while (x < 0){ x += tau; } }
    printf("Original x = %f, x = %f\n", original_x, x);

    /*
     * Do the power series
     */
    double sin = 0;
    double cos = 1;
    double abs_term = 1; // (x^n)/(n!)
    for(int n = 1 ; n < 40; n++){
        int m = n%2;
        int sign = ((n/2)%2 ? -1 : 1);
        abs_term *= x/n;
        sin +=  m * sign * abs_term;  // If n is odd, add sign*x^n/n!
        cos += !m * sign * abs_term; // if n is even, add sign*x^n/n!
    }

    /*
     * output sine and cosine
     */
    printf("sin(%f)=%.16f, cos(%f)=%.16f\n",original_x,sin,original_x,cos);

    return 0;
}
