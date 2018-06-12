#include <stdio.h>
#include <stdlib.h>

int main(void){
    if ( (100 + 1.0/3) - 100 == 1.0/3 ){
        puts("true");
    } else {
        puts("false");
    }
    return 0;
}
