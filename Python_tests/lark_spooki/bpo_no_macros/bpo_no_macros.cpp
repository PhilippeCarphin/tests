#include <boost/program_options.hpp>
#include <map>
#include <iostream>
#include <string>

namespace bpo = boost::program_options;

typedef std::map<std::string, std::string> option_description;
typedef std::vector<option_description> options_collection;
enum my_enum {
    ACTUAL = 0,
    FINAL,
    NB_MEMBERS
};

std::ostream & operator<<(std::ostream & os, const my_enum & value){
    switch(value){
        case ACTUAL:
            os << "ACTUAL";
            break;
        case FINAL:
            os << "FINAL";
            break;
        case NB_MEMBERS:
            os << "NB_MEMBERS";
            break;
        default:
            break;
    }
    return os;
}
class OperationBase{

public:
    bpo::options_description specific_options;

    // options_collection opts_basic_def(void){

    //     options_collection options;
    //     std::map<std::string, std::string> lifted_from = {
    //         {"name", "liftedFrom"},
    //         {"sname", ""},
    //         {"type", std::string()}
    //     };

    //     options.push_back(lifted_from);

    //     return options;
    // }
};

int main(void){

    OperationBase o;
    // options_collection options = o.opts_basic_def();
    // for(option_description od : options){
    //     std::cout << "name" << od["name"] << std::endl;
    //     std::cout << "type" << typeid(od["type"]).name() << std::endl;
    // }
    for(int i = 0; i < my_enum::NB_MEMBERS ; i++){
        std::cout << my_enum(i) << std::endl;
    }
    std::string s = "1234567890";
    size_t sz = s.size();
    assert(s == s.substr(0, sz));
    std::cout << "size: " << s.size() << std::endl;
    std::cout << "substring: " << s.substr(0, sz-1) << std::endl;
    std::cout << "last char" << s[sz-1] << std::endl;
    return 0;
}