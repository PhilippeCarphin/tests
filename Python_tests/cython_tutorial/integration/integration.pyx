
from math import sin

cdef f(double x) except *:
    return sin(x**2)

def integrate_f(a, b, N):
    s = 0
    dx = (b-a)/N
    for i in range(N):
        s += f(a+i*dx) * dx
    return s
