import argparse

DESCRIPTION = """ This test demonstrates the use of argparse.Action classes
to perform arbitrary code for a certain argument """

def get_args(*args):
    class SpecialAction(argparse.Action):
        def __init__(self, option_strings, dest, nargs=None, **kwargs):
            print("")
            print(f"SpecialAction::__init__(): kwargs={kwargs}")
            super().__init__(option_strings, dest, **kwargs)
            print(self)
        def __call__(self, parser, namespace, values, option_string=None):
            print("")
            # print(f"SpecialAction::__call__(): parse: {parser}")
            print(f"SpecialAction::__call__(): namespace={namespace}")
            print(f"SpecialAction::__call__(): values={values}")
            print(f"SpecialAction::__call__(): option_string={option_string}")
            setattr(namespace, self.dest, values.split(','))


    p = argparse.ArgumentParser(description=DESCRIPTION)
    p.add_argument("--arg1", "-a", action=SpecialAction)
    p.add_argument("--arg2", nargs='*',      action=SpecialAction)
    print(f"parser: {p}")

    if args:
        return p.parse_args(args)
    else:
        return p.parse_args()

args = get_args(*"--arg1 asdf --arg2 8 --arg2 11".split())
print(f"\nargs={args}")

print("\033[1;32m================================================================================\033[0m")
args = get_args(*"--arg1 asdf".split())
print(f"\nargs={args}")

