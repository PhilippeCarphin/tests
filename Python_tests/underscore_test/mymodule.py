#!/usr/bin/env python3

class MyClass:
    def __init__(self):
        pass

    def __leading_dunder_method(self):
        print("MyClass::__leading_dunder_method (self = {})".format(self))


def __kinda_dunder_func():
    print("__kinda_dunder_func")


def _kinda_private_func():
    print("_kinda_private_func()")


def public_function():
    print("public_function()")


def __dunder_func__():
    print("__dunder_func__")
