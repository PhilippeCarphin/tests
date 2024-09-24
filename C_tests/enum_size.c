#include <stdio.h>
#include <limits.h>

// #define FORCE_ENUM_TYPE

enum normal
#ifdef FORCE_ENUM_TYPE
: unsigned long
#endif
{

    UN = 1,
    HUIT = 8,
    DOUBLE_V = 'W',
};
enum big
#ifdef FORCE_ENUM_TYPE
: unsigned long
#endif
{
    LIKE_UM_A_LOT = 4294967295LU,
    LIKE_UM_REALLY_A_LOT = 1000 * 4294967295LU,
    LIKE_UM_LITERALLY_INFINITE = (unsigned long)UINT_MAX * (unsigned long)UINT_MAX,
};
int main(void)
{
    int x = 'W';
    switch(x){
        case UN:
            fprintf(stderr, "1\n");
            break;
        case HUIT:
            fprintf(stderr, "8\n");
            break;
        case DOUBLE_V:
            fprintf(stderr, "W\n");
            break;
    }
    fprintf(stderr, "sizeof normal enum %lu\n", sizeof(enum normal));
    fprintf(stderr, "sizeof big enum %lu\n", sizeof(enum big));
    fprintf(stderr, "      LIKE_UM_REALLY_A_LOT=%lu\n", LIKE_UM_REALLY_A_LOT);
    fprintf(stderr, "             LIKE_UM_A_LOT=%lu\n", LIKE_UM_A_LOT);
    fprintf(stderr, "LIKE_UM_LITERALLY_INFINITE=%lu\n", LIKE_UM_LITERALLY_INFINITE);
    fprintf(stderr, "                 ULONG_MAX=%lu\n", ULONG_MAX);
    fprintf(stderr, "                  UINT_MAX=%u\n", UINT_MAX);

    return 0;
}
