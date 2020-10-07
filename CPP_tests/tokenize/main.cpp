#include <sstream>
#include <string>
#include <vector>
#include <iostream>

int main(void){
    std::string s = "This\tis\na    sentence\\ asdf";
    std::istringstream iss(s);
    std::vector<std::string> words;
    std::cout << s.substr(8);
    for(std::string w; iss >> w;){
        words.push_back(w);
    }

    for(auto w : words){
        std::cout << w << std::endl;
    }
    return 0;
}

