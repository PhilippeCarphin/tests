#include <iostream>
#include "variadic.hpp"

int main(void)
{
    constexpr int N = 4;
    int a[N] = {1,2,3,4};
    int b[N] = {5,6,7,8};
    int c[N] = {0,0,0,0};
    int d[N] = {0,0,0,0};
    auto reset = [&](){for(int i = 0; i < N; i++){c[i] = 0; d[i] = 0;}};
    auto check = [&](){
        for(int i = 0; i < N; i++){
            if(c[i] != a[i] + b[i]){
                std::cout << "Invalid value for c[" << i << "]!!!" << std::endl;
                exit(-1);
            }
            if(d[i] != a[i] + b[i] + c[i]){
                std::cout << "Invalid value for d[" << i << "]!!!" << std::endl;
                exit(-1);
            }
        }
    };

    std::cout << "=========== variadic sum =============" << std::endl;
    std::cout << "sum(1,2,3,4,5) : " << sum(1,2,3,4,5) << std::endl;
    std::cout << std::endl << "========= transform_phil ============" << std::endl;
    reset();
    auto f = [](int N, int *a, int *b, int *c, int *d){
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
            d[i] = a[i] + b[i] + c[i];
        }
    };
    transform_phil(f, N, a, b, c, d);
    check();
    std::cout << "Success with transform_phil" << std::endl;

    std::cout << std::endl << "======= transform_paul ==============" << std::endl;
    reset();
    auto h = [](int N, int *a, int *b, int *c, int *d){
        *c = *a + *b;
        *d = *a + *b + *c;
    };
    transform_paul(h, N, a, b, c, d);
    check();
    std::cout << "Success with transform_paul" << std::endl;

    return 0;
}