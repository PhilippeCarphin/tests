#include <unistd.h>
#include <string>
#include <iostream>

int main(int argc, char **argv)
{
    if(argc < 2){
        std::cout << "Please provide the path to a file" << std::endl;
        return -1;
    }

    std::string path{argv[1]};

    int result = access(argv[1], W_OK);

    if(result == 0){
        std::cout << "You have permission to write to this file" << std::endl;
        return 0;
    } else {
        std::cout << "You cannot write to this file" << std::endl;
        return 1;
    }

}