#include <ctype.h>
#include <stdio.h>
#include <string.h>

int strip_whitespace(char *str)
{
    char *p = str + strlen(str);

    /*
     * Make p point to first non-blank starting from the end of the string
     */
    while( *--p == ' '){
        if(p < str) {
            fprintf(stderr, "String is all blank chars\n");
            break;
        }
    }

    /*
     * Put '\0' AFTER first non blanck character
     */
    *++p = '\0';

    return 0;
}

int test(const char *str, const char *expected)
{
    size_t size = strlen(str)+1;
    char s[size];
    strncpy(s, str, size);
    strip_whitespace(s);
    if(strcmp(s, expected)){
        fprintf(stderr, "Expected result '%s' from strip_whitespace(\"%s\"), got '%s'\n", expected, str, s);
        return 1;
    }
    return 0;
}

int main(void)
{
    test("abcd    ", "abcd");
    test("xyz", "xyz");
    test("    ", "");
    test("xy ", "xy");
    char s[] = "        ";
    char *p = s+4;
    strip_whitespace(p);
    fprintf(stderr, "p = %p, s = %p\n", p, s);
    test(p, "");
    return 0;
}
