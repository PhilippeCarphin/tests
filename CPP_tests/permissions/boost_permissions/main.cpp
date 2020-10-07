#include <boost/filesystem.hpp>
#include <iostream>
#include <unistd.h>
#include <string>
#include <libgen.h>
#include <sstream>


std::string cpp_dirname(std::string path) {
    // Man dirname says not to free pointers returned by dirname and basename
    return dirname(const_cast<char*>(path.c_str()));
} 

bool writer_std_path_is_valid_1(std::string path){
    if(boost::filesystem::is_directory(path)){
        std::cout << "Path provided is an existing directory, you must provide a filename for the output of WriterStd" << std::endl;
        return -1;
    } else {
        std::cout << "Path provided is not an existing directory" << std::endl;
        if (boost::filesystem::exists(path)){
            std::cout << "    Path provided is an existing file, checking for write permissions to this file" << std::endl;
            if(access(path.c_str(), W_OK) == 0){
                std::cout << "        We can write to the file" << std::endl;
                return true;
            } else {
                std::cout << "        You do not have permission to write to the file" << std::endl;
                return false;
            }
        } else {
            std::cout << "    Path provided does not exist, checking if we can create the file" << std::endl;
            std::string dir = cpp_dirname(path);
            bool can_write = (access(dir.c_str(), W_OK|X_OK) == 0);
            if(can_write){
                std::cout << "        We can create the file" << std::endl;
            } else {
                std::cout << "        We cannot create the file" << std::endl;
            }
            return can_write;
        }
    }
}

bool can_write_file(std::string path){
    std::ofstream path_ofstream(path, std::ios::out);
    bool can_write = path_ofstream.is_open();
    if(can_write) {
        std::cout << "        We were able to open the file, so we can write to it (also we just created an empty file" << std::endl;
    } else {
        std::cout << "        We could not open the file, so we can't write and this is the most proper way to find out" << std::endl;
    }
    return can_write;
}

bool new_path_is_valid(std::string path){
    if(can_write_file(path)){
        return true;
    } else {
        std::cout << "Cannot open '" << path << "' for writing" << std::endl;
        return false;
    }
}

int main(int argc, char ** argv)
{
    
    if(argc < 2){
        std::cout << "Please provide a path as an argument" << std::endl;
        return -1;
    }

    // return writer_std_path_is_valid(argv[1]);
    return new_path_is_valid(argv[1]);


    //std::cout << cpp_dirname(argv[1]) << std::endl;
    //std::string output_dir = cpp_dirname(argv[1]);
    //if(){
    //    std::cout << "Output file '" << argv[1] << "' already exists, checking for write permission to this file" << std::endl;
    //} else {
    //    std::cout << "Output file does not exits, we will check if we can create it" << std::endl;
    //    if(access(output_dir.c_str(), W_OK) != 0)
    //    {
    //        std::cout << "CANNOT write to directory '" << output_dir << "'" << std::endl;
    //    } else {
    //        std::cout << "We have write permission to the directory" << std::endl;
    //    }
    //}

}