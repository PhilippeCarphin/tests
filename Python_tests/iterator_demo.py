#
# In python we don't like do
#       for i in range(len(l)):
#           pass
# but sometimes we kind of have to if we want to handle adjacent elements:
# for example, if we have
l = "gcc -I dir1 -fPIC -I dir2 ...".split()
# and we want to get all the include directories (assuming for simplicity that
# there are no '-Idir3')

def while_includes(l):
    i = 0
    while i < len(l):
        elem = l[i]
        if elem == "-I":
            yield l[i+1]
            i += 1
        i += 1
print(f"while_includes: {list(while_includes(l))}")

# because it is at step `i` that we know to add l[i+1], this is one way of doing
# it.  It is not impossible to do it with python simple python list iteration
# but it's kind of inelegant
def inelegant_for_includes(l):
    add_next = False
    for elem in l:
        if add_next:
            yield elem
            add_next = False
        elif elem == "-I":
            add_next = True
print(f"inelegant_for_includes: {list(inelegant_for_includes(l))}")

# With better knowledge of iterators we can do it in an elegant way:
# I think this is the best one.  Because it is like doing i+=1 which
# skips the next element.
def for_includes(l):
    words = iter(l)
    for w in words:
        if w == "-I": # '-I /some/directory'
            yield next(words)
        elif w.startswith("-I"): # '-I/some/directory'
            yield w[2:] # Remove the '-I' from the start

print(f"for_includes: {list(for_includes(l))}")

# It's good toknow how to use zip for this kind of thing but ther is an
# inelegant part which is that if element i is "-I" we yield 'y' but then
# on the next iteration, we will have x will have the value of 'y' from
# the previous iteration, but we already delt with that one.  We could
# think of doing 'for x,y in zip(l[::2], l[1::2]) which for
# l = [-I, /some_path, -I, other_path, -L, another_path] would produce the
# right pairs but only works if all arguments are '-X value' and throws
# off everything that comes after if we have '-Xvalue' or '-f' if '-f' takes
# no argument.
def zip_includes(l):
    for x,y in zip(l, l[1:]):
        if x == "-I":
            yield(y)
        elif x.startswith("-I")
l = []
print(f"zip_includes: {list(zip_includes(l))}")

