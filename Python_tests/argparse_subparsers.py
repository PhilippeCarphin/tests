import logging
import argparse

#
# This test demonstrates two things:
#
# - Doing subcommands with argparse using subparsers
#
# - The argparse.Action class to have other actions than the 'builtin' ones
#   like 'count', 'store_true' etc.  In this case to set the log level.
#   For that, I would normally just put some code after p.parse_args() and it
#   would be simpler that way.
#

DESCRIPTION = """ Tests of the logging library """

def cmd_phil(args, **kwargs):
    print(f"cmd_phil(): {args}")

def cmd_paul(args, **kwargs):
    print(f"cmd_paul(): {args}")

def main():
    args = get_args()
    args.func(args)

def get_args():

    p = argparse.ArgumentParser(description=DESCRIPTION)
    p.add_argument("-F", metavar="CONFIG_FILE")
    subparsers = p.add_subparsers()

    common = argparse.ArgumentParser(add_help=False)
    common.add_argument("--file")

    parser_phil = subparsers.add_parser('phil', parents=[common])
    parser_phil.set_defaults(func=cmd_phil)
    parser_phil.add_argument("--phil-arg")

    parser_paul = subparsers.add_parser('paul', parents=[common])
    parser_paul.set_defaults(func=cmd_paul)
    parser_paul.add_argument("--paul-arg")

    return p.parse_args()

if __name__ == "__main__":
    main()
