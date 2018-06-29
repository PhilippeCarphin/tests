#include <iostream>
#include "myclass.h"

int MyClass::myClassVar = 8;

void MyClass::show_my_var()
{
    std::cout << __func__ << "() : MyVar = " << myClassVar << std::endl;
}
