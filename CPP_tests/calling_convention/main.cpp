#include <iostream>

extern "C" int to_wrap(char c, float *f);

extern "C" int to_wrap_good(char c, float f);

inline static void wrapper_function(char c, float f)
{
    to_wrap(c, &f);
}

void wrapper_function_good(char c, float f)
{
    to_wrap_good(c, f);
}

int main(void)
{
    char c = 'A';
    float f = 3.1415;

    wrapper_function(c,f);
    wrapper_function_good(c,f);
}
