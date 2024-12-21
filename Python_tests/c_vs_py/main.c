#include <stdio.h>
#include <unistd.h>

int main(void){
    uint64_t sum = 0;
    for(uint64_t i = 0; i < 1000000000 ; i++ ){
        sum += i;
    }
    printf("sum=%llu\n", sum);
}

