#include <stdio.h>
#include <stdlib.h>

extern char *ext;

int main(void){

    char  *in[2];
    char **in_p = malloc(8 * sizeof(*in_p));

    fprintf(stderr, "       &in = %p (where the array lives)\n", &in);
    fprintf(stderr, "        in = %p (address of its first element)\n", in);

    fprintf(stderr, "     &in_p = %p (where the pointer lives) \n", &in_p);
    fprintf(stderr, "      in_p = %p (value of the pointer)\n", in_p);
    fprintf(stderr, "&(in_p[0]) = %p (value of the pointer)\n", &(in_p[0]));

    /*
     * Get the first element from an array
     * - Find where that array lives
     *   that's the address of the first elment
     */

    /*
     * Get the first element from an array using a pointer
     * - Find where the pointer lives (&ptr)
     * - Get the address stored there
     * - get the value at the address stored in ptr.
     */

    /*
     * Mix it up and get errors
     * - Look where ext lives, that's &ext,
     * - Get the address stored there (we're going to get the 8 bytes 'This is '
     * - Get the value at the addresss whose bytes are 'This is '
     * - SEGFAULT!!!
     */
    fprintf(stderr, "      &ext = %p (where the pointer lives) \n", &in_p);
    fprintf(stderr, "      ext  = %p (value of the pointer)\n", in_p);
    fprintf(stderr, "      &(ext[0]) = %p (where the pointer lives) \n", &in_p);
    long unsigned int ptr_val = (long unsigned int)ext;
    char eight_bytes[9] = {
        (ptr_val & 0xFF),
        ((ptr_val >> 8) & 0xFF),
        ((ptr_val >> 16) & 0xFF),
        ((ptr_val >> 24) & 0xFF),
        ((ptr_val >> 32) & 0xFF),
        ((ptr_val >> 40) & 0xFF),
        ((ptr_val >> 48) & 0xFF),
        ((ptr_val >> 56) & 0xFF),
        '\0',
    };

    fprintf(stderr, "      ext = '%s'\n", eight_bytes);
    // char c = ext[0];
    // fprintf(stderr, "The first char of ext is %c\n", c);

    int     *int_ptr = (void*)0x1000;
    short *short_ptr = (void*)0x1000;

    fprintf(stderr, "int_ptr + 20: %p\n", int_ptr+20);
    fprintf(stderr, "short_ptr + 20: %p\n", short_ptr+20);
    fprintf(stderr, "&(int_ptr[20): %p\n", &(int_ptr[20]));
    fprintf(stderr, "&(short_ptr[20): %p\n", &(short_ptr[20]));
    if(int_ptr == short_ptr){
        fprintf(stderr, "same value\n");
    } else {
        fprintf(stderr, "different value\n");
    }
    return 0;
}

