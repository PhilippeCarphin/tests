#include "func.h"

int main(int argc, char **argv)
{
    for(int i = 0; i < argc; i++){
        print_nth_string(argv, i);
    }
    return 0;
}
