#include "climbingstats.h"
#include <stdio.h>

void climb_print(struct Climb *c)
{
    printf("Info on climb %d\n", c->id);
    printf("    difficulty : %d\n", c->difficulty);
}
