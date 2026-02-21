#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <string.h>

int print_string(char *info, char *s)
{
    printf("C: %s(): string(%s) : '%s'\n", __func__, info, s);
    return 0;
}
