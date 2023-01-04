#include <stdio.h>

int print_string(char *s)
{
    printf("C: %s(): string : '%s'\n", __func__, s);
    return 0;
}
