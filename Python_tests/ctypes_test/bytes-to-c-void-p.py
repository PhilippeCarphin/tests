import ctypes
import numpy

lib = ctypes.cdll.LoadLibrary("libtest.so")

_give_me_some_bytes = lib.give_me_some_bytes
_give_me_some_bytes.argtypes = (ctypes.c_void_p, ctypes.c_int)
_give_me_some_bytes.restype = ctypes.c_int

x = bytes([32,65,66,67,68,77])

def give_me_some_bytes(b):
    _give_me_some_bytes(b, len(b))

give_me_some_bytes(x)

s = "Hello world"

give_me_some_bytes(s.encode('UTF-8'))

a1 = numpy.random.randint(0,100, 16).astype(numpy.uint32)
print(a1)
_give_me_some_bytes(a1.ctypes.data, 16)
# a2 = numpy.astype(a1, numpy.uint8)
# _give_me_some_bytes(a2.ctypes.data, 16)
