#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <math.h>

static char *int_array_to_string(int *array, size_t array_size) {
    // Most digits an int can take is INT_MAX%10
    // +1 for the potential minus sign
    // +2 for the ', ' between each int,
    // and we add 2 for the starting '[' and ending ']\0'
    size_t digits = log(INT_MAX)/log(10) + 1; // +1 because 9.33 gets truncated to 9 but the value should be 10
    size_t str_size = (digits + 3) * array_size + 3;
    char *array_str = malloc(str_size);
    char *p = array_str;
    size_t s = str_size;
    size_t l = snprintf(p, str_size, "[%d", array[0]); s -= l; p+= l;
    for(size_t i = 1; i < array_size; i++){
        l = snprintf(p, s, ", %d", array[i]);
        if(l > s){
            fprintf(stderr, "ERROR Out of space to write in string, reached size of %lu with %lu elements left to print, l=%lu, s=%lu\n", str_size, array_size-i, l,s);
            free(array_str);
            return NULL;
        }
        p += l; s -= l;
    }
    snprintf(p, s, "]");
    return array_str;
}

static void print_int_array(char *start, int *array, size_t array_size){
    char *array_str = int_array_to_string(array, array_size);
    if(array_str == NULL){
        fprintf(stderr, "%s(): ERROR Converting array to string\n", __func__);
        return;
    }
    fprintf(stderr, "%s%s\n", start, array_str);
    free(array_str);
}

static char *float_array_to_string(float *array, size_t array_size)
{
    if(array_size == 0){
        char * array_str = malloc(3);
        snprintf(array_str, 3, "[]");
        return array_str;
    }
    size_t str_size = (1 + 5 + 1 + 5 + 2) * array_size + 3;
    char *array_str = malloc(str_size);
    char *p = array_str;
    size_t s = str_size;
    size_t l = snprintf(p, str_size, "[%5.5f", array[0]); s -= l; p += l;
    for(size_t i = 1; i < array_size; i++){
        l = snprintf(p, s, ", %f", array[i]); p += l; s -= l;
    }
    snprintf(p, s, "]");
    return array_str;
}

static void print_float_array(char *start, float *array, size_t array_size){
    char *array_str = float_array_to_string(array, array_size);
    fprintf(stderr, "%s%s\n", start, array_str);
    free(array_str);
}
