import ctypes

lib = ctypes.cdll.LoadLibrary("./libecho.so")

# void *echo_void_star(unsigned long int x)
_echo_void_star = lib.echo_void_star
_echo_void_star.argtypes = [ctypes.c_ulong]
_echo_void_star.restype = ctypes.c_void_p

# int *echo_int(int x)
_echo_int = lib.echo_int
_echo_int.argtypes = [ctypes.c_int]
_echo_int.restype = ctypes.POINTER(ctypes.c_int)

class MyThing(ctypes.Structure):
    _fields_ = [
        ("int", ctypes.c_int),
        ("void_star", ctypes.c_void_p)
    ]

# struct MyThing *MyThing_New(int integer, void* void_star)
_mything_new = lib.MyThing_New
_mything_new.argtypes = [ctypes.c_int, ctypes.c_void_p]
_mything_new.restype = ctypes.POINTER(MyThing)

print("=================== return void*, non NULL ===================")
x = _echo_void_star(1234)
print(f"Result of _echo_void_star(1234): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
# print(f"contents: {x.contents}") # ERROR: No contents

print("=================== return void*, yes NULL ===================")
x = _echo_void_star(0)
print(f"Result of _echo_void_star(0): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
# print(f"contents: {x.contents}") # ERROR: NoneType has no attribute contents

print("=================== return int*, non NULL ===================")
x = _echo_int(1234)
print(f"Result of _echo_int(1234): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
print(f"contents: {x.contents}")

print("=================== return int*, yes NULL ===================")
x = _echo_int(666)
print(f"Result of _echo_int(0): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
# print(f"contents: {x.contents}") # ERROR: NULL pointer access

print("=================== return ctypes.POINTER(MyThing), non NULL ===================")
x = _mything_new(8, 0xDEADBEEF)
print(f"result of _mything_new(666, _): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
print(f"contents: {x.contents}")
print(f"values: {x.contents.void_star}, {x.contents.int}")

print("=================== return ctypes.POINTER(MyThing), yes NULL ===================")
x = _mything_new(666, 0xDEADBEEF)
print(f"result of _mything_new(666, _): {x}, type: {type(x)}")
print(f"bool(x): {bool(x)}")
# print(f"contents: {x.contents}") # ERROR: NULL pointer access

