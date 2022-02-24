#include <map>
#include <string>
#include <iostream>

void print_map(std::map<std::string, std::string> &dict){
    for(auto it : dict){
        std::cout << it.first << ": " << it.second << std::endl;
    }
}

void clear_map(std::map<std::string, std::string> &dict){
    for(auto it = dict.begin();it != dict.end(); ++it){
        dict.erase(it);
    }
}

int main(){
    std::map<std::string, std::string> dict;

    dict["phil"] = "6954 de Lanaudiere";
    dict["paul"] = "12264 de Poutrincourt";

    print_map(dict);
    clear_map(dict);
    print_map(dict);

    return 0;
}
