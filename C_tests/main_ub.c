#include <stdio.h>
#include <inttypes.h>

int some_func(int* z){
    fprintf(stderr, "E: %s(): z=%d\n", __func__, *z);
    return 0;
}

int some_func_val(int z){
    fprintf(stderr, "%s(): z=%d\n", __func__, z);
    return 0;
}

#ifdef WITH_ABCDE
int read_int(const char *s, int *n){
    if(sscanf(s, "%d", n) != 1){
        fprintf(stderr, "Could not convert '%s' to int\n", s);
        return 1;
    } else {
        return 0;
    }
}
#endif

int main(int argc, char **argv){

#ifdef WITH_ABCDE
    int a, b, c, d, e;
#endif
    // Prevent the compiler from optimizing since the variables will get a value
    // at runtime.
    int32_t zigzag;
#ifdef WITH_ABCDE
    switch(argc){
        // case 7: read_int(argv[6], &zigzag);
        case 6: read_int(argv[5], &e);
        case 5: read_int(argv[4], &d);
        case 4: read_int(argv[3], &c);
        case 3: read_int(argv[2], &b);
        case 2: read_int(argv[1], &a);
        default: break;
    }
    fprintf(stderr, "a=%d, b=%d, c=%d, d=%d\n", a,b,c,d);
#endif


    fprintf(stderr, "A: zigzag = %d\n", zigzag);

    // if(zigzag != 0){
    //   fprintf(stderr, "B: 'if(zigzag != 0)': value of zigzag: %d\n", zigzag) ;
    // }

    // if(zigzag == 0){
    //   fprintf(stderr, "C: 'if(zigzag == 0)': value of zigzag: %d\n", zigzag) ;
    // }

    fprintf(stderr, "D: zigzag = %d\n", zigzag);

    // Uncommenting this changes behavior of the above code
    some_func(&zigzag);

    // This one doesn't look like it changes anything
    // some_func_val(zigzag);
}

/*
 * COMPILER | CASE 7        | some_func(&zigzag) || What is seen | Values
 * ====================================================================================
 * icx      | commented     | commented          ||  A, D,       | same values  | -----
 * icx      | commented     | active             ||  A, B, C, D, | (B==D) != A  | E = 0
 *
 * With the extra integers a,b,c,d,e and the switch, we have A==B==D.
 */
