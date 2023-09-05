#include <stdint.h>
#include <stdio.h>

/*
 * This function is meant to take a pointer to arbitrary memory of more than
 * one type.  However because we intend to work on this memory four bytes at a
 * time, we chose to make the parameter uint32_t*.
 *
 * This is not a good idea because it lies to the users about what the function
 * can take.  They will get warnings about incompatible pointer types:
 * -Wincompatible-pointer-types or pointer sign problems -Wpointer-sign.
 *
 * Users of our library that work with -Werror=incompatible-pointer-types or
 * -Werror=pointer-sign will not be able to use our function.
 */
int original_func(uint32_t * ptr){
    unsigned char *p = (unsigned char *)ptr;
    uint32_t first_four_bytes = *ptr++;
    uint32_t next_four_bytes = *ptr++;
    fprintf(stderr, "%s(): first_four_bytes = %x\n", __func__, first_four_bytes);
    fprintf(stderr, "%s(): next_four_bytes = %x\n", __func__, next_four_bytes);
    fprintf(stderr, "%s(): %x,%x,%x,%x, %x,%x,%x,%x\n", __func__, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    return 0;
}

/*
 * Instead, we should use a signature that correctly communicates that our
 * function can take pointers to arbitrary types.  This does not stop us from
 * working in 4 byte chunks.  All we have to do is change the name of the
 * parameter name and declare a uint32_t* with the original name and we will
 * not have to modify any of the remaining code of the function
 */
int new_func(void * _ptr){
    uint32_t *ptr = (uint32_t *)_ptr;
    // Everything after this is the same as the previous function
    unsigned char *p = (unsigned char *)ptr;
    uint32_t first_four_bytes = *ptr++;
    uint32_t next_four_bytes = *ptr++;
    fprintf(stderr, "%s(): first_four_bytes = %x\n", __func__, first_four_bytes);
    fprintf(stderr, "%s(): next_four_bytes = %x\n", __func__, next_four_bytes);
    fprintf(stderr, "%s(): %x,%x,%x,%x, %x,%x,%x,%x\n", __func__, p[0], p[1], p[2], p[3], p[4], p[5], p[6], p[7]);
    return 0;
}

int main(void){

    long unsigned int i = 0x1122334455667788;
    int j[2] = {-0xeeddccbb - 1, 0x11223344};

    // original_func(&i); // -Werror=incompatible-pointer-types
    original_func(j); // -Wpointer-sign
    new_func(&i);
}
