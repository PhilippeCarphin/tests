#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "phil.h"

int main(void)
{
	printf("Included file defines Phil as %s\n", PHIL);
	printf("Included from include file defines paul as %s\n", PAUL);

#ifdef MACRO_IN_PAUL_H
	printf("MACRO_IN_PAUL_H is defined\n");
#else
	printf("MACRO_IN_PAUL_H is NOT defined\n");
#endif
	return 0;
}
