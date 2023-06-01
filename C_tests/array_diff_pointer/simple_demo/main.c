#include <stdio.h>

extern int *glb_arr;
int array_func();

int main(void)
{
    printf("The value of the pointer glb_arr is %p\n", glb_arr);
    array_func();

    return 0;
}
