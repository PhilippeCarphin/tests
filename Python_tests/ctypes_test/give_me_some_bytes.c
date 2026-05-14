#include <stdio.h>
#include <inttypes.h>

int give_me_some_bytes(void *_bytes, int n_bytes, void *output_array){
    uint8_t *bytes = (uint8_t*)_bytes;
    int i = 0;
    fprintf(stderr, "%s() Printing bytes starting at address %p\n", __func__, _bytes);
    for(int i = 0; i < n_bytes; i++){
        uint8_t byte = bytes[i];
        fprintf(stderr, "bytes[%d]='%c' (%d)\n", i, byte, byte);
    }
    return 0;
}
