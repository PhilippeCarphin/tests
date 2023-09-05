#include <stdio.h>
#include <stdint.h>

/*
 * This test demonstrates that you can pass a pointer to whatever you want
 * to a function that takes void* but if you pass the wrong type of pointer
 * to a function that takes uint32_t*, then you will get at least a warning
 * and that is if you are not using -Werror=incompatible-pointer-types
 *
 * When passing the wrong type of pointer, the most likely warning is
 * -Wincompatible-pointer-types except in the following:
 *
 * When the pointer passed and the pointer expcted by the function differ only
 * in signedness, no -Wincompatible-pointer-type is issued and instead a
 * -Wpointer-sign warning is issued.
 *
 * See void_star_conversion for details on how a function that should take
 * void star but doesn't can be converted to the appropriate form.
 */

int take_void_star(void* p){
    fprintf(stderr, "%s(%p)\n", __func__, p);
    return 0;
}

int take_uint32_star(uint32_t *p)
{
    fprintf(stderr, "%s(%p)\n", __func__, p);
    return 0;
}

int main(void)
{
    uint32_t uint32_val = 8;
    int int_val = 8;
    char char_val[10];
    take_void_star(&uint32_val);
    take_void_star(char_val);
    take_void_star(&int_val);
    take_uint32_star(&int_val); // -Wpointer-sign
    take_uint32_star(&uint32_val);
    take_uint32_star(char_val); // -Wincompatible-pointer-types
}
