import inspect

class PySpookiImplementationError(Exception):
    pass

class PySpookiArgumentError(Exception):
    pass

def make_spooki_command(funcname, argnames, defaults, kwargs):
    """Create a spooki command from a function call.

    This function will replace the decorated function that specifies the plugin
    interface.

    ARGUMENTS

    funcname : Name of the decorated function.  This name determines the spooki plugin.

    argnames : Names of the arguments

    defaults : Specifies the argument types and default values.
           None: Specifies that the argument is mandatory
           False: Specifies that the argument is a flag
           Otherwise : Gives the default value of the argument

    kwargs   : The keyword arguments from the function call.

    EXCEPTIONS

    PySpookiArgumentError :
            arg has no value and default is None
            arg is a flag but it's value is not True or False
            arg has been given None value

    NOTES

    Note : I can make them not appear in the string sent to the C++ part, but I
    don't think it's worth it to do.

    """
    def is_flag(arg):
        return defaults[arg] is False
    def is_specified(arg):
        return arg in kwargs
    def is_mandatory(arg):
        return defaults[arg] is None
    words = [funcname]
    for arg in argnames:

        if is_specified(arg):
            argvalue = kwargs[arg]

            if is_flag(arg):
                if argvalue not in [True, False]:
                    raise PySpookiArgumentError("Flag argument {} can only be True or False".format(arg))
                if argvalue is True:
                    words.append("--{}".format(arg))

            else:
                if kwargs[arg] is None:
                    raise PySpookiArgumentError("Spooki functions cannot have None for arguments")
                words.append("--{} {}".format(arg, kwargs[arg]))
        else:
            if is_mandatory(arg):
                raise PySpookiArgumentError("Argument {} is required for".format(arg, funcname))
            else:
                words.append("--{} {}".format(arg, defaults[arg]))

    return ' '.join(words)

def make_spooki_function(func):
    """Create a spooki function from a specification.

    ARGUMENTS

    func: A function that specifies an interface for a spooki plugin

    RETURNS

    new_func: A keyword argument function that construcst a spooki command and sends it to spooki

    """
    funcname = func.__name__
    argspec = inspect.getargspec(func)
    argnames = argspec[0]
    argdefaults = argspec[3]
    defaults = dict(zip(argnames, argdefaults))
    if len(argdefaults) != len(argnames):
        raise PySpookiImplementationError("Spooki function {} must have default values for all arguments")
    if True in argdefaults:
        raise PySpookiImplementationError("Spooki function {} arguments cannot have a default value of True")

    def new_func(**kwargs):
        spooky_cmd = make_spooki_command(funcname, argnames, defaults, kwargs)
        print("libmeteo_information(\"[{}]\")".format(spooky_cmd))
    return new_func

@make_spooki_function
def decorated_arg_function(humeur=None, couleur='piss-bucket', francois_est_hot=False):
    """EXAMPLE SPECIFICATION : A function that doesn't do anything.

    It is decorated to make a function that checks the argumensts, builds a
    string and makes a call to the spooki plugin by the same name.

    humeur is a mandatory argument, an exception will be raised if a call is
    made without it.

    couleur has a default value, it doesn't need to be specified.

    phil_est_hot is a flag if it is set to true then the flag will be appended
    to the command

    """
    pass

@make_spooki_function
def windchill(temperature="cold", pressure=130, some_flag=False):
    pass


if __name__ == "__main__":
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(humeur='piss-bucket', couleur='rouge', francoisphil_est_hot=True)
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(humeur='Joyeux', phil_est_hot=True)
    print("CALLING DECORATED FUNCTION")
    decorated_arg_function(couleur='rouge', humeur='piss-bucket', francois_est_hot=True)
    windchill()
    windchill(some_flag=True)
