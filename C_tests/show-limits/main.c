#include <stdint.h>
#include <linux/limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define name_value(name) {#name, name}

struct name_int {
    char *name;
    long long unsigned int value;
};

int get_value(char *name, long long unsigned int *value){
    static struct name_int nv[] = {
        name_value(NR_OPEN),
        name_value(NGROUPS_MAX),
        name_value(ARG_MAX),
        name_value(LINK_MAX),
        name_value(MAX_CANON),
        name_value(MAX_INPUT),
        name_value(NAME_MAX),
        name_value(PATH_MAX),
        name_value(PIPE_BUF),
        name_value(XATTR_NAME_MAX),
        name_value(XATTR_SIZE_MAX),
        name_value(XATTR_LIST_MAX),
#if(1)
        name_value(USHRT_MAX),
        name_value(SHRT_MAX),
        name_value(SHRT_MIN),
        name_value(INT_MAX),
        name_value(INT_MIN),
        name_value(UINT_MAX),
        name_value(LONG_MAX),
        name_value(LONG_MIN),
        name_value(ULONG_MAX),
        name_value(LLONG_MAX),
        name_value(LLONG_MIN),
        name_value(ULLONG_MAX),
        name_value(SIZE_MAX),
        name_value(PHYS_ADDR_MAX),
        name_value(U8_MAX),
        name_value(S8_MAX),
        name_value(S8_MIN),
        name_value(U16_MAX),
        name_value(S16_MAX),
        name_value(S16_MIN),
        name_value(U32_MAX),
        name_value(U32_MIN),
        name_value(S32_MAX),
        name_value(S32_MIN),
        name_value(U64_MAX),
        name_value(S64_MAX),
        name_value(S64_MIN)
#endif
    };

    for(int i=0; i < sizeof(nv)/sizeof(*nv); i++){
        if(strcmp(nv[i].name, name) == 0){
            *value = nv[i].value;
            return 0;
        }
    }

    return -1;
}

int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "Need one argument\n");
        exit(1);
    }

    long long unsigned int value;

    if(get_value(argv[1], &value)){
        printf("Name '%s' is not recognized\n", argv[1]);
        exit(1);
    }

    printf("Value of %s is %ld\n", argv[1], value);
    return 0;
}

