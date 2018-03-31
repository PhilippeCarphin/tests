#include <iostream>

/*
 * This shows how the warning of unused parameter can be dealt with by casting
 * to void.  This is useful in the context of polymorphism when the
 * implementation in the base class may not use parameters that are intended to
 * be used by the implementations in the derived classes.
 */
int unused_param(int param)
{
	(void) param;
	return 42;
}


int main(void)
{

	std::cout << "Hello world" << std::endl;
	return 0;
}
