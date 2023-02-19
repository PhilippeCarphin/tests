#include "climber.h"
#include <stdio.h>

void climber_print(struct Climber *c)
{
    printf("Stats for climber %d\n", c->id);
    printf("    name: %s\n", c->name);
}

