#!/usr/bin/env python3
#
# This test demonstrates that `sys.exit()` allows all the cleanup to happen
# (it works by raising an exception).  This is different from `os._exit()`
# which is a python wrapper around the exit system call which terminates the
# process.
#

import sys
import os

class CustomError(Exception):
    pass

class MyClass:
    def __init__(self, value):
        self.value = value

    def __del__(self):
        print(f"Deleting instance of MyClass with value '{self.value}'")


def main():
    mc = MyClass("from main()")

    try:
        print("try block")
        sys.exit(1)               # Destructors and finally blocks are run
        # quit(3)                 # Destructors and finally blocks are run
        # os._exit(2)             # No destructors or finally blocks are run
    except CustomError as e:
        print(f"Caught CustomError")
    finally:
        print(f"This is the finally block")

if __name__ == "__main__":
    main()
