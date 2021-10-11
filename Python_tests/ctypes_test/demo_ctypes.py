
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

# We now have a function that we can call!
home = getenv(b'HOME')
oopsie = getenv('HOME')
print(f'home = {home}')
print(f'oopsie = {oopsie}')

# 2.2 ##########################################################################
# We need to tell this encapsulator what the functions signature is
getenv.restype = ctypes.c_char_p
getenv.argtypes = [ctypes.c_char_p]

# c_char_p represents a byte array, we have to give the function a bytes object
home = getenv(b'HOME')
# The returned type is a bytes object as well
print(f'type(home) = {type(home)}')
print(home)

# 2.3 ##########################################################################
# Once you have access to your C functions they can be further wrapped to
# completely hide that there is a C function under the hood:
def pygetenv(var):
    bytes_in = var if isinstance(var, bytes) else var.encode('ASCII')
    return getenv(bytes_in).decode('ASCII')

pyhome = pygetenv('HOME')
print(pyhome)

# Demo ends here, the rest is fiddling around with types. ######################
quit()



# The default return type will be c_int in which case, our return value will
# lose 32 of its 64 bits on a machine where the sizeof(int) = 32 and
# sizeof(char*) = 64
getenv.restype = ctypes.c_uint
res32 = getenv(b'HOME')
getenv.restype = ctypes.c_longlong
res64 = getenv(b'HOME')

print(f'{" "*32}res32 = {res32:032b}')
print(f'res64 = {res64:064b}')
print(f'res32 = {res32:064b}')


# The 64 bit int can be turned into a ctypes.c_char_p and read as a string
res64_char_p = ctypes.c_char_p(res64)
print(f'res64_char_p.value = {res64_char_p.value}')
