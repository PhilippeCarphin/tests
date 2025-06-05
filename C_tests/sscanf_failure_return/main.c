#include <stdio.h>

int main(int argc, char **argv)
{
    if(argc < 2){
        fprintf(stderr, "Need one argument\n");
        return 1;
    }

    int number;
    // The manpage `man 3 sscanf` says
    // > The value EOF is returned if the end of input is reached before either
    // > the first successful conversion or a matching failure occurs.
    // but doing `sscanf(argv[1], "%d", &number) == EOF` is not true when we
    // pass say 'asdf' as the argument.  However to me it looks like we reach
    // the end of input before the first successful conversion so sscanf should
    // return EOF in that case.
    if(sscanf(argv[1], "%d", &number) != 1){
        fprintf(stderr, "Conversion error: %s\n", argv[1]);
        return 1;
    }
    fprintf(stderr, "Your number is %d\n", number);

    const unsigned char x = number;
    const size_t nbits = 8 * sizeof(x);
    fprintf(stderr, "Number into char:   %d\n", x);
    fprintf(stderr, "Number mod maxchar: %d\n", number % (1 << nbits));

    return 0;
}
