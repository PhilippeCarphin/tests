import ctypes

"""
This test demonstrates that ctypes "byrefs" things automatically it seems
"""

_quadruple_by_ref = ctypes.cdll.LoadLibrary("libtest.so").quadruple_by_ref
_quadruple_by_ref.argtypes = (ctypes.POINTER(ctypes.c_double),)
_quadruple_by_ref.restype = ctypes.c_int

pi = ctypes.c_double(3.14159)

_quadruple_by_ref(pi)
print(pi)

