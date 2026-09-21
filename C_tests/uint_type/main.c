#ifdef INCLUDE_STDLIB
#include <stdlib.h>
#endif
#include <stdio.h>
#include <sys/time.h>


int main(int argc, char **argv){
#if defined(__INTEL_LLVM_COMPILER)
    fprintf(stderr, "Compiler is INTEL LLVM\n");
#elif defined(__INTEL_COMPILER)
    fprintf(stderr, "Compiler is INTEL (non-LLVM)\n");
#elif defined(__GNUC__)
    fprintf(stderr, "Compiler is GNU\n");
#endif
    uint x = 8;
    fprintf(stderr, "x = %u\n", x);
    return 0;
}

