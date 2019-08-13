#include <stdio.h>

int to_wrap(char *s, float f)
{
        printf("The falue of the float is %f (%p)\n", f, f);
}

int to_wrap_good(char *s, float f)
{
        printf("The falue of the float is %f\n", f);
}
