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
 *
 * IMPORTANT NOTE ABOUT std::endl;
 *
 * See stack overflow https://stackoverflow.com/a/1134467 
 *
 * The gist is that std::endl is actually a function and when it is the argument
 * of operator<<, the stream is to call that function and forward the return
 * value.
 *
 * Because it is a function, the template stuff has trouble figuring out what it
 * is so we use this.
 */

class SpookiLogging
{

public:

    template<class T>
    SpookiLogging& operator<<(const T& a)
    {
        acc << a;
        return *this;
    }

    // Defining StandardEndLine to be the type of std::endl
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    SpookiLogging& operator<<(StandardEndLine manip)
    {
        acc << std::endl;
        return *this;
    }

    ~SpookiLogging()
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

    SpookiLogging p;
    p << "HELLO";
    SpookiLogging() << "This is the first line";
    SpookiLogging() << "I heard it on the grapevine" << std::endl << "after endline";
    p << " WORLD";
    return 0;
}
