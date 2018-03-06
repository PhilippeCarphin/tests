#include <stdlib.h>
#include <stdio.h>
#include "object_counter.h"

int main(void)
{
	object_count = 3;
	print_object_count();
	printf("Object count from mai %d\n", object_count);
	return 0;
}

