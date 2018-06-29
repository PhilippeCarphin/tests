#include <iostream>
#include "myclass.h"

int main(void)
{
    std::cout << "Hello World" << std::endl;
    MyClass::show_my_var();
    MyClass::myClassVar = 3;
    MyClass::show_my_var();

    return 0;
}
