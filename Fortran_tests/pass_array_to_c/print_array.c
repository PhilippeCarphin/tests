#include <stdio.h>

void print_array_2d(float *array, size_t ni, size_t nj)
{
    fprintf(stderr, "Printing array at %p with dimensions %lux%lu\n", array, ni, nj);
    float *elem_ptr = array;
    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            // float elem = array[j*ni + i];
            // fprintf(stderr, "%f ", elem);
            fprintf(stderr, "%.2f ", *elem_ptr++);
        }
        fputc('\n', stderr);
    }
}

void print_array_1d(float *array, size_t n)
{
    fprintf(stderr, "Printing array at %p with dimension %lu\n", array, n);
    float *elem_ptr = array;
    for(int i = 0; i < n; i++){
        // float elem = array[j*ni + i];
        // fprintf(stderr, "%f ", elem);
        fprintf(stderr, "%.2f ", *elem_ptr++);
    }
    fputc('\n', stderr);
}
