import timeit
import numpy as np
import numba as nb


@nb.jit(nopython=True)
def sum2d_numba(arr):
    M, N = arr.shape
    result = 0.0
    for i in range(M):
        for j in range(N):
            result += arr[i,j]
    return result


def sum2d(arr):
    M, N = arr.shape
    result = 0.0
    for i in range(M):
        for j in range(N):
            result += arr[i,j]
    return result



def compare(n):
    arr = np.random.ranf((n,n))
    # print(arr)
    start = timeit.default_timer()
    res = sum2d_numba(arr)
    end = timeit.default_timer()
    time_numba = end - start
    print(f"Result numba              = {res}, time = {time_numba}")

    start = timeit.default_timer()
    res = sum2d(arr)
    end = timeit.default_timer()
    time_normal = end - start
    print(f"Result numba              = {res}, time = {time_normal}")
    print("======================================================\n")

# compare(10)
compare(100)
compare(1000)
compare(2000)
compare(4000)


