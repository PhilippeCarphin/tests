#include <time.h>
#include <stdio.h>
#define PRINT(name, fmtspec) fprintf(stderr, #name "(%%" #fmtspec ") %" #fmtspec "\n", name)
/*
 * Arguments are named according to how the ISO C Binding for this function
 * will be misconfigured.
 *
 * The first argument will have the VALUE specifier but the second will not
 * and therefor the Fortran function will pass it by reference.  We did choose
 * time_t AKA long so that it would be big enough to hold all 64 bits of an
 * address.
 */
int print_datetime(const time_t DateTimeVal, const time_t DateTimeRef){
    PRINT(DateTimeVal, ld);
    PRINT(DateTimeRef, ld);
    PRINT(*(time_t*)DateTimeRef, ld);
    return 0;
}
