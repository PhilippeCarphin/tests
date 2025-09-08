#include <stdio.h>

int maybe_in_maybe_out(int *num_ptr, int b, int c){

    if (*num_ptr < 100) {
        // We're in intent(IN) mode
        fprintf(stderr, "num == %d < 100, using this value\n", *num_ptr);
    } else {
        // We're in intent(OUT) mode
        fprintf(stderr, "num == %d >= 100, finding a value\n", *num_ptr);
        *num_ptr = 8 * (b+c);
    }
    return *num_ptr;
}
