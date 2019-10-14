//
// Created by Philippe Carphin on 2019-10-14.
//

#include "OtherClass.h"
#include "PhilLogger.hpp"

void OtherClass::method(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    PhilLogger::instance()->log_special(std::string("This is a string ") + __FUNCTION__);
}

OtherClass::~OtherClass(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    PhilLogger::instance()->log_special(std::string("This is a string ") + __FUNCTION__);
}

OtherClass::OtherClass(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    //PhilLogger::instance()->log_special(std::string("This is a string ") + __FUNCTION__);
}
