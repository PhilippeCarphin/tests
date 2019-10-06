#include <stdio.h>

int c_to_wrap(char *s, float f) {
        printf(" C       :    c_to_wrap() %f (%p)\n", f, f);
        return 0;
}

int c_to_wrap_good(char *s, float f) {
        printf(" C       :    %s() %f\n", __func__, f);
        return 0;
}

extern void f_ezsetval_(char * s, float *fp);
int c_ezsetval(char *s, float *fp) {
        f_ezsetval_(s, fp);
        return 0;
}

int c_ezsetval2(char *s, float *f) {
        f_ezsetval_(s, f);
        return 0;
}
