#include <stdlib.h>
#include <stdio.h>

int main(void){
    int array[8];
    int *array_p = malloc(8 * sizeof(*array_p));

    printf("ARRAY\n");
    printf("array identifier : array=%p\n", array);
    printf("address of array identifier : &array=%p\n", &array);

    printf("POINTER\n");
    printf("pointer : array_p=%p\n", array_p);
    printf("address of pointer : &array_p=%p\n", &array_p);

    return 0;
}
