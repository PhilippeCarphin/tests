//
// Created by Philippe Carphin on 2019-10-14.
//

#include "OtherClass.h"
#include "PhilLogger.hpp"

void OtherClass::method(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

OtherClass::~OtherClass(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    PhilLogger::instance()->log_special(std::string("OC_DESTROY ") + __PRETTY_FUNCTION__);
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

OtherClass::OtherClass(){
    for(int i = 1; i < 1000 ; i++) {
        PhilLogger::instance()->log_special(std::string("This is a string ") + __PRETTY_FUNCTION__);
    }
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // PhilLogger::instance()->log_special(std::string("This is a string ") + __FUNCTION__);
}
