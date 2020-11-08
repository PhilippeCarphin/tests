#!/usr/bin/env python3

import subprocess
import sys
import os
from termcolor import colored
import re


script, path, old_file, old_hex, old_mode, new_file, new_hex, new_mode = sys.argv

position_re = re.compile(r'(@@ .* @@)(.*)')

def main():
    diff_result = subprocess_diff_grepdiff()
    print(diff_result.returncode)

    output_lines = diff_result.stdout.splitlines()
    colored_lines = map(color_line, output_lines)

    header = colored(f'diff --color=always a/{path} b/{path}\n', 'white', attrs=['bold'])
    header += colored(f'index {old_hex}..{new_hex} {old_mode}', 'white', attrs=['bold'])

    print(header)
    print('\n'.join(colored_lines))

def subprocess_diff_grepdiff():
    grepdiff_regex=os.environ['GREPDIFF_REGEX']
    command = f'diff -u -p "{old_file}" "{new_file}" | grepdiff "{grepdiff_regex}" --output-matching=hunk'
    return subprocess.run(
            command, # shell=True causes command to be passed to 'bash -c'
            shell=True, # if it was shell=False, command should be [program, ar1, arg2]
            stdout=subprocess.PIPE, # Output arrives in result.stdout
            universal_newlines=True # result.stdout will be str and not bytes
    )

def color_line(l):
    m = position_re.match(l)
    if m:
        at_part = colored(m.group(1), 'cyan', attrs=['underline'])
        func_part = colored(m.group(2),'white')
        return f"{at_part}{func_part}"
    elif l.startswith('---'):
        return colored(f'--- a/{path}', 'white', attrs=['bold'])
    elif l.startswith('+++'):
        return colored(f'+++ b/{path}', 'white', attrs=['bold'])
    elif l.startswith('+'):
        return colored(l, 'green')
    elif l.startswith('-'):
        return colored(l, 'red')
    else:
        return l

main()
