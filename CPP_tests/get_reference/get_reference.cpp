#include <iostream>

class IntWrapper
{
private:
    int _value;
public:
    IntWrapper(int value):_value(value){}
    int &get_int_ref();
    int get_int();
};

int IntWrapper::get_int()
{
    return _value;
}

int& IntWrapper::get_int_ref()
{
    return _value;
}

int main(void)
{
    auto my_int_wrapper = IntWrapper(5);
    /*
     * I don't like that I can do this in C++
     * In Python it's OK because everything is a reference.
     */
    my_int_wrapper.get_int_ref() = 8;

    /*
     * At least this would generate a compilation error

     my_int_wrapper.get_int() = 9;

     *  get_reference.cpp:31:30: error: expression is not assignable
     *        my_int_wrapper.get_int() = 9;
     *        ~~~~~~~~~~~~~~~~~~~~~~~~ ^
     *        1 warning and 1 error generated.
     */
    std::cout << "value of my_int_wrapper : " << my_int_wrapper.get_int() << std::endl;
    return 0;
}
