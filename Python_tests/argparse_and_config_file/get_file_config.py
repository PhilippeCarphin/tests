import argparse
import os
import yaml

def get_file_config(default_path, config_file_arg_names):
    """ Returns conf_parser, defaults, remaining_argv
    Use conf_parser in 'parser = ArgumentParser(..., parents=[conf_parser]) for
    the config file argument to be shown in the help.

    Use defaults in 'parser.set_defaults(**defaults)' before using
    parser.parse_args() to set the default values with minimal checks.

    Then run parser.parse_args(remaining_argv) and continue as usual.

    Alternatively to 'parser.set_defaults(**defaults)' one can have some checks
    to detect unused portions of the config file by following this example
    after having called 'args = parser.parse_args(remaining_argv):

        for k,v in defaults.items():
            if k in args and args.__dict__[k] is None:
                args.__dict__[k] = v
            else:
                print(f"Key '{k}' in config file is not a recognized argument")

    Note: The function changes all '-' in key names to '_' and raises an
    exception if both versions are found in the same file.
    """

    conf_parser = argparse.ArgumentParser(add_help=False)
    conf_parser.add_argument(*config_file_arg_names, help="Specify a configuration file", metavar="FILE")
    args, remaining_argv = conf_parser.parse_known_args()
    if not args.config:
        default_config_file = "conf.yml"
        if os.path.isfile(os.path.expanduser(default_config_file)):
            args.config = default_config_file

    if args.config:
        with open(args.config, 'r') as y:
            defaults = yaml.safe_load(y)
    else:
        defaults = {}

    # Change '-' in key names to '_' and raise exception if both versions are found
    new_defaults = {}
    for k,v in defaults.items():
        if '-' in k:
            kk = k.replace('-', '_')
            if kk in defaults:
                raise Exception("Cannot have '-' version and '_' of a key in the same file")
            new_defaults[kk] = v
        else:
            new_defaults[k] = v

    return conf_parser, new_defaults, remaining_argv


def get_args():
    conf_parser, defaults, remaining_argv = get_file_config("conf.yml", ['-C', '--config'])
    p = argparse.ArgumentParser(
        parents=[conf_parser],
        description=__doc__,
        formatter_class=argparse.RawDescriptionHelpFormatter,
    )
    p.add_argument("--list", nargs='+')
    p.add_argument("--multiple-words", nargs='+')

    args = p.parse_args(remaining_argv)

    for k,v in defaults.items():
        if k in args and args.__dict__[k] is None:
            args.__dict__[k] = v
        else:
            print(f"Key '{k}' in config file is not a recognized argument")
    return args

args = get_args()
print(args)
