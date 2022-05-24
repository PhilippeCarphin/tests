import argparse
import os
import yaml
"""
This is a more simple version of get_file_config().  The previous one was
modeled after the thing I found on github (github.py) which declares a second
parser because he wants to get values from the config file and use 'parser.set_defaults()'
and he has to do that before calling parser.parse_args().

This makes it so that he needed two ArgumentParser instances.

Because I want to do extra checks like rejecting things from the config file that
are not arguments, I do my own loop.

That means I don't need two parsers and the '-C', '--config' argument can be in
the same parser and I don't have to do parse_known_args and forward the reamining
argv to another parser.
"""

def add_config_file_values(filename, args):
    with open(args.config, 'r') as y:
        defaults = yaml.safe_load(y)

    new_defaults = {}
    for k,v in defaults.items():
        if '-' in k:
            kk = k.replace('-', '_')
            if kk in defaults:
                raise Exception("Cannot have '-' version and '_' of a key in the same file")
            new_defaults[kk] = v
        else:
            new_defaults[k] = v
    defaults = new_defaults

    for k,v in defaults.items():
        if k in args and args.__dict__[k] is None:
            args.__dict__[k] = v
        else:
            print(f"Key '{k}' in config file is not a recognized argument")
    return args

def get_args():
    p = argparse.ArgumentParser(
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    p.add_argument("-C", "--config")
    p.add_argument("--list", nargs='+')
    p.add_argument("--multiple-words", nargs='+')

    args = p.parse_args()

    if not args.config:
        default_config_file = "conf.yml"
        if os.path.isfile(os.path.expanduser(default_config_file)):
            args.config = default_config_file

    return add_config_file_values(args.config, args)

print(get_args())
