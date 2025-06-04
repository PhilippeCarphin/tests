import ctypes

__doc__ = """ This test shows that a ctypes function object declared as returning
a ctypes.c_float, when called, will give us a straight up unwrapped Python float
that does not need to be converted.
"""
lib = ctypes.cdll.LoadLibrary("./libtest.so")

give_me_a_float = lib.give_me_a_float
give_me_a_float.argtypes = (ctypes.c_float,)
give_me_a_float.restype = ctypes.c_float

x = give_me_a_float(8)
print(type(x))
print(x)
