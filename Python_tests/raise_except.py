import sys


def function_i_ve_never_heard_of(v):
    a = v['dateo']
def other_function_i_ve_never_heard_of(v):
    a = v['dateo']

def library_function(u):
    function_i_ve_never_heard_of(u)

def library_other_function(u):
    other_function_i_ve_never_heard_of(u)



def low_level_function(u):
    if len(sys.argv) <= 1:
        # Takes a dictionary with key 'dateo'
        library_function(u)
    else:
        library_other_function(u)

def medium_level_function(t):
    low_level_function(t)

def high_level_function(s):
    medium_level_function(s)

class MyThing:
    def __init__(self, **kwargs):
        self.levels = kwargs['levels']
        self.dateo = kwargs['dateo']

if __name__ == "__main__":
    my_thing_dict = {
        "levels": [ 0, 1025, 2050, 3100],
        "dateo": 20201206,
    }
    # We have started a project and we were mostly working
    # with a dictionary with a couple of keys
    # this is cool because it corresponded too the kwargs
    # of some library functions.
    # but now we want to create a proper class...
    my_thing_class = MyThing(**my_thing_dict)
    high_level_function(my_thing_dict)


