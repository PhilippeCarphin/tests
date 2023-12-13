#include <iostream>
#include "lib.hpp"

Person::Person()
{
    // std::cout << "C++: Constructor of Person, name = " << this->name << std::endl;
    std::cout << "C++: Constructor of Person" << std::endl;
}

void Person::say_hello()
{
    // std::cout << this->name << "says 'Hello'" << std::endl;
    std::cout << "C++: An instance of Person " << "says 'Hello'" << std::endl;
}




static Person mc;

extern "C" {
    int say_hello(const char *name){
        std::cout << "C++: Hello " << name << std::endl;
        // Person mcc("Phil");
        // mc.say_hello();
        return 0;
    }
}
