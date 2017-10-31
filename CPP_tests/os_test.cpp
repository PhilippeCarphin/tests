#include <iostream>
/*
 * This demonstrates how put code for the OS using macros
 */

void print_OS()
{

	printf("OS is ");
#ifdef __APPLE__
	printf("MacOS\n");
#endif

#ifdef _WIN32
	prinff("Windows 32 bit or windows 64 bit");
#endif

#ifdef __WINDOWS__
	prinf("__WINDOWS__ is defined\n");
#endif

}

int main(void)
{
	print_OS();
	return 0;
}

