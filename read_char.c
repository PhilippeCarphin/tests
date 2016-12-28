#include "debug.h"

/*
 * This just tests that the (*(*cursor_ptr)++) thing works the way I think it
 * should work.
 */
char read_char(char **cursor_ptr)
{
	return *(*cursor_ptr)++;
}

int main(void)
{
	char *s = "HELLO PHIL";

	char *cursor = s;

	char c;
	while((c = read_char(&cursor)) != 0)
	{
		printf("%c",c);
	}
	printf("\n");

	return 0;
}
