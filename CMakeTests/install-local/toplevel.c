#include <stdio.h>

int main(int argc, char **argv)
{
    printf("I am %s\n", argv[0]);
    for(int i = 1; i < argc; i++){
        printf("%s: argv[%d] = '%s'\n", argv[0], i, argv[i]);
    }
    return 0;
}
