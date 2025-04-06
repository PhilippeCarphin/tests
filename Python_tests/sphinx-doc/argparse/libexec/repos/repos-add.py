#!/usr/bin/env python3

import sys
import argparse
import os
import _repos_logging

logger = _repos_logging.logger

def arg_parser():
    p = argparse.ArgumentParser(description="Add a repo to the repos.yml config file")
    p.add_argument("-F", help="Specify alternate file to ~/.config/repos.yml")
    p.add_argument("repo", help="Specify the repository, defaults to $PWD", nargs='?')
    p.add_argument("--name", help="Specify name for repo in config file")
    return p

if __name__ == "__main__":
    sys.exit(main(get_args()))
