/*
 * A cool file with some debugging macros to print the values of variables
 * without having to write a debug message.
 *
 * Should be included in any substancial project where some listings might be
 * useful.
 */

#ifdef DEBUG
#define DBG_PRINT(...) printf(__VA_ARGS__)
#else
#define DBG_PRINT(...) do{}while(0)
#endif

#define IVAL(var) printf("%s() line %d: Value of integer " #var " is %d\n",    \
													__func__,__LINE__, var)

#define SVAL(var) printf("%s(): line %d: Value of string " #var " is %s\n",    \
													__FUNCTION__,__LINE__, var)

#define VARVALUE(var,type) DBG_PRINT("%s() line %d: Value of variable " #var   \
								" is " #type "\n", __FUNCTION__, __LINE__, var)
