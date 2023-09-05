#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc < 2)
    {
        fprintf(stderr, "ERROR: An integer argument is required\n");
        return 1;
    }

    int i;
    sscanf(argv[1], "%d", &i);

    fprintf(stderr, "i = %d\n", i);
    fprintf(stderr, "as unsigned int: i = %u\n", (unsigned int)i);

    return 0;
}
