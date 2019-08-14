#include <iostream>
#include <string>

extern "C" void f_ezsetval_(const char *, float *f);
extern "C" int c_ezsetval(const char *s, float f);
extern "C" int c_ezsetval2(const char *s, float *f);

extern "C" int c_to_wrap(float *f);
extern "C" int c_to_wrap_good(float f);
inline static void wrapper_function(float f) {
    // Uncommenting this line causes
    // C       :    c_to_wrap() 0.000000 (0x7ffeef4a034c) 
    // std::cout << " C++     :    " << __FUNCTION__ << "() " << f << std::endl;
    c_to_wrap(&f);
}
inline static void wrapper_function_good(float f) {
    std::cout << " C++     :    " << __PRETTY_FUNCTION__ << " " << f << std::endl;
    c_to_wrap_good(f);
}

int main(void)
{
   std::string s = "The constant pi";
    float f = 3.1415;
    const char *c_str = s.c_str();

    // calling f_ezsetfal_() directly from this file causes a segfault
    // f_ezsetval_(c_str, &f);
    // c_ezsetval(c_str, f);
    // c_ezsetval2(c_str, &f);
    // c_ezsetval2()

    wrapper_function(f);
    wrapper_function_good(f);
    // wrapper_function(s,f);
    c_to_wrap(&f);
}
