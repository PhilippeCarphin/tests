# from : https://gist.github.com/gene1wood/9217725
# Commented and modified a bit.
# Reusable version in get_file_config.py
import os
import argparse
import yaml

# INPUTS:
# - arg spec : add_arguments()...
# - default config file

""" BEGIN get_file_config() <- default_path, ['-C', '--config'] """
def process_defaults(defaults):
    """ Optional part: Allow keys matching command line argument names
    as well as the version with '-' replaced by '_'.

    Note: We don't know what the arguments will be.  This function just
    changes keys k with k.replace('-', '_') and makes sure that both forms
    of a key are not there."""
    new_defaults = {}
    for k,v in defaults.items():
        if '-' in k:
            kk = k.replace('-', '_')
            if kk in defaults:
                raise Exception("Cannot have '-' version and '_' of a key in the same file")
            new_defaults[kk] = v
        else:
            new_defaults[k] = v
    return new_defaults

"""
Create a parser that will just look for '-C' or '--config' using
parse_known_args.
"""
conf_parser = argparse.ArgumentParser(
        # Turn off help, so we print all options in response to -h
        add_help=False
)
conf_parser.add_argument("-c", "--config",
                         help="Specify a configuration file", 
                         metavar="FILE")
args, remaining_argv = conf_parser.parse_known_args()

"""
Set a default config file if one was not found on the command line
"""
if not args.config:
    default_config_file = "conf.yml"
    if os.path.isfile(os.path.expanduser(default_config_file)):
        args.config = default_config_file

"""
Read the config file
"""
if args.config:
    with open(args.config, 'r') as y:
        defaults = yaml.safe_load(y)
else:
    defaults = {}

"""
Optionnaly check errors and do some kind of processing.  Here it's allowing
keys with '-' or '_' but not both for the same key.
"""
defaults = process_defaults(defaults)

""" END get_file_config() -> parser, defaults """

"""
Create a parser as we would normally but give it 'config_parser' as a parent.
This makes it so that the '-C, --config' arguments will show up in the help
"""
p = argparse.ArgumentParser(
    parents=[conf_parser],
    description=__doc__,
    formatter_class=argparse.RawDescriptionHelpFormatter,
)
p.add_argument("--list", nargs='+')
p.add_argument("--multiple-words", nargs='+')

"""
On GitHub, the guy used this to set the defaults but this doesn't reject unknown
keys so I did something else, but I have to run parse_args first...
"""
# p.set_defaults(**defaults)

"""
Parse the arguments as usual
"""
args = p.parse_args(remaining_argv)

"""
For each argument whose value is None, set it to the value
found in defaults (the config file) if there is one

I iterate over the items of defaults because that way I can
give a message if there is something in the config file that
should not be there.
"""
for k,v in defaults.items():
    if k in args and args.__dict__[k] is None:
        args.__dict__[k] = v
    else:
        print(f"Key '{k}' in config file is not a recognized argument")



print('list' in args)

print(args)
