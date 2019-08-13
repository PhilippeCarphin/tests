#include <stdio.h>

int to_wrap(char c, float f)
{
        printf("The falue of the float is %f (%p)\n", f, f);
}

int to_wrap_good(char c, float f)
{
        printf("The falue of the float is %f\n", f);
}
