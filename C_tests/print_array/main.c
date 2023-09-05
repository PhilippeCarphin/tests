#include "print_array.h"
#include <stdlib.h>

int main(void){

    int *arr_i = malloc(1000 * sizeof(*arr_i));
    int *arr_f = malloc(1000 * sizeof(*arr_f));

    for(int i = 0; i < 1000; i++){
        arr_i[i] = -INT_MAX;
    }

    print_int_array("My INT array: ", arr_i, 1000);
    size_t digits = log(INT_MAX)/log(10);
    printf("log2(int_max)=%f, log2(10)=%f, log2(int_max)/log2(10)=%f, digits=%lu\n", log(INT_MAX), log(10), log(INT_MAX)/log(10), digits);
    printf("log2(int_max)=%f, log2(10)=%f, log2(int_max)/log2(10)=%f, digits=%lu\n", log2(INT_MAX), log2(10), log2(INT_MAX)/log2(10), digits);
    printf("INT_MAX=%d\n", INT_MAX);

    return 0;
}

