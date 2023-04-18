#include <stdio.h>

int main(void){
    printf("Double precision\n");
    double a = 7.0/3.0;
    double b = 4.0/3.0;
    double c = 1;
    double r = a - b -c;
    printf("    7/3 - 4/3 - 1 = %.26f\n", r);
    printf("Single precision\n");
    float fa = 7.0/3.0;
    float fb = 4.0/3.0;
    float fc = 1;
    float fr = fa - fb - fc;
    printf("    7/3 - 4/3 - 1 = %.26f\n", fr);
    return 0;
}

