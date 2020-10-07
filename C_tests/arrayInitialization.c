#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int get_nb_non_zero(char * array, size_t size){
    int nb_non_zero = 0;
    for(int i = 0; i < size; i++){
        if(array[i] != 0){
            nb_non_zero++;
        }
    }
    return nb_non_zero;
}
int main ( int argc , char ** argv ) {

    char depArgs[256] = {0};
    char uninitialized[246];
    char partial_init[1234] = {1,2,3,4,5};
    printf("There were %d non-zero elements in depArgs\n", get_nb_non_zero(depArgs, sizeof(depArgs)));
    printf("There were %d non-zero elements in uninitialized\n", get_nb_non_zero(uninitialized, sizeof(uninitialized)));
    printf("There were %d non-zero elements in partial_init\n", get_nb_non_zero(partial_init, sizeof(partial_init)));

    return 0;
}
