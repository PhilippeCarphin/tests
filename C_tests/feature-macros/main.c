int printf(const char *fmt, ...);
#define isdefed(a) printf(#a " is defined\n");
#define isndefed(a) printf(#a " is NOT defined\n");
#define printvall(a) printf(#a " has value %ld\n", a - 0);
#define printval(a) printf(#a " has value %d\n", a - 0);


int main_pre(){
#include "check.h"
    return 0;
}

// #define _ISOC99_SOURCE
// #define _XOPEN_SOURCE 400
// #define __STRICT_ANSI__
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main_after(){
#include "check.h"
    return 0;
}

int main(int argc, char **argv){
#ifndef JUST_AFTER
    printf("\033[1;34mMain defined before including any headers\033[0m\n");
    main_pre();
#endif
#ifndef JUST_BEFORE
    printf("\033[1;34mMain defined after including any headers\033[0m\n");
    main_after();
#endif
    return 0;
}
