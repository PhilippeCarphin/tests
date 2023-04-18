#include <stdio.h>
/*
 * This test demonstrates the '-Wimplicit-fallthrough' GCC warning along
 * with the '__attribute__((fallthrough))' which can be used to prevent
 * the warning from being issued when fallthrough is desired.  It needs to
 * be put directly before a case label for which falling through from the
 * previous label is desired.
 *
 * With -Wimplicit-fallthrough, a case in a switch that ends with a statement
 * other than "break;" or "return ...;" will be marked with "This statement may
 * fall through".  Note that for the default case, the line 'if (1)' is marked
 * because the whole 'if(1){...}else{...}' is the last statement of the
 * switch.
 *
 * Also note that only non-empty cases without "break/return" cause a warning
 * that's because there is no reason to put an empty case if you don't want
 * fallthrough.
 *
 * "case 'a'" demonstrates that empty cases do not generate implicit fallthrough
 * warnings.
 *
 * "case 'b'" demonstrates the use of '__attribute__((fallthrough))'.  It is
 * put immediately before the 'case c' to tell the compiler that falling through
 * from 'b' to 'c' is the desired behavior.
 *
 * "case 'c'" is a proper case that ends with a 'break;'
 *
 * "case 'd'" demonstrates the '-Wimplicit-fallthrough' warning.
 */

int switch_func(char c)
{
    printf("%s(%c):\n", __func__, c);
    switch(c){
        case 'a':
        case 'b':
            printf("    case 'b'...\n");
            __attribute__((fallthrough));
        case 'c':
            printf("    a or b or c\n");
            break;
        case 'd':
            if (1) {
            // ^ warning: this statement may fall through [-Wimplicit-fallthrough=]
                printf("    d : true\n");
            } else {
                printf("    d : false\n");
                break;
            }
        default:
            printf("    default\n");
    }
    return 0;
}

int main(void)
{
    switch_func('a');
    switch_func('b');
    switch_func('x');
    return 0;
}

