from mymodule import *


public_function()
try:
    _kinda_private_func()
except NameError:
    print("NameError raised when calling _kinda_private_func")

try:
    __kinda_dunder_func()
except NameError:
    print("NameError raised when calling __kinda_dunder_func")

try:
    __dunder_func__()
except NameError:
    print("NameError raised when calling __dunder_func__")


my_instance = mymodule.MyClass()

try:
    my_instance.__leading_dunder_method()
except AttributeError as e:
    print("Calling my_instance.__leading_dunder_method() produced an AttributeError")
    my_instance._MyClass__leading_dunder_method()

