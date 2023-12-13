# This test demonstrates why it is bad to set default values of arguments to
# mutable objects.
#
# The default values of functions are created only once rather than being
# created at every function call.  Because of this, every time my_func_bad()
# is called with no 2nd argument, it modifies its default value.
#
# In contrast, my_func_good uses an idiom (that is annoying but necessary) to
# create a new default value for the arg2 if it is not passed.
#
# We also note that for immutable objects there is no problem since for both
# functions, t points to an empty tuple created at the start of the program
# but there is no way to modify this tuple.  All we can do is make the local
# variable t point to a different tuple, but at the next function call t goes
# back to pointing to that initial empty tuple that cannot be modified.

def my_func_bad(arg1, arg2=[], t=()):
    print(f" my_func_bad(): arg2={arg2}, t={t}")
    arg2.append(arg1)
    t = (arg1, arg2)

def my_func_good(arg1, arg2=None, t=()):
    if arg2 is None:
        arg2 = []
    print(f"my_func_good(): arg2={arg2}, t={t}")
    t = (arg1, arg2)

l = [1,2,3]
my_func_bad("hello", l)
my_func_bad("hello")
my_func_bad("hello")
my_func_bad("hello")
my_func_bad("hello")
print("=======================================================================")

my_func_good("hello", l)
my_func_good("hello")
my_func_good("hello")
my_func_good("hello")
my_func_good("hello")
