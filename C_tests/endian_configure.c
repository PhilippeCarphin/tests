// from https://stackoverflow.com/a/12792056/5795941
// and used in configure scripts
#include <inttypes.h>
int main(int argc, char ** argv){
    volatile uint32_t i=0x01234567;
    // return 0 for big endian, 1 for little endian.
    return (*((uint8_t*)(&i))) == 0x67;
}
