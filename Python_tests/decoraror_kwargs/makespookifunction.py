import inspect
from spooki import IMO


class PySpookiImplementationError(Exception):
    pass


class PySpookiArgumentError(Exception):
    pass


def make_spooki_command(funcname, argspec, kwargs, annotations=None):
    """Create a spooki command from a function call.

    This function will replace the decorated function that specifies the plugin
    interface.

    ARGUMENTS

    funcname : Name of the decorated function. This name determines the spooki
    plugin.

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

    def is_flag(argname):
        return argspec[argname] is False or (argname in annotations and type(annotations[argname]) is bool)

    words = [funcname]

    params = set(argspec)                  # Parameters are from the function definition
    args = set(kwargs)                     # Arguments come from the function call
    invalid = args - params                # Arguments that don't correspond to something in the function definition
    specified = params.intersection(args)  # Valid arguments
    unspecified = params - args            # Parameters for which an argument was not supplied

    if invalid:
        raise PySpookiArgumentError("Arguments {} are not part of the specification".format(list(invalid)))

    for arg in specified:
        argval = kwargs[arg]
        if arg in annotations and type(argval) is not annotations[arg]:
            raise TypeError("Argument {} must be of type {}, got {} of type {} instead"
                            .format(arg, annotations[arg], argval, type(argval)))
        del kwargs[arg]
        if is_flag(arg):
            if argval not in [True, False]:
                raise PySpookiArgumentError("Flag argument {} can only be True or False".format(arg))
            if argval is True:
                words.append("--{}".format(arg))
        else:
            if argval is None:
                raise PySpookiArgumentError("Spooki functions cannot have None for arguments")
            else:
                words.append("--{} {}".format(arg, argval))

    for arg in unspecified:
        if argspec[arg] is None:
            raise PySpookiArgumentError("Argument {} is required for".format(arg, funcname))
        elif not is_flag(arg):
            words.append("--{} {}".format(arg, argspec[arg]))

    return ' '.join(words)


def make_spooki_function(func):
    """Create a spooki function from a specification.

    ARGUMENTS

    func: A function that specifies an interface for a spooki plugin

    RETURNS

    new_func: A keyword argument function that construcst a spooki command and
              sends it to spooki.

    """
    plugin_name = func.__name__
    argspec = inspect.getfullargspec(func)
    argnames = argspec.args
    argdefaults = argspec.defaults
    annotations = argspec.annotations
    if len(argdefaults) != len(argnames):
        raise PySpookiImplementationError("Spooki function {} must have default values for all arguments")
    if True in argdefaults:
        raise PySpookiImplementationError("Spooki function {} arguments cannot have a default value of True")

    argspec = dict(zip(argnames, argdefaults))

    def new_func(**kwargs) -> IMO:
        spooky_cmd = make_spooki_command(plugin_name, argspec, kwargs, annotations)
        print("libmeteo_information(\"[{}]\")".format(spooky_cmd))
        return IMO()  # return libmeteo_information(...)

    new_func.__doc__ = func.__doc__
    new_func.__name__ = func.__name__
    return new_func
