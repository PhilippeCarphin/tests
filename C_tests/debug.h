/*
 * A cool file with some debugging macros to print the values of variables
 * without having to write a debug message.
 *
 * Should be included in any substancial project where some listings might be
 * useful.
 */

#ifdef PHIL_DEBUG
#define DBG_PRINT(...) fprintf(stderr,"%s():%d ",__func__, __LINE__);fprintf(stderr,__VA_ARGS__)
#else
/*
 * THis is important because if it were just
 * #define DBG_PRINT(...)
 * then it would be ok to have
 * DBG_PRINT()
 * with no ';' but when you turn on debugging, all those places missing a ';'
 * would cause errors that were not there before.
 *
 * Now you could include the ';' in the above and still have DBG_PRINT() expand
 * to nothing when PHIL_DEBUG is not defined.  That would cause worse problems
 * because
 *
 * if(error)
 *    DBG_PRINT(...) // no ';' here because we included it in the definition
 * do_this();
 *
 * Because the if has no '{}', turning debugging off will result in do_this()
 * being executed only if error is true
 *
 * The following way is the cannonical way of doing it.  It creates an empty
 * statement.
 */
#define DBG_PRINT(...) do { } while(0)
#endif

#define IVAL(i)        DBG_PRINT("Value of integer " #i " is %d\n", i)

#define SVAL(s)        DBG_PRINT("Value of string " #s " is %s\n", s)

#define VARVALUE(v,t)  DBG_PRINT("Value of variable " #v " is " #t "\n", v)

#define FUNCBEGIN      DBG_PRINT("BEGIN\n");

#define FUNCEND        DBG_PRINT("END\n");
