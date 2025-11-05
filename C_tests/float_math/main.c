#include <stdio.h>

// This test was done following some article that was discussed at work about
// interesting things about floating point math.

int main(void){
    float f = 0.1f;
    float sum = 0.0f;

    for (int i = 0; i < 10; ++i){
        sum += f;
    }
    float product = f * 10;
    printf("sum = %1.15f, mul = %1.15f, mul2 = %1.15f\n", sum, product, f * 10);
    return 0;
}
