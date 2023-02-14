#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>

int print_string(char *s)
{
    printf("C: %s(): string : '%s'\n", __func__, s);
    return 0;
}
