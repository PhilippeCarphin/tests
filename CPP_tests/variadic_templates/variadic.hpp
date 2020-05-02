#include <iostream>
#include <tbb/tbb.h>
// template<typename Op, typename Arg1>
// void transformLinear(Op op, Arg1 arg1, Arg1 arg1End)
// {
//     for(;arg1 != arg1End; ++arg1)
//     {
//         op(*arg1);
//     }
// }
// 
// // Does nothing, used for variadic pack expension in C++11
// template<typename ... Args>
// void noOp(Args &&...){ }
// 
// template<typename Op, typename Arg1, typename ... Args>
// void transformLinear(Op op, Arg1 arg1, Arg1 arg1End, Args /*&&*/ ... args)
// {
//     for(;arg1 != arg1End; ++arg1, noOp(std::forward<Args>(++args)...))
//     {
//         op(*arg1,*std::forward<Args>(args)...);    
//     }
// }
template<typename Op, typename T>
void transform_phil(Op op, int N, T t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    op(N, t);
}

template<typename Op, typename T, typename ... Ts>
void transform_phil(Op op, int N, T t, Ts ... ts)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // op(N, t, std::forward<Ts>(ts)...);
    op(N, t, ts...);
}

// Does nothing, used for variadic pack expension in C++11
template<typename ... Args>
void noOp(Args &&...){ }

template<typename Op, typename T>
void transform_paul(Op op, int N, T t)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    op(N, t);
    for(int i = 0; i < N; i++){
        op(t[i]);
    }
}

template<typename Op, typename T, typename ... Ts>
void transform_paul(Op op, int N, T t, Ts ... ts)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    // op(N, t, std::forward<Ts>(ts)...);
    // for(;arg1 != arg1End; ++arg1, noOp(std::forward<Args>(++args)...))
    for(int i = 0; i < N; i++, ++t, noOp(std::forward<Ts>(++ts)...)){
        op(N, t, ts...);
    }
}

template<typename Op>
void transform_TBB(Op op, int N){
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    tbb::parallel_for(tbb::blocked_range<int>(0, N), [&](tbb::blocked_range<int> &r){
        for(int i = r.begin(); i != r.end(); i++){
            op(i);
        }
    });
}


template<typename T>
T sum(T t)
{
    return t;
}


template<typename T, typename... Args>
T sum(T first, Args... args)
{
    std::cout << __PRETTY_FUNCTION__ << std::endl;
    return first + sum(args...);
}
