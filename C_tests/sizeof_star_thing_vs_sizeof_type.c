#include <stdio.h>
#include <stdlib.h>

#ifndef T
#define T char
#endif
#define stringify(x) #x

/*
 * This test is used to demonstrate that using sizeof(T) or sizeof(*a)
 * produces the same assembly code (which gcc).  In each case, the
 * expression is compiled to a litteral constant.
 *
 *      movl $8, %edi
 *      call malloc
 *
 * in the case of a double and GCC.
 *
 * This is all compile time stuff so there is no "dereferencing of a"
 * that happens at runtime.
 */

int main(void)
{
    size_t s = sizeof(T);

    T *a = malloc(sizeof(*a));

    T *b = malloc(sizeof(T));

    fprintf(stderr, "sizeof(%s): %lu\n", stringify(x), s);
    fprintf(stderr, "a=%p, b=%p", a, b);

    return 0;
}
