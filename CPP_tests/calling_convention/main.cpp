#include <iostream>
#include <string>

extern "C" void f_ezsetval_(const char *, float *f);
extern "C" int c_ezsetval(const char *s, float f);
extern "C" int c_ezsetval2(const char *s, float *f);

/*
 * What we think the function we are wrapping is.
 * The first one is incorrect and leads to interesting
 * behaviors
 */
extern "C" int c_to_wrap(char *s, float *f);
extern "C" int c_to_wrap_good(char *s, float f);

inline static void wrapper_function(std::string s, float f) {
    c_to_wrap(&s[0], &f);
}
inline static void wrapper_function_cout(std::string s, float f){
    std::cout << " C++     :    " << __FUNCTION__ << "() f = " << f << std::endl;
    c_to_wrap(&s[0], &f);
}
inline static void wrapper_function_good(std::string s, float f) {
    std::cout << " C++     :    " << __FUNCTION__ << "() f = " << f << std::endl;
    c_to_wrap_good(&s[0], f);
}

int main(void)
{
   std::string s = "The constant pi";
    float f = 3.1416;
    const char *c_str = s.c_str();

    /*
     * This shows that under the right circumstances, the
     * wrapped function c_to_wrap() might still be able to
     * see the float.  When compiled with the makefile, one
     * might see the following output:

make test
gfortran -shared -fPIC -L. frmn.f -o libfrmn.so
gcc -shared -Wno-format -fPIC -L. -lfrmn -o librmn.so rmn.c
g++ -o main main.cpp -L. -l rmn -l frmn
./main
C       :    c_to_wrap() 3.141600 (0x7ffe32445de4)
C++     :    void wrapper_function_good(std::__cxx11::string, float) 3.1416
C       :    c_to_wrap_good() 3.141600
C       :    c_to_wrap() 0.000000 (0x7ffe32445e14)

     */
    std::cout << " C++     :    main() calling wrapper_function(s, " << f << ") ..." << std::endl;
    wrapper_function(s,f);
    wrapper_function_good(s,f);
    c_to_wrap(&s[0], &f);
    wrapper_function_cout(s,f);

    /*
     */
    // calling f_ezsetfal_() directly from this file causes a segfault
    // f_ezsetval_(c_str, &f);
    // c_ezsetval(c_str, f);
    // c_ezsetval2(c_str, &f);
    // c_ezsetval2()

}
