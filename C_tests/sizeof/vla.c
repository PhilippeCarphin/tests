#include <stdio.h>

int test_vla(size_t s);
int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "ERROR at least one argument must be provided\n");
        return 1;
    }

    size_t s;
    if(sscanf(argv[1], "%lu", &s) != 1){
        fprintf(stderr, "ERROR getting a size form first argument '%s'\n", argv[1]);
        return 1;
    }

    int err = test_vla(s);
    if(err){
        fprintf(stderr, "ERROR in test_vla(%lu)\n", s);
        return err;
    }
}

int test_vla(size_t s){

    int ivl_array[s];
    char cvl_array[s];

    size_t si = sizeof(ivl_array);
    size_t sc = sizeof(cvl_array);

    printf("si = %lu, sc = %lu\n", si, sc);
    return 0;
}
