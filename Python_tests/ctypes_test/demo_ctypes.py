#!/usr/bin/env python3
import ctypes
import os

# 1. Obtain an object for your shared library
# 2. Create wrapper functions for C library functions
#    2.1 C object wrapping a library function(s)
#    2.2 Configure the object according to the function signature(s)
#    2.3 Create a wraper function that takes and returns Python types
# (*) Note: If you have access to the C code being exposed, then
#           adding C functions to help with the python wrapping is
#           always possible

# 1 ############################################################################
libc_name = "libc.so.6"
if os.uname().sysname == 'Darwin':
    libc_name = "libc.dylib"

libc = ctypes.cdll.LoadLibrary(libc_name)

# 2 ############################################################################
# 2.1 ##########################################################################
# This line looks for a function called getenv. (This is done by overloading
# the __getattr__ method.
getenv = libc.getenv

# We now have a function that we can call! We shouldn't call it now though
# but we can:
home = getenv(b'HOME')
print(f'2.1: home = {home}')

# BTW: Passing a str object instead of a bytes object doesn't work
# and we shouldn't even do this.  We should set the restype and argtypes
# attributes and if we do, this would raise a ctypes.ArgumentError.
wrong_arg_result = getenv('HOME')
print(f'2.1: wrong_arg_result = {wrong_arg_result}')

# 2.2 ##########################################################################
# We need to tell this encapsulator what the functions signature is
getenv.restype = ctypes.c_char_p
getenv.argtypes = [ctypes.c_char_p]

# c_char_p represents a NUL terminated byte array which means
# a bytes object in python.
home = getenv(b'HOME')
print(f"2.2: home = {home}")

# Now that argtypes is set, this would raise cytpes.ArgumentError:
# oopsie = getenv('HOME')

# 2.3 ##########################################################################
# Once you have access to your C functions they can be further wrapped to
# completely hide that there is a C function under the hood:
def pygetenv(var):
    bytes_in = var if isinstance(var, bytes) else var.encode('ASCII')
    return getenv(bytes_in).decode('ASCII')

wrapper_home = pygetenv('HOME')
print(f"2.3: wrapper_home = {wrapper_home}")

# Demo ends here, the rest is fiddling around with types. ######################
quit()



# The default return type will be c_int in which case, our return value will
# lose 32 of its 64 bits on a machine where the sizeof(int) = 32 and
# sizeof(char*) = 64
getenv.restype = ctypes.c_uint
res32 = getenv(b'HOME')
getenv.restype = ctypes.c_longlong
res64 = getenv(b'HOME')

print(f'res32 = {res32:064b}')
print(f'res64 = {res64:064b}')

# ctypes.c_longlong was the wrong type but it still contains the address of
# the first char of a c-string.  If we use it to initialize a ctypes.c_char_p,
# then we can interpret it correctly.
res64_char_p = ctypes.c_char_p(res64)
print(f'res64_char_p = {res64_char_p}')
print(f'res64_char_p.value = {res64_char_p.value}')

# Note: In the first part, we correctly set the restype to c_char_p and
# the function returned a bytes object.
