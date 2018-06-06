#!/usr/bin/python3

import sys
from subprocess import call

if len(sys.argv) < 2:
    print("Missing argument")
    sys.exit(1)

lib=sys.argv[1]

call(['gcc', '--print-file-name='+lib]);
