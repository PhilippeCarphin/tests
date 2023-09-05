#include <iostream>

int my_func(void* p){
    std::cerr << __func__ << '(' << p << ')' << std::endl;
    return 0;
}

int my_other_func(uint32_t *p)
{
    std::cerr << __func__ << '(' << p << ')' << std::endl;
    return 0;
}

int main(void)
{
    int int_val = 8;
    char char_val[10];
    my_func(&int_val);
    my_func(char_val);
    my_other_func(&int_val);
}
