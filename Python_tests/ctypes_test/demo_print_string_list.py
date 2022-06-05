import ctypes

libprintlist = ctypes.cdll.LoadLibrary("libprintlist.so")

print_string_list = libprintlist.print_string_list
print_string_list.argtypes = [ctypes.c_int, ctypes.POINTER(ctypes.c_char_p)]
print_string_list.restype = ctypes.c_int

def list_of_str_to_char_star_star(l):
    """ Create a python object representing char** pointing
    to an array of len(l) char* from a list of python bytes
    objects.
    """
    return (ctypes.c_char_p * len(l))(*l)

def py_print_string_list(bl):
    return print_string_list(len(bl), list_of_str_to_char_star_star(bl))

def pypy_print_string_list(l, encoding='ASCII'):
    bl = [e.encode('ASCII') for e in l]
    py_print_string_list(bl)

l = ['hello', 'world', 'asdf']
bl = [e.encode('ASCII') for e in l]
py_print_string_list(bl)
pypy_print_string_list(l)
