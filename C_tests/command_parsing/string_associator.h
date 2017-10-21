#ifndef STRING_ASSOCIATOR_H_
#define STRING_ASSOCIATOR_H_

/*
 * Allows for the quick association of strings with integers
 * usually associating members of an enum with string representations
 * 
 * One must define an array of string_associator terminated with {0,0}
 * to pass to the functions.
 * 
 * EXAMPLE : 
 
		enum flag {YELLOW = 4, GREEN = 1, RED = 2, BLUE = 3};
		struct string_associator flag_associator[] = {
			{ YELLOW, "yellow"},
			{ GREEN, "green"},
			{ RED, "red"},
			{ BLUE, "blue"},
			{ 0, 0}
		};

 * Since str_associated_to() returns the actual str_val from the array,
 * it is a good idea to make it a static global array in the 
 * .c file (NOT THE .h FILE!) where it will need to be visible.
 *
 * One could use this scheme and expand the int_val to an actual struct
 * with more information
 */

struct string_associator{
	int int_val;
	char *str_val;
};

int int_associated_to(char *str, struct string_associator *ass);
char *str_associated_to(int int_val, struct string_associator *ass);

#endif
