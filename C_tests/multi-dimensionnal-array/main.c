#include <stdlib.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    const int NI = 3;
    const int NJ = 5;

    int value = 0;
    int three_d_array[NI][NJ];
    for(int i = 0; i < NI; i++){
        for(int j = 0; j < NJ; j++){
            three_d_array[i][j] = value;
            fprintf(stderr, "(a[%d][%d] = %2d) ", i,j,value);
            value++;
        }
        fprintf(stderr, "\n");
    }
    fprintf(stderr, "=======================\n");

    fprintf(stderr, "Printing according to memory layout:\n\t");
    fprintf(stderr, "fprintf(stderr, \"%%2d \", *cursor++);\n");

    int *cursor = three_d_array;
    for(int i = 0; i < NI; i++){
        for(int j = 0; j < NJ; j++){
            fprintf(stderr, "%2d ", *cursor++);
        }
        fprintf(stderr, "\n");
    }

    return 0;
}
