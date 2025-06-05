import argparse

#
# This test demonstrates the `error` method of `argparse.ArgumentParser`.
# When called, it exits with code 2 (on Linux, Mac, and Windows) which according
# to https://tldp.org/LDP/abs/html/exitcodes.html is used by BASH to signal the
# misuse of a shell builtin.
#
__doc__ = """This is where I put my program description to use as the
`description` kwarg to my arparse parser"""

# Could be os.path.basename(sys.argv[0])
# or os.path.basename(__file__)
# or anything else
PROG_NAME = "name"

def get_args(error):
    p = argparse.ArgumentParser(description=__doc__, prog=PROG_NAME)

    args = p.parse_args()
    if error:
        p.error("This is the error message")

    return args

get_args(True)


