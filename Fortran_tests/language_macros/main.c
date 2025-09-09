#include <stdio.h>

int main(void){

#ifdef __STDC_VERSION__
    fprintf(stderr, "__STDC_VERSION__ is YES defined\n");
#else
    fprintf(stderr, "__STDC_VERSION__ is NOT defined\n");
#endif
    return 0;
}
