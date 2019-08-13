#include <iostream>
#include <stdlib.h>
#include <sstream>


/*
 * This test demonstrates that constructing an istringstream with a NULL pointer
 * (for example from a failed getenv()) will cause a segfault.
 */
int main(int argc, char** argv)
{
    (void) argc;
    (void) argv;

    int level = 8;

    std::istringstream iss(getenv("SPOOKI_LOG_LEVEL"));

    iss >> level;
    std::cout << "Level = " << level << std::endl;

    return  level;
}
