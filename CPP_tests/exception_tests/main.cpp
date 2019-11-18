#include <exception>

//
// Created by afsmpca on 19-08-15.
//

#include <exception>
#include <string>
struct spooki_validation_error : public std::exception
{
private:
    std::string _msg;
public:
    explicit spooki_validation_error(std::string msg):_msg(msg){}
    virtual const char* what() const throw()
        {
            return _msg.c_str();
        }
};

struct spooki_null_level_error : public std::exception
{
private:
    std::string _msg;
public:
    explicit spooki_null_level_error(std::string msg):_msg(msg){}
    virtual const char* what() const throw()
        {
            return "spooki_null_level_error happened";
        }
};

int throw_except(){
    std::string msg("Hello");
    throw spooki_null_level_error(msg);
}

int main(void)
{
    try{
        
    } catch(spooki_null_level_error &e){
        std::cout << e.what() << std::endl;
    }
}
