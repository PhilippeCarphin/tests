#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <inttypes.h>
#include <complex.h>
#include <limits.h>
#include <float.h>

#define printsizeof(type) fprintf(stderr, "%28s = %-2lu (%-3lu bits)\n", "sizeof(" #type ")", sizeof(type), sizeof(type)*8)
int main ( int argc , char ** argv ) {

    fprintf(stderr, "========== Classic types ===============\n");
    printsizeof(char);
    printsizeof(short);
    printsizeof(int);
    printsizeof(long);
    fprintf(stderr, "\n");

    /*
     * Historically, the various integer types have had different sizes
     * but nowadays, normal 64 bit systems have them all at 64 bits
     * See https://www.open-std.org/Jtc1/sc22/wg14/www/docs/C99RationaleV5.10.pdf
     * page 36 for info about the choice to go with these names.
     */
    fprintf(stderr, "========== long integers ===============\n");
    printsizeof(long int);
    printsizeof(long long);
    printsizeof(long long int);
    fputc('\n', stderr);

    /*
     * Note that long float existed and was synonymous for double but was
     * retired in C89 (above linked standard p.42).
     */
    fprintf(stderr, "========== Floating point types ==========\n");
    printsizeof(float);
    printsizeof(double);
    printsizeof(long double);
    fprintf(stderr, "\n");

    /*
     * Obviously there is no need for this part of the test since
     * the names of the types are good
     */
    fprintf(stderr, "========== Types from inttypes.h ===============\n");
    printsizeof(uint8_t);
    printsizeof(uint16_t);
    printsizeof(uint32_t);
    printsizeof(uint64_t);
    fputc('\n', stderr);

    /*
     * Exotic stuff
     */
    fprintf(stderr, "========== Complex numbers from complex.h ===============\n");
    printsizeof(float complex);
    printsizeof(double complex);
    printsizeof(long double complex);

    /*
     * Limit values and precision
     */
#define print_val(VAL,TYPE) fprintf(stderr, "%12s = " #TYPE "\n", #VAL, VAL)
    fprintf(stderr, "========== Limit values and precision =====================\n");
    print_val(UINT_MAX, %u);
    print_val(ULONG_MAX, %lu);
    print_val(INT_MAX, %11d);
    print_val(INT_MIN, %11d);
    print_val(LONG_MAX, %20ld);
    print_val(LONG_MIN, %20ld);
    print_val(FLT_MAX, %e);
    print_val(FLT_MIN, %e);
    print_val(FLT_EPSILON, %e);
    print_val(DBL_MAX, %e);
    print_val(DBL_MIN, %e);
    print_val(DBL_EPSILON, %e);
    print_val(LDBL_MAX, %Le);
    print_val(LDBL_MIN, %Le);
    print_val(LDBL_EPSILON, %Le);
    print_val(SIZE_MAX, %lu);

    return 0;
}
