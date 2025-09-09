#include <stdio.h>

int read_int(const char *s, int *n){
    if(sscanf(s, "%d", n) != 1){
        fprintf(stderr, "Could not convert '%s' to int\n", s);
        return 1;
    } else {
        return 0;
    }
}

int main(int argc, char **argv)
{
    int a;
    int b;
    int c;
    int d;
    switch(argc){
        case 5: read_int(argv[4], &d);
        case 4: read_int(argv[3],&c);
        case 3: read_int(argv[2], &b);
        case 2: read_int(argv[1], &a);
        default: break;
    }

    fprintf(stderr, "a=%d, b=%d, c=%d, d=%d\n", a,b,c,d);

    return 0;
}
