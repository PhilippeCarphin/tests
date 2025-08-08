import ctypes
import numpy
import copy

lib = ctypes.cdll.LoadLibrary("libtest.so")

array_type = numpy.ctypeslib.ndpointer(dtype=numpy.float32)
array_type = ctypes.POINTER(ctypes.c_float)
array_type = ctypes.c_int64
average = lib.average
average.argtypes = (array_type,ctypes.c_int, ctypes.c_int, ctypes.POINTER(ctypes.c_float))
average.restype = ctypes.c_int

result = ctypes.c_float(0)
arr = numpy.empty((8,8), dtype=numpy.float32)

arr[:,:] = 8.123
arr[::2,::2] = -8.123
# average(None, 8,8,ctypes.byref(result))
average(arr.ctypes.data, 8, 8, ctypes.byref(result))
print(result.value)
