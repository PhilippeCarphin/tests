
#include <vector>
#include <string>
#include <memory>
#include <iostream>
#include "OtherClass.h"

#include "PhilLogger.hpp"
class LoggerCreator {
public:
    LoggerCreator(){PhilLogger::instance()->log_special("Creating the logger");}
};


LoggerCreator lc;
OtherClass g_oc;
std::unique_ptr<PhilLogger> PhilLogger::_instance;
int main(void){

    std::cout << "start of main, first use of PhilSingleton::instance() ..." << std::endl;
    PhilLogger::instance()->log_special("Hello: we dont want short string optimization");

    std::cout << "End of main" << std::endl;

}
