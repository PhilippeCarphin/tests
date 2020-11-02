#include <stdio.h>

/*
 * The function external_function() has true signature
 *
 *          'const char * external_function(void)'
 *
 * But we declare it as returning int or long long int to see what happens. This
 * demonstrates what happens when a function returning char * is implcitely
 * declared and is assumed to return an int.
 *
 * If the type is 'int' as it would be if we simply comment the following line
 * and let the function be "implicitely declared", then we risk a segfault when
 * trying to look at the string pointed to by 's' because it may only be the
 * lower 4 bytes of the 8 byte value returned by external_function().
 */
extern long long int external_function();

int main(void)
{
    const char *s = (const char*) external_function();
    printf("s = %s\n", s);
    return 0;
}
