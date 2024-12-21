#include <stdlib.h>
#include <stdio.h>
#include "greet.h"

#ifndef PLATFORM
# define PLATFORM "Unknown"
#endif

int main(int argc, const char **const argv){

    for(int i=0; i<argc; i++){
        fprintf(stderr, "arg[%d] = '%s'\n", i, argv[i]);
    }
    fprintf(stderr, "PLATFORM='%s'\n", PLATFORM);
    if(argc > 1){
        greet(argv[1]);
    }

    return 0;
}
