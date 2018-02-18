#include <stdlib.h>
#include <stdio.h>
#include "object_counter.h"

int object_count = 0;

void print_object_count()
{
	printf("print_object_count(): %d\n", object_count);
}

