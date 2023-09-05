#include "coolclass.h"
#include <iostream>

int CoolClass::print(){
    std::cout << "Printing CoolClass at" << this << std::endl;
    std::cout << "    this->integer = " << this->integer << std::endl;
    std::cout << "    this->string = " << this->string << std::endl;
    return 0;
}

namespace A {

    namespace B {
        int namespace_function(){
            std::cout << __PRETTY_FUNCTION__ << std::endl;
            return 0;
}
}
}

int standalone_function(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return 0;
}
