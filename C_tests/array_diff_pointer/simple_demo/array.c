#include <stdio.h>

int glb_arr[4] = {0xdeadbeef, 0xbaadc0de, 0, 2};

int array_func(){

    printf("Address of the array glb_arr is %p\n", &glb_arr);
    printf("Address of first elment of the array glb_arr is %p\n", &(glb_arr[0]));

    return 0;
}
