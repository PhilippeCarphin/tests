#include <stdio.h>
/*
 * The C function we need to wrap.  They're actually both the
 * same function, but I was trying things and depending on what
 * I was trying, they might have been different
 */
int c_to_wrap(char *s, float f) {
        // printf(" C       :    %s() %f (%p)\n",__func__, f, f);
        printf(" C       :    c_to_wrap() f = %f (%p)\n", f, f);
        return 0;
}

int c_to_wrap_good(char *s, float f) {
        printf(" C       :    %s() f = %f\n", __func__, f);
        return 0;
}

/*
 * This is for some tests on wrapping a Fortran function
 * Depending on the system, an incorrect call can cause a
 * segfault
 */

extern void f_ezsetval_(char * s, float *fp);
int c_ezsetval(char *s, float *fp) {
        f_ezsetval_(s, fp);
        return 0;
}

int c_ezsetval2(char *s, float *f) {
        f_ezsetval_(s, f);
        return 0;
}
