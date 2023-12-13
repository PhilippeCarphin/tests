#include <string>

class Person {
    public:
        Person(void);
        void say_hello(void);
};

extern "C" {
int say_hello(const char *person);
int say_hello_f();
}

