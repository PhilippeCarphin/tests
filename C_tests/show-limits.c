#include <stdint.h>
#ifdef __APPLE__
#include <limits.h>
#else
#include <linux/limits.h>
#endif
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_value(name, neg) {#name, name, neg}
#define print_value(name) \
    long long int name##uint = name; \
    fprintf(stderr, "The value of %-14s is  %llu\n", #name, name##uint)

#define print_value_neg(name) \
    long long int name##int = name; \
    fprintf(stderr, "The value of %-14s is %lld\n", #name, name##int)

#define print_size(name) \
    fprintf(stderr, "The  size of %-14s is  %lu\n", #name, sizeof(name))

struct name_int {
    char *name;
    long long unsigned int value;
    int negative;

};

int get_value(char *name, long long unsigned int *value){
    fprintf(stderr, "Short ----\n");
    print_size(short);
    print_value_neg(SHRT_MIN);
    print_value(SHRT_MAX);
    print_value(USHRT_MAX);

    fprintf(stderr, "\nInt ----\n");
    print_size(int);
    print_value_neg(INT_MIN);
    print_value(INT_MAX);
    print_value(UINT_MAX);

    fprintf(stderr, "\nLong ----\n");
    print_size(long int);
    print_value_neg(LONG_MIN);
    print_value(LONG_MAX);
    print_value(ULONG_MAX);

    fprintf(stderr, "\nLong Long ----\n");
    print_size(long long int);
    print_value_neg(LLONG_MIN);
    print_value(LLONG_MAX);
    print_value(ULLONG_MAX);

    fprintf(stderr, "\nSize_t ----\n");
    print_size(size_t);
    print_value(SIZE_MAX);

    fprintf(stderr, "Others -------\n");
    static struct name_int nv[] = {
        name_value(NGROUPS_MAX, 0),
        name_value(ARG_MAX, 0),
        name_value(LINK_MAX, 0),
        name_value(MAX_CANON, 0),
        name_value(MAX_INPUT, 0),
        name_value(NAME_MAX, 0),
        name_value(PATH_MAX, 0),
        name_value(PIPE_BUF, 0),

#ifndef __APPLE__
        name_value(NR_OPEN),
        name_value(XATTR_NAME_MAX),
        name_value(XATTR_SIZE_MAX),
        name_value(XATTR_LIST_MAX),
        name_value(PHYS_ADDR_MAX),
        name_value(S8_MAX, 0),
        name_value(S8_MIN, 1),
        name_value(U8_MAX, 0),

        name_value(S16_MAX, 0),
        name_value(S16_MIN, 1),
        name_value(U16_MAX, 0),

        name_value(U32_MAX, 0),
        name_value(U32_MIN, 0),
        name_value(S32_MAX, 0),
        name_value(S32_MIN, 0),

        name_value(S64_MIN, 0)
        name_value(S64_MAX, 0),
        name_value(U64_MAX, 0),
#endif
    };

    for(int i=0; i < sizeof(nv)/sizeof(*nv); i++){
        if(nv[i].negative){
            printf("Value of %-20s is %lld\n", nv[i].name, (long long int)nv[i].value);
        } else {
            printf("Value of %-20s is %llu\n", nv[i].name, nv[i].value);
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    get_value(NULL, NULL);
    return 0;
}

