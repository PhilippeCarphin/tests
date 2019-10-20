#include <iostream>

// #define USE_DYNAMIC_ALLOCATION
int &get_int_ref()
{
#ifdef USE_DYNAMIC_ALLOCATION
    int * c = new int;
    *c = 5;
    return *c;
#else
    int a = 8;
    return a;
#endif
}

int other_function(){
    int b = 7;

    return 9;
}

int main() {

    int &int_ref = get_int_ref();
    int ref_copy = int_ref;
    printf("printf: Value of int_ref:%d\n",int_ref);
    std::cout << "std::cout : Value of int_ref : " << int_ref << std::endl;
    printf("printf: Value of int_ref:%d\n",int_ref);
    int ref_later_copy = int_ref;
    printf("printf: Value of ref_copy:%d\n",ref_copy);
    std::cout << "std::cout : Value of ref_later_copy : " << ref_later_copy << std::endl;
    printf("printf: Value of ref_later_copy:%d\n",ref_later_copy);
    other_function();
    int ref_later_later_copy = int_ref;
    printf("printf: Value of ref_later_later_copy:%d\n",ref_later_later_copy);

    return 0;
}
