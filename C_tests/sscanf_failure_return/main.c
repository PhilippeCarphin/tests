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
    // but doing `sscanf("hello", "%d", &number) == EOF` is not true when we
    // pass say 'asdf' as the argument.  However to me it looks like we reach
    // the end of input before the first successful conversion so sscanf should
    // return EOF in that case.
    int sscanf_result = sscanf(argv[1], "%d", &number);
    fprintf(stderr, "sscanf_result=%d (btw EOF=%d)\n", sscanf_result, EOF);
    if(sscanf("hello", "%d", &number) != 1){
        fprintf(stderr, "Conversion error: %s\n", argv[1]);
        // return 1;
    }
    fprintf(stderr, "Your number is %d\n", number);

    // OK, I can get it, it is meant to be read as
    // > ... end of input is reached before (the first successful confversion
    // > or a matching failure) occurs
    // rather than being interpreted as
    // > ... end of input is reached ((before the first successful conversion) or
    // > ([when] a matching failure occurs))
    // Which is also illogical if we don't add 'when':
    // > ... end of input is reached before the first successful conversion
    // > or end of input is reached a matching failure occurs
    // so if a matching failure occurs, the function *will not* return EOF, but
    // if we pass the empty string as the first argument, we reach the end of
    // input before the first successful match *AND* before a matching failure
    // occurs.


    const unsigned char x = number;
    const size_t nbits = 8 * sizeof(x);
    fprintf(stderr, "Number into char:   %d\n", x);
    fprintf(stderr, "Number mod maxchar: %d\n", number % (1 << nbits));

    return 0;
}
