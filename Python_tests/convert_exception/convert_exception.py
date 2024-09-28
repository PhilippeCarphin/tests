import sys
import yaml

debug = True
#
# Sometimes when an exception occurs, we want to forget about it and raise an
# entirely new exception.
#
# In this example, if the config file for this program is not parsable yaml,
# I don't want to see a traceback that goes 50 functions deep in the yaml
# library.  I want the point where the parsing failed in my code to be the
# start of the traceback.

def main():
    # not_the_solution()
    the_solution()

class MyError(Exception):
    pass

def load_config():
    return open("f")

#
# This gives a double traceback with "Durint the handling of this exception
# this other exception happened".  This is because from Python's point of view
# it just thinks that something went wront in my code that handles the exception
#
def not_the_solution():
    try:
        yaml.safe_load(open("f.yml"))
    except yaml.parser.ParserError as e:
        raise MyError(f"The config file is not valid yaml: {e}")
    except FileNotFoundError:
        raise MyError("The config file must exist")

#
# This one tells python that the exception being raised in the except block
# is normal and we're changing from one exception to another.  I still don't
# care about where in the yaml library this happened.
#
def not_quite_the_solution():
    try:
        yaml.safe_load(open("f.yml"))
    except FileNotFoundError as e:
        raise MyError("The config file must exist") from e
    except yaml.parser.ParserError as e:
        raise MyError(f"The config file is not valid yaml: {e}") from e

#
# This does what I want but the need for that extra variable, that I then need
# to check is really painful.  There must be a better way.
#
def does_what_i_want_but_code_is_meh():
    file_exists = True
    yaml_good = True
    try:
        yaml.safe_load(open("f.yml"))
    except FileNotFoundError as e:
        file_exists = False
    except yaml.parser.ParserError as e:
        yaml_good = False
    if not file_exists:
        raise MyError("The config file must exist")
    if not yaml_good:
        raise MyError(f"The config file is not valid yaml: {e}")
#
# This one does what I want:  Although the first exception is the reason why I
# decided to raise the other one, I only want it to look as if I raised my
# exception normally in this function
# NOTE: This should be used wisely with exceptions that we *expect* like a
# FileNotFoundError when attempting to load a config file.  And we need to
# be careful otherwise we might lie to the user.
#
def the_solution():
    try:
        yaml.safe_load(open("f.yml"))
    except FileNotFoundError as e:
        raise MyError("The config file must exist") from None
    except yaml.parser.ParserError as e:
        raise MyError(f"The config file is not valid yaml: {e}") from None

if __name__ == "__main__":
    # I like this method because when my whole program is in this try-except
    # block, I can cleanly stop the program from any point with an error
    # message.  As the developer, I can still set 'debug' to True and get a
    # traceback to tell me where that message comes from and see the call
    # stack that led to it.
    if debug:
        main()
    else:
        try:
            main()
        except MyError as e:
            print(f"{sys.argv[0]}: \033[1;31mERROR\033[0m: {e}")
            sys.exit(1)
