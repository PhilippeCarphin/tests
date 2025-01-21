
cdef extern from "math.h":
    double sin(double)

cdef f(double x):
    return sin(x**2)

def integrate_f(double a, double b, int N):
    cdef double s
    cdef double dx
    cdef int i
    s = 0
    dx = (b-a)/N
    for i in range(N):
        s += f(a + i*dx) * dx
    return s
