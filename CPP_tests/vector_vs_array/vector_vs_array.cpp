#include <iostream>
#include <vector>

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    std::vector<int> my_vec;

    const unsigned int max = 10;
    for(unsigned int i = 0; i < max; i++){
        my_vec.push_back(i);
    }

    std::cout << "Address of the first element " << &my_vec[0] << std::endl;
    std::cout << "Address of the vector" << &my_vec << std::endl;
    std::cout << "vector.data() " << my_vec.data() << std::endl;

    return 0;

}
