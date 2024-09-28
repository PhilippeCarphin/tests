import iteration
import pathlib
import sys

d = pathlib.Path("/fs/site5/eccc/prod/ops/suites/gdps_20220621/g1/gridpt.usr/prog/pres")
gen = d.glob("2024*")
iteration.iterate(gen)

#
# Use a generator that yields a class that I made so that I can make sure I got
# the refcounts right.  The above code with d.glob as my iterable yields items
# but it holds a bunch of references to these items.
#
class Phil:
    def __init__(self, name):
        self.name= name
    def __str__(self):
        return f"Phil({self.name})"
    def __del__(self):
        print(f"Destructor of Phil({self.name})")

def gen0(n):
    l = []
    for i in range(n):
        p = Phil(i)
        # While the C code is running, the local variable p is another
        # reference, and the item in the C code is another reference which
        # makes 2
        yield p
        # At the end of the iteration in the C code, we decref once for item,
        # then when the next iteration of this loop begins, we assign something
        # new to p which decrefs the previous Phil instance.
def gen1(n):
    l = []
    for i in range(n):
        p = Phil(i)
        l.append(p)
        # While the C code is running, the list holds 1 reference,
        # the local variable p is another reference, and the
        # item in the C code is another reference which makes 3
        yield p
def gen2(n):
    for i in range(n):
        # Here in the C code, item is the only reference to 
        yield Phil(i)
print("========= gen0 ==========")
iteration.iterate(gen0(4))
print("========= gen1 ==========")
iteration.iterate(gen1(4))
print("========= gen2 ==========")
iteration.iterate(gen2(4))
print("========= ints ==========")
# Something pretty interesting happens here, since integers are kind of singletons
# in python.  For 1, there is an integer object 1 and every variable that gets
# 1 assigned to it adds another reference to that object.  So we will see some
# integers with a pretty high refcount.
iteration.iterate(range(5))


# print(sys.getcounts())
# print(sys.gettotalrefcount())
