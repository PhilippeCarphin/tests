#include "coolstruct.h"
#include <stdio.h>

int print_cool_struct(struct CoolStruct *s)
{
    fprintf(stderr, "Printing CoolStruct at %p\n", s);
    fprintf(stderr, "    s->integer = %d\n", s->integer);
    fprintf(stderr, "    s->char_star = %s\n", s->char_star);
    return 0;
}
