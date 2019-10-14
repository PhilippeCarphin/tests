#include "PhilLogger.hpp"
#include "OtherClass.h"


PhilLogger::PhilLogger(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
}

PhilLogger::~PhilLogger(){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    for(auto v : special_messages){
        std::cout << "  " << v << std::endl;
    }
}
void PhilLogger::log_special(std::string m){
    special_messages.push_back(m);
}
const std::unique_ptr<PhilLogger> & PhilLogger::instance(){
    static bool called = false;
    if(!_instance && !called){
        _instance = std::make_unique<PhilLogger>();
        called = true;
    } else {
        _instance = nullptr;
    }
    return _instance;
}
