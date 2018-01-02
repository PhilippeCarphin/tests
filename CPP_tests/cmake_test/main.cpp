#include <iostream>

int main(int argc, char **argv)
{
	for(unsigned int i = 0; i < argc; ++i){
		std::cout << "argv[" << i << "] : " << argv[i] << std::endl;
	}
	return 0;
}
