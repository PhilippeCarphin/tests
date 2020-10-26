#include <string>
#include <libgen.h>
#include <sstream>
#include <iostream>
#include <string.h>

std::string cpp_dirname(std::string path)
{
    char * work_path = strdup(path.c_str());

    std::cout << __FUNCTION__ << "() : work_path = '" << work_path << "'" << std::endl;

    char * tmp_output_dirname = dirname(work_path);
    if(tmp_output_dirname == NULL){
        std::ostringstream oss;
        oss << "Could not get dirname of output path '" << path << "'";
        throw std::runtime_error(oss.str());
    }

    std::cout << __FUNCTION__ << "() : work_path = '" << work_path << "'" << std::endl;
    std::cout << __FUNCTION__ << "() : tmp_output_dirname = '" << tmp_output_dirname << "'" << std::endl;

    std::string output = tmp_output_dirname;
    free(work_path);

    return output;
}

int main(void)
{
    std::cout << cpp_dirname("CMakeLists") << std::endl;
    std::cout << cpp_dirname("/home/phc001/workspace/spooki/CMakeLists.txt") << std::endl;
    std::cout << cpp_dirname("CMakeLists") << std::endl;

    return 0;
}
