#include <stdlib.h>
#include <string.h>
#include "string_associator.h"
#include "lookup_struct.h"

/******************************************************************************
 * Lookup table of structs
 ******************************************************************************/
struct the_struct the_structs[] = 
{
	{
		.name = "first",
		.int_val = 1,
		.float_val = 3.14,
		.enum_val = A
	},
	{
		.name = "second",
		.int_val = 2,
		.float_val = 500000.0,
		.enum_val = B
	},
	{
		.name = "third",
		.int_val = 3,
		.float_val = 8,
		.enum_val = C
	}
};

/******************************************************************************
 * Lookup function
 ******************************************************************************/
struct the_struct *lookup_struct(const char *name, struct the_struct the_structs[])
{
	struct the_struct *ts;
	for(struct the_struct *ts = the_structs; ts->name != NULL; ++ts){
		if(strcmp(name, ts->name))
		{
			return ts;
		}
	}
	return NULL;
}
