#include <stdlib.h>
#include <stdio.h>

extern int f_print_two_ints();

int main(int argc, char **argv){

    long unsigned int i = 8;
    f_print_two_ints(i, &i);
    f_print_two_ints(i, i);
    return 0;
}

