#include <math.h>
#include <stdio.h>
#include <stdlib.h>

float mean(float *array, size_t nb_elem)
{
    float product = 1.0f;
    float *x = array;
    for(size_t i=0; i<nb_elem; i++){
        product *= *x++;
    }
    return pow(product, 1.0/nb_elem);
}
