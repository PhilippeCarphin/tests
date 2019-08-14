#include <stdio.h>

int to_wrap(char *s, float f)
{
        printf("The falue of the float is %f (%p)\n", f, f);

}

int to_wrap_good(char *s, float f)
{
        printf("The falue of the float is %f\n", f);
}

extern void f_ezsetval_(char * s, float *f);
int c_ezsetval(char *s, float f)
{
        f_ezsetval_(s, &f);
}

int c_ezsetval2(char *s, float f)
{
        f_ezsetval_(s, &f);
}
