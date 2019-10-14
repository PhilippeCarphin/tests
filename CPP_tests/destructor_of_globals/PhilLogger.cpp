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
std::unique_ptr<PhilLogger> & PhilLogger::instance(){
    if(!_instance){
        _instance.reset(new PhilLogger());
    }
    return _instance;
}
