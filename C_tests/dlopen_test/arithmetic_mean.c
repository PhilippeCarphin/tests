#include <stdlib.h>

float mean(float *array, size_t nb_elem)
{
    float sum = 0.0f;
    float *x = array;
    for(size_t i=0; i<nb_elem; i++){
        sum += *x++;
    }
    return sum/nb_elem;
}
