#!/bin/python

class pointer(object):
    def __init__(self, ref=None):
        self.ref = ref
    def __call__(self):
        return self.ref
    def __str__(self):
        return str(id(self))
    def __eq__(self, other):
        return id(self.ref) == id(other.ref)

a = [1,2,3]
b = [4,5,6]


ptr = pointer(a)

ptr2 = pointer(b)

c = ptr

print("c = " + str(c))
print(c == ptr2)
ptr.ref = b
print("c = " + str(c))
print(c == ptr2)
