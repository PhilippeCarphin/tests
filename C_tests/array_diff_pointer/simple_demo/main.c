#include <stdio.h>

extern int *glb_arr;
int array_func();

int main(void)
{
    printf("The value of the pointer glb_arr is %p\n", glb_arr);
    array_func();
    // Attempt to get the first element of the array
    int first_elem = glb_arr[0];

    printf("The value of the first element is %d\n", first_elem);
    return 0;
}
