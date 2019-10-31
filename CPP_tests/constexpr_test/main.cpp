#include <iostream>

constexpr int my_function(){
    return 8;
}

constexpr int my_divide(int num, int denom){
    if(denom == 0){
        // throw std::runtime_error("Denominator cannot be 0");
        // return 9;
    }

    return num/denom;
}

int main() {
    int my_array[my_function()];
    my_array[my_function()-2] = 8;
    constexpr int a = my_divide(8, 4);
    constexpr int b = my_divide(8, 0);
    int c = my_divide(8, 0);
    std::cout << "my_array[my_function] = " << my_array[my_function()-2] << std::endl;
    std::cout << "a=" << a << ", b=" << b << ", c=" << c << std::endl;
    return 0;
}