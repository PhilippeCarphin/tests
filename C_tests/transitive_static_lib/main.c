#include <stdio.h>
#include "dotproduct.h"

int main(int argc, char **argv) {
    int a[] = {1,2,3,4};
    int b[] = {2,3,4,5};
    size_t na = sizeof(a)/sizeof(*a);
    size_t nb = sizeof(b)/sizeof(*b);
    int a_dot_b;
    int err = dot_product(a, na, b, nb, &a_dot_b);
    if(err){
        fprintf(stderr, "Failed to compute dot product\n");
    }
    printf("a dot b = %d\n", a_dot_b);
    return 0;
}
