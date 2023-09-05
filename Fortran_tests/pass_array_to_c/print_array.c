#include <stdio.h>

void cprint_array_2d_memory(float *array, size_t ni, size_t nj)
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %lux%lu\n", __func__, array, ni, nj);
    float *elem_ptr = array;
    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            float elem = *elem_ptr++;
            fprintf(stderr, "%.2f ", elem);
        }
        fputc('\n', stderr);
    }
}

void cprint_array_2d_indexing(float *array, size_t ni, size_t nj)
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %lux%lu\n", __func__, array, ni, nj);
    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            float elem = array[j*ni + i];
            fprintf(stderr, "%.2f ", elem);
        }
        fputc('\n', stderr);
    }
}

void cprint_array_2d_array_yuck(size_t ni, size_t nj, float array[nj][ni])
{
    fprintf(stderr, "%s(): Printing array at %p with dimensions %lux%lu\n", __func__, array, ni, nj);
    for(int j = 0; j < nj; j++){
        for(int i = 0; i < ni; i++){
            float elem = array[j][i];
            fprintf(stderr, "%.2f ", elem);
        }
        fputc('\n', stderr);
    }
}


void cprint_array_1d(float *array, size_t n)
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
