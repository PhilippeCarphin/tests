#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// #define DEBUG
#ifdef DEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...) do{}while(0)
#endif

/*
 * This test demonstrates the use of the operator '#' on a macro parameter.
 * The macro parameter is var, and the operator #var expands to "var"
 */

#define stringize(var) #var

/*
 * Note that this operator is necessary for doing this because the following
 * doesn't work:
 */

#define attempt(var) "var"

/*
 * The following are cool uses of this macro for debugging purposes
 * Note the use of the __FUNCTION__ and __LINE__ macros.  They are special
 * preprocessor macros that expand to a string litteral of the name of the
 * function in which it is found and integer litteral of the line number where
 * it is found.  There is also the __FILE__ macro that expands to a string
 * litteral of the file in which it is found.
 *
 * Also note that the __func__ and __FUNCTION__ macros are non-standard but are
 * supported at least in GCC.
 */
#define IVAL(var) printf("%s() line %d: Value of integer " #var " is %d\n",    \
													__func__,__LINE__, var)

#define SVAL(var) printf("%s(): line %d: Value of string " #var " is %s\n",    \
													__FUNCTION__,__LINE__, var)

#define VARVALUE(var,type) DBG_PRINT("%s() line %d: Value of variable " #var   \
								" is " #type "\n", __FUNCTION__, __LINE__, var)

/*
 * Note that macro definitions are terminated by a '\n' character.  So to fit
 * the definition of a macro on multiple lines a '\' is put before the '\n'
 * (the '\n' is invisible in text editors.  One danger here is that if you don't
 * put the '\' at the very end of the line, then it won't escape the '\n', it
 * will escape a space.  That's why it's useful if your editor either
 * automatically removes trailing whitespace like XILINX SDK, or shows it to you
 * in a displeasing way like vim with the plugin 'ntpeters/vim-better-whitespace'
 */

/*
 * Note that C auto-concatenates string litterals so
 * char *s = "HELLO " "WORLD";
 * is the same thing as
 * char *s = "HELLO WORLD";
 */


int main(int argc, const char **argv)
{
	int my_int = argc;
	int my_other_int = 8;
	const char *s = argv[0];

	/*
	 * The following illustrates the basic use of the '#' operator
	 * Use cpp strinising_macro_test.c > preprocessed to see for yourself.
	 */
	printf("This is a string litteral made with the preprocessor: %s\n",
									stringize(string litteral without quotes));
	/*
	 * Also the following illustrates the need for the stringsing operator
	 * As you can see using cpp, this macro will just always expand to the
	 * string litteral "var".
	 */
	printf("This is the bad attempt to stringize my_variable :%s\n",
									attempt(my_variable));

	/*
	 * And these are the results of using the other debugging macros. They
	 * illustrate what I think is the most useful way to use that operator.
	 */
	IVAL(my_int);
	IVAL(my_other_int);
	SVAL(s);

	printf("=========================\n");

	VARVALUE(my_int,%d);
	VARVALUE(s,%s);

	return 0;
}
