#include <stdarg.h>
#include <stdlib.h>

#define fool_optimizer(...) _variadic(NULL, __VA_ARGS__)
void _variadic(...){
    va_list va_args;
}
int main(void){
    fool_optimizer("bing", 0, "dingdong");
}

