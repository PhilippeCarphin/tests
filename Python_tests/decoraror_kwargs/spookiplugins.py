from makespookifunction import make_spooki_function
from spooki import IMO


# noinspection PyUnusedLocal
@make_spooki_function
def decorated_arg_function(humeur=None,
                           couleur=8,
                           bonjour=False) -> IMO:
    """EXAMPLE SPECIFICATION : A function that doesn't do anything.

    It is decorated to make a function that checks the argumensts, builds a
    string and makes a call to the spooki plugin by the same name.

    humeur is a mandatory argument, an exception will be raised if a call is
    made without it.

    couleur has a default value, it doesn't need to be specified.

    bonjour is a flag if it is set to true then the flag will be appended
    to the command

    """
    pass


# noinspection PyUnusedLocal
@make_spooki_function
def windchill(temperature="cold",
              pressure=130,
              some_flag=False) -> IMO:
    """ This docstring will be given over to the new function """
    pass


# noinspection PyUnusedLocal
@make_spooki_function
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
