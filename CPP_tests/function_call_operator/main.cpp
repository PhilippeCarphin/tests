#include <iostream>
#include <typeinfo>

class MyFunctor
{
public:
    int operator()()
    {
        std::cout << typeid(*this).name() << "::"
                  << __FUNCTION__ << "() called" << std::endl;
        return 0;
    }
};

struct MyStructFunctor
{
    int operator()()
    {
        std::cout << typeid(*this).name() << "::"
                  << __FUNCTION__ << "() called" << std::endl;
        return 0;
    }
};

int main(int argc, char **argv)
{
    MyFunctor mf;
    mf();
    mf.operator()();

    MyStructFunctor msf;
    msf();
    msf.operator()();

    return 0;
}
