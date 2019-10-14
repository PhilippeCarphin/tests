//
// Created by Philippe Carphin on 2019-10-14.
//

#ifndef DEST_TEST_PHILLOGGER_HPP
#define DEST_TEST_PHILLOGGER_HPP


#include <vector>
#include <string>
#include <memory>
#include <iostream>

class PhilLogger {
public:
    std::vector<std::string> special_messages;

    ~PhilLogger();
    void log_special(std::string m);
    static const std::unique_ptr<PhilLogger> & instance();

    PhilLogger();
    static std::unique_ptr<PhilLogger> _instance;
};

#endif //DEST_TEST_PHILLOGGER_HPP
