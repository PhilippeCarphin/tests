#include <iostream>
/*
 * This test shows that case identifiers need to be compile time constants.
 */

#define LOWER_BOUND 25
#define UPPER_BOUND 35

int switch_with_expression(int in)
{
	switch(in){
	case LOWER_BOUND < in && in < UPPER_BOUND:
		std::cout << "in is between the bounds" << std::endl;
		break;
	default:
		std::cout << "in is not between the bounds" << std::endl;
		break;
	}
	return 0;
}

int main(void)
{
	int input = 30;
	switch_with_expression(input);
	return 0;
}


