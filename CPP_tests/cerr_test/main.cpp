#include <iostream>
#include <sstream>

class CLogger : public std::ostream {
private:
    class CLogBuf : public std::stringbuf {
    private:
        // or whatever you need for your application
        std::string m_marker;
    public:
        ~CLogBuf() {  pubsync(); }
        int sync() {
            std::cout << m_marker << ": " << str() << "cock" << std::endl;
            str("");
            return std::cout?0:-1;

        }


    };

    

public:
    // Other constructors could specify filename, etc
    // just remember to pass whatever you need to CLogBuf
    CLogger(const std::string& marker) : std::ostream(new CLogBuf(marker)) {}
    ~CLogger() { delete rdbuf(); }

};


int main()
{
    CLogger hi("hello");
    CLogger bye("goodbye");

    CLogger("COCK") << "ALLO";
    CLogger("boner") << "pipi caca";
    hi << "hello, world" << "asdfasdf";
    hi << "Oops, forgot to flush.";
    bye << "goodbye, cruel world";
    bye << "Cough, cough.";


    return 0;
}
