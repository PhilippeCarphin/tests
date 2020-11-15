
import ctypes
import os

libc_name = "libc.so.6"
if os.uname().sysname == 'Darwin':
    libc_name = "libc.dylib"

libc = ctypes.cdll.LoadLibrary(libc_name)

# This line looks for a function called getenv.
getenv = libc.getenv
# The result is a _FuncPtr object that encapsulates the C function
print(f'getenv = {getenv}')

# We need to tell this encapsulator what the functions signature is
getenv.restype = ctypes.c_char_p
getenv.argtypes = [ctypes.c_char_p]


# c_char_p represents a byte array, we have to give the function a bytes object
home = getenv(b'HOME')
# The returned type is a bytes object as well
print(f'type(home) = {type(home)}')
print(home)

# Once you have access to your C functions they can be further wrapped to
# completely hide that there is a C function under the hood:
def pygetenv(var):
    bytes_in = var if isinstance(var, bytes) else var.encode('ASCII')
    return getenv(bytes_in).decode('ASCII')

pyhome = pygetenv('HOME')
print(pyhome)

# Demo ends here, the rest is fiddling around with types.
quit()


#
# The default return type will be c_int in which case, our return value will
# lose 32 of its 64 bits on a machine where the sizeof(int) = 32 and
# sizeof(char*) = 64
#
getenv.restype = ctypes.c_uint
res32 = getenv(b'HOME')
getenv.restype = ctypes.c_longlong
res64 = getenv(b'HOME')

print(f'{" "*32}res32 = {res32:032b}')
print(f'res64 = {res64:064b}')
print(f'res32 = {res32:064b}')

#
# The 64 bit int can be turned into a ctypes.c_char_p and read as a string
#
res64_char_p = ctypes.c_char_p(res64)
print(f'res64_char_p.value = {res64_char_p.value}')
