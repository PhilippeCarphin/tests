#include <iostream>
#include <sstream>
/*
 * This program defines a new output stream that automatically adds a newline.
 * There are better ways of doing it but this is by far the simplest way of
 * making it work.
 *
 * Note that the destructor is called after the end of the line.  Therefore the
 * destructor for the first pout is called before the next line begins.
 *
 * Apparently there are exceptions to "temporary objects are destroyed 'at the
 * end of the line' idea" but we shouldn't worry about that because our usage of
 * this will not be funky in any way.
 */

class pout // p is for Phil
{

public:

    template<class T>
    pout& operator<<(const T& a)
    {
        acc << a;
        return *this;
    }

    ~pout()
    {
        std::cout << acc.str() << std::endl;
    }

private:

    std::ostringstream acc;
};

class pout2
// class pout2 : public std::ostream
{
public:
    template <class T>
    pout2& operator<<(const T& a)
        {
            std::cout << a;
            return *this;
        }
    ~pout2()
        {
            std::cout << std::endl;
        }
};

int main(int argc, char **argv)
{
    (void) argc;
    (void) argv;

    pout p;
    p << " WORLD";
    pout() << "This is the first line";
    pout() << "I heard it on the grapevine";
    pout2() << "HELLO";
    return 0;
}
