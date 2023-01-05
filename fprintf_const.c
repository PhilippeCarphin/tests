#include <stdio.h>

/*
 * This test demonstrates that a 'const char*' can be passed to fprintf
 * without causing Wdiscarded-qualifiers warnings
 */
int do_Login(const char *node){

    fprintf(stderr, "This is a the value of a const char * : '%s'\n", node);

    return 0;
}

int main(void){

    const char *node = "const correctness FTW";

    do_Login(node);

    return 0;
}
