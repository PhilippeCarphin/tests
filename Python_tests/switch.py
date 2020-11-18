
def print_number(n):
    return {
        1: lambda : print("One"),
        2: lambda : print("Two"),
        3: lambda : print("Three"),
        4: lambda : print("Four"),
    }[n]()

print_number(3)
print_number(1)
def do_one():
    print("Running function 1")
def do_two():
    print("Running function 2")
def do_three():
    print("Running function 3")
def do_four():
    print("Running function 4")

# I kind of like this one where we don't have
# to name the map, but it kind of bugs me that
# this dictionnary has to get remade everytime
# we call the function.  It's too bad because
# I really think this piece of code looks good
# and expressive.  We see that we're mapping
# n to one of these functions and calling it.
def string_switch(n):
    return {
        "one"  : do_one,
        "two"  : do_two,
        "three": do_three,
        "four" : do_four
    }[n]()

# The thing that we switch on can be
# any hashable type (so that it can
# be used as the key of a dictionnary)
string_switch("one")
string_switch("three")

string_switch_map = {
    "one"  : do_one,
    "two"  : do_two,
    "three": do_three,
    "four" : do_four
}
def string_switch(n):
    return string_switch_map[n]()

# It makes sense that a switch is a map so we
# can make switches this way.  The closest we
# can get to a C-style switch is to define our
# functions as lambdas inside the dictionnary
# or by using an if-elif-elif structure.

# The if-elif-elif method runs the risk of being
# corrupted by changing some of the conditions
# and making it no-longer a switch.

# It would be cool if python had a
# switch(n):
#     case "one":
#         print("doing one")
#     case "two":
#         print("doing two")
#     case "three":
#         print("doing three")
# with or without fallthrough
# but I think the map is best way to express an
# association.  And the problem with the switch
# statement is that writing the code in with the
# switch makes it less readable and a proper switch
# should just have case "something" : return function_call()
# and all cases delegate to the properly named
# function.  Having to do switches with dictionnaries
# enforces this naturally, along with the limitations
# of lambdas which make it harder to define functions
# inside the dictionnaries and thus getting back
# to a less readable switch.  Because lambdas must be
# expressions and cannot have assignment, this
# limits how unreadable you can make your switch by
# putting code inside it.

# But you might as well use the map directly:
# string_switch_map["one"]()
# string_switch_map["three"]()

# I don't like this one as much because the code
# isn't making it as obvious that this is a map
# I have to verify that the elif conditions are
# all comparing n to a value and nothing else.
# But nothing stops me from changing some of the
# conditions, maybe add a little something and now
# it breaks the "map" nature of the logic.
global_var = 8
def string_elif(n):
    if n == "one":
        print("Running function 1")
    elif n == "two":
        print("Running function 2")
    elif n == "three" and global_var % 2 == 0:
        print("Running function 3")
    elif n == "four":
        print("Running function 4")

string_elif("two")
string_elif("three")
