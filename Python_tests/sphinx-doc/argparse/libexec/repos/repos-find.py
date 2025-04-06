
#!/usr/bin/env python3
import os
import argparse
import _repos_logging

logger = _repos_logging.logger

def arg_parser():
    p = argparse.ArgumentParser(description="Find git repos recursively and produce YAML code for ~/.config/repos.yml on STDOUT.  Use the --merge option to merge the results into the config file")
    p.add_argument("dirs", nargs='*', default=[os.getcwd()], help="Directories to search.  Searches PWD if none are specified")
    p.add_argument("--recursive", action='store_true', help="Search recursively")
    p.add_argument("--debug", action="store_true", help="Print current search dir to STDERR")
    p.add_argument("--merge", action='store_true', help="Merge with repo file")
    p.add_argument("-F", dest='repo_file', metavar="CONFIG_FILE", help="Alternate repo-file, defaults to ~/.config/repos.yml", default=os.path.expanduser("~/.config/repos.yml"))
    p.add_argument("--exclude", help="Regular expression to exclude")
    p.add_argument("--include", help="Regular expression to include")
    p.add_argument("--cleanup", action='store_true', help="Remove repos that don't exist anymore.  Only valid when using the --merge option")

    return p


# It is important that this be protected by this if because otherwise the
# tool gets called with no arguments sphinx imports this file.
if __name__ == "__main__":
    args = arg_parser().parse_args()
