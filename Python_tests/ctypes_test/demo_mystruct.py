import ctypes
import sys

"""
This test demonstrates that `ctypes.byref(None)` is invalid and that passing
None as the argument for a _FuncPtr object that expects a ctypes.POINTER(X)
where X is a ctypes.Structure derived class results in the C function receiving
NULL for that argument.

When we have a C function taking a pointer to a struct and this pointer can be
NULL, this corresponds well with with a Python function that takes an optional
argument.

In that case, we would like to pass `ctypes.byref(optional_arg)` to the
underlying C function but if we define the function as

    def func(optional_arg=None):

that doesn't work and we need to either pass `ctypes.byref(optional_arg)` or
`None` which means we need an extra check in the wrapping C function.
"""

#
# Setup the context:
# - A C library with a function that takes a pointer to a struct as an argument
# - A class representing the struct
#
_greet_person = ctypes.cdll.LoadLibrary("libtest.so").greet_person
_greet_person.restype = None

class Person(ctypes.Structure):
    _fields_ = [
        ("name", ctypes.c_char_p),
        ("age", ctypes.c_int),
        ("height", ctypes.c_float)
    ]
_greet_person.argtypes = (ctypes.POINTER(Person),)

phil = Person()
phil.name = b'Philippe Carphin'
phil.age = 40
phil.height = 182.0

#
# This is what we would like to do:  just pass ctypes.byref(p) and hope that
# when the argument when we pass whatever `ctypes.byref(None)` is, then ctypes
# will pass NULL to the C function
#
def greet_person_wrong(p=None):
    _greet_person(p)

print("===================== wrong =============================", file=sys.stderr)
greet_person_wrong(phil)
try:
    greet_person_wrong()
except TypeError as e:
    print(f"{type(e).__name__}: {e}", file=sys.stderr)

#
# But because `None` is not a valid argument to `ctypes.byref`, we 

def greet_person_correct(p=None):
    p_ptr = ctypes.byref(p) if p else None
    _greet_person(p_ptr)


print("===================== correct =============================", file=sys.stderr)
greet_person_correct(phil)
greet_person_correct()

