#include <stdio.h>

int print_nth_string(char **strings, int n)
{
    printf("string %d is '%s'\n", n, strings[n]);
    return 0;
}
