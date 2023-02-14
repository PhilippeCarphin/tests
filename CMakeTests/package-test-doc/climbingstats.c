#include <stdio.h>
#include "climbingstats.h"

int print_climbing_stats(struct ClimbingStats *cs)
{
    fprintf(stderr, "Name: %s, level: %d\n", cs->name, cs->level);
    return 0;
}
