#include <stdio.h>

int main(void){

    char string[] = "This is my string";

    const char * const_ptr;
    char * const ptr_const = string;

    const_ptr = string;
    const_ptr[8] = 'A';

    ptr_const[9] = 'B';

    printf("String '%s'\n", string);

    return 0;

}
