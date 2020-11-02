
import ctypes
import os

libc_name = "libc.so.6"
if os.uname().sysname == 'Darwin':
    libc_name = "libc.dylib"

libc = ctypes.cdll.LoadLibrary(libc_name)

getenv = libc.getenv

#
# Failure to set restype to c_longlong discards information
#
getenv.restype = ctypes.c_longlong

res64 = getenv('HOME'.encode('ASCII'))

print(hex(res64))

string = ctypes.c_char_p(res64)

print(string.value.decode('ASCII'))


#
# The default return type will be c_int in which case, our return value will
# lose 32 of its 64 bits on a machine where the sizeof(int) = 32 and
# sizeof(char*) = 64
#
getenv.restype = ctypes.c_uint
res32 = getenv('HOME'.encode('ASCII'))

print(f'{" "*32}{res32 = :032b}')
print(f'{res64 = :064b}')
print(f'{res32 = :064b}')



