""" This test shows the subtleties of the difference between python variables
and python objects.

As someone put it: an "a = b" could be thought of as binding 'a' to the same
object as 'b'.

As part of this subject, we also demonstrate the copy and deepcopy modules
"""

from copy import copy, deepcopy
class Phil:
    def __init__(self, val, d=None):
        self.val = val
        self.d = d
    def __str__(self):
        return str(self.val) + ' d --> ' + str(self.d)

print("======== Initial objects ===========")

a = Phil(4)
b = Phil(5)

print(a)
print(b)

print("========= Assignment-like statement =======")
""" This makes a 'point to' the same object as b """
a = b
a.val = 99

print(a)
print(b)

print("====copy===")

a = Phil(10)
b = Phil(99)

print(a)
print(b)

print("==")
b = a
a.val =88

print(a)
print(b)


print("===========")

a = 4
b = 5

b = a
a = 99

print(a)
print(b)

print("============== copy vs deepcopy ================")
dictionnaire = {'phil':50, 'godefroy':60}
a = Phil(88, dictionnaire)
d = deepcopy(a)
b = copy(a)
b.d['marcus'] = 42
c = a
c.val = 67

for v in [a,b,c,d]:
    print(v)

