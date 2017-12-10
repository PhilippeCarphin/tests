''' In python, when passing something as an argument, a reference is passed such
that one might make the mistake of modifying the argument in the function.

This shows that there all variables are pointers to objects and that functions
get copies of those pointers.  They can modify the thing that their arguments
point to but they cannot change what the variable passed as an argument points
to.

It then becomes easy to make mistakes with ints if you forget that ints are
objects like anything else.  So the variable a points to an integer object
somewhere whose value is 4, then the function receives a pointer to this object.

But the assignement line makes the local copy of the pointer to 4 change to a
pointer to another object with value 8.  Leaving a pointing to 4.  It's kinda
weird but in a way, it's consitent'''

class WrappedInt:
    def __init__(self, value):
        self.value = value

def modify_wrapped(wrapped_int):
    wrapped_int.value *= 2

def modify(integer):
    integer *= 2
    print("modify(integer) : integer = " + str(integer))

def modify_tuple(tup):
    tup[0] = 3

def change_tuple(tup):
    tup = (8,8)


print("Passing naked integers")
a = 4
print("a = " + str(a))
modify(a)
print("a = " + str(a))

print("Passing int wrapped in a class")
b = WrappedInt(4)
print("b.value = " + str(b.value))
modify_wrapped(b)
print("b.value = " + str(b.value))

t = (3,3)
change_tuple(t)
print("t = " + str(t))

''' This line causes an exception '''
# modify_tuple((4,4))
