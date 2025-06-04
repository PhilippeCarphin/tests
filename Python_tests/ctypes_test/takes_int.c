#include <stdio.h>

/*
 * This function is used to demonstrate automatic conversion of {True,False} to
 * {1,0} by ctypes.  See demo_bool_conversion.py.
 */

int not(int bool_val){
    fprintf(stderr, "Received the value %d\n", bool_val);
    return !bool_val;
}
