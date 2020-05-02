#include <iostream>
#include "variadic.hpp"

int main(void)
{
    int a[] = {1,2,3,4};
    int b[] = {5,6,7,8};
    int c[] = {9,10,11,12};
    int N = 4;

    std::cout << std::endl << "========= transform_phil ============" << std::endl;
    auto f = [](int N, int *a, int *b, int *c){
        for(int i = 0; i < N; i++){
            c[i] = a[i] + b[i];
        }
    };

    transform_phil(f, 4, a, b, c);

    for(int i = 0; i < N; i++){
        std::cout << c[i] << " ";
    }
    int d[] = {0,0,0,0};
    auto g = [](int N, int *a, int *b, int *c, int *d){
        for(int i = 0; i < N; i++){
            d[i] = a[i] + b[i] + c[i];
        }
    };

    transform_phil(g, N, a, b, c, d);
    for(int i = 0; i < N; i++){
        if(d[i] != a[i] + b[i] + c[i]){
            std::cout << "Invalid value for d[" << i << "]!!!" << std::endl;
            return -1;
        }
    }
    std::cout << "Success calling g()" << g << std::endl;

    std::cout << std::endl << "======= transform_paul ==============" << std::endl;
    for(int i = 0; i < N; i++){c[i] = 0; d[i] = 0;}
    auto h = [](int N, int *a, int *b, int *c, int *d){
        *c = *a + *b;
        *d = *a + *b + *c;
    };
    transform_paul(h, N, a, b, c, d);
    for(int i = 0; i < N; i++){
        if(c[i] != a[i] + b[i]){
            std::cout << "Invalid value for c[" << i << "]!!!" << std::endl;
            return -1;
        }
        if(d[i] != a[i] + b[i] + c[i]){
            std::cout << "Invalid value for d[" << i << "]!!!" << std::endl;
            return -1;
        }
    }
    std::cout << "Success with transform_paul" << std::endl;

    std::cout << "sum(1,2,3,4,5) : " << sum(1,2,3,4,5) << std::endl;
    return 0;
}