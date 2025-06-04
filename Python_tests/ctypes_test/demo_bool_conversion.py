#!/usr/bin/env -S python3 -u

import sys
import ctypes

"""
This test demonstrates that we can pass an argument of type bool to a ctypes
wrapper declared to take arguments of type ctypes.c_int and True gets converted
to 1 and False gets converted to 0 by ctypes before being passed to the underlying
C function
"""

lib = ctypes.cdll.LoadLibrary("libtest.so")

_not = lib['not']
_not.argtypes = [ctypes.c_int]
_not.restype = ctypes.c_int

print(f"Value of _not(True): {bool(_not(True))}", file=sys.stderr)
print(f"Value of _not(False): {bool(_not(False))}", file=sys.stderr)
