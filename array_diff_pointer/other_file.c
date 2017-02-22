#include <stdio.h>
#include <stdlib.h>
#include <string.h>


unsigned long int other_array[10] = {0,1,2,3,4,5,6,7,8,9};
unsigned long int bad_array[5] = {4,3,2,1,0};

int other_function()
{
	printf("\t%s:%s() called\n",__FILE__, __FUNCTION__);
	printf("\t%s: &bad_array[0] = %p\n",__FILE__, &(bad_array[0]));
	printf("\t%s: &bad_array[3] = %p\n",__FILE__, &(bad_array[3]));
	printf("\t%s:  bad_array[0] = %d\n",__FILE__, bad_array[0]);
	printf("\t%s:  bad_array[3] = %d\n\n",__FILE__, bad_array[3]);
	printf("\t%s:     bad_array = %p\n\n",__FILE__, bad_array);
	return 0;
}
