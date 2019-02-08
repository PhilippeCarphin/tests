#include <iostream>
// https://stackoverflow.com/a/1134467

struct MyStream
{
    template <typename T>
    MyStream& operator<<(const T& x)
        {
            std::cout << x;

            return *this;

        }


    // function that takes a custom stream, and returns it
    typedef MyStream& (*MyStreamManipulator)(MyStream&);

    // take in a function with the custom signature
    MyStream& operator<<(MyStreamManipulator manip)
        {
            // call the function, and return it's value
            return manip(*this);

        }

    // define the custom endl for this stream.
    // note how it matches the `MyStreamManipulator`
    // function signature
    static MyStream& endl(MyStream& stream)
        {
            // print a new line
            std::cout << std::endl;

            // do other stuff with the stream
            // std::cout, for example, will flush the stream
            stream << "Called MyStream::endl!" << std::endl;

            return stream;

        }

    // this is the type of std::cout
    typedef std::basic_ostream<char, std::char_traits<char> > CoutType;

    // this is the function signature of std::endl
    typedef CoutType& (*StandardEndLine)(CoutType&);

    // define an operator<< to take in std::endl
    MyStream& operator<<(StandardEndLine manip)
        {
            // call the function, but we cannot return it's value
            manip(std::cout);

            return *this;

        }

};

int main(void)
{
    MyStream stream;

    stream << 10 << " faces.";
    stream << MyStream::endl;
    stream << std::endl;

    return 0;

}
