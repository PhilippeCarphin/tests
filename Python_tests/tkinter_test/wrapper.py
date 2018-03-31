import sys

if sys.version_info < (3,0):
    print("python2")
    import tktest2
else:
    print("python3")
    import tktest
