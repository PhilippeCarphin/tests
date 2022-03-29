#!/usr/bin/env python3

import sys
from pprint import pprint
import os

with open(os.path.expanduser('~/.log.txt'), 'a') as f:

    print('=============================================', file=f)
    # Arguments passed to the command
    print(f'sys.argv[1] = {sys.argv[1]} (command)', file=f)
    print(f'sys.argv[2] = {sys.argv[2]} (current)', file=f)
    print(f'sys.argv[3] = {sys.argv[3]} (previous)', file=f)

    # Complete command line
    print(f"os.environ['COMP_LINE'] = {os.environ['COMP_LINE']}", file=f)

    # Index within the line where the cursor is
    print(f"os.environ['COMP_POINT'] = {os.environ['COMP_POINT']}", file=f)

    # Type of completion
    # '?' normal completion
    # '!' listing completion like after double tab
    # '@' listing alternatives...
    print(f"os.environ['COMP_TYPE'] = {os.environ['COMP_TYPE']}", file=f)

    # The key (or final key of a key sequence) used to invoke the current completion function.
    print(f"os.environ['COMP_KEY'] = {os.environ['COMP_KEY']}", file=f)

    comp = {k:v for k,v in os.environ.items() if k.startswith('COMP_')}
    pprint(comp, stream=f)

    candidates = ['apple', 'apricot', 'bananna', 'cherry']

    matching_candidates = filter(lambda w: w.startswith(sys.argv[2]), candidates)

    print('\n'.join(matching_candidates))
