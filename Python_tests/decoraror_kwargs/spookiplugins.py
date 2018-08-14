from pyunix import make_unix_function

# noinspection PyUnusedLocal
@make_unix_function
def decorated_arg_function(humeur=None,
                           couleur=8,
                           bonjour=False) -> IMO:
    """EXAMPLE SPECIFICATION : A function that doesn't do anything.

    # TODO The behavior will be that declaring a function to be 
    or simpler than that.
    a factory function that does this:
    make_unix_function(initial_words, arg_spec):


    git_clone('https://github.com/philippecarphin/configurations')
    git_clone('https://github.com/philippecarphin/configurations', target='~/Documents/GitHub/config')


    mv(src='somefile', 'dst=somefile')
    mv(src='somefile', 'dst=somefile')

    {target: NO_DEFAULT, link_name= NO_DEFAULT})

    It is decorated to make a function that checks the argumensts, builds a
    string and makes a call to the spooki plugin by the same name.

    humeur is a mandatory argument, an exception will be raised if a call is
    made without it.

    couleur has a default value, it doesn't need to be specified.

    bonjour is a flag if it is set to true then the flag will be appended
    to the command

    """
    pass

def make_unix_function(initial_words, argspec=[()], kwargspec={}, options_before=True, varargs=false):
    # Validate that argspec is a list of 2-element tuples
    # validate that kwargspec is a dictionary of
    # {
    #     PyUnixKwarg(name=this, other_prop=that, option_prefix='--', with_equal=False, flag=False)
    # }
    # Both argspec and kwargspec will be lists of these. Optio
    # Argspec same 'struct' but an ordered list of them instead of a dictionary of them.

    if options_before:
        def new_func(*args, **kwargs):
            option_words = make_option_words(kwargspec, kwargs) # A list
            arg_words = list(args)
            command_words = initial_words + option_words + arg_words
            subprocess.run(command_words)
    else:
        def new_func(*args, **kwargs):
            option_words = make_option_words(kwargspec, kwargs) # A list
            arg_words = list(args)
            command_words = initial_words + arg_words + option_words
            subprocess.run(command_words)



# noinspection PyUnusedLocal
@make_unix_function
def git(temperature="cold",
              pressure=130,
              some_flag=False) -> IMO:
    """ This docstring will be given over to the new function """
    pass


# noinspection PyUnusedLocal
@make_unix_function
def annotated_func(humidity: int=8,
                   stickyness: str="hello",
                   sweatiness: str=None,
                   sunny: bool=False) -> IMO:
    pass


if __name__ == "__main__":
    # print("CALLING DECORATED FUNCTION")
    decorated_arg_function(humeur='piss-bucket', couleur=8, bonjour=True)
    # print("CALLING DECORATED FUNCTION")
    # decorated_arg_function(humeur='Joyeux', bonjour=True)
    # print("CALLING DECORATED FUNCTION")
    # decorated_arg_function(couleur='rouge', humeur='piss-bucket', bonjour=True)
    windchill()
    windchill(some_flag=True)
    annotated_func(humidity=8, stickyness="9", sweatiness="asdf", sunny=True)
