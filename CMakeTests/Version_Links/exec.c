#include "lib.h"

int main(int argc, char **argv)
{
    char *name;
    if(argc > 1){
        name = argv[1];
    } else {
        name = "World";
    }

    greet(name);

    return 0;
}
