import os

print("PATH=" + os.environ['PATH'])
try:
    print("PHIL=" + os.environ['PHIL'])
except KeyError:
    print("PHIL is not in environment")

try:
    print("PHIL_ENV=" + os.environ['PHIL_ENV'])
except KeyError:
    print("PHIL_ENV is not in environment")
print("This is sorts.py")

