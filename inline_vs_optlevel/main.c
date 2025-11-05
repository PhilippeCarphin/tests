#include <stdio.h>

static inline int echo_int(int i){
    return i;
}

// extern inline int echo_int(int);

int main(void)
{
    fprintf(stderr, "The value of 8 is %d\n", echo_int(8));
}
