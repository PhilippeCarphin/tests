
import os
import sys
import subprocess

def get_env_from_sourcing(filename):
    stdout = subprocess.check_output(['/bin/bash', '-c', f'source {filename} >/dev/null 2>&1 ; env'])

    new_env = {pair[0]: pair[1]
               for pair in [
                   line.split('=') for line in stdout.decode('utf-8').split('\n')
               ] if len(pair) == 2
               }

    return new_env


def pysource(filename):
    new_env = get_env_from_sourcing(filename)
    os.environ.update(new_env)


def setup_environment():
    os.environ['SOURCING_GUY_EXPORTED_VARIABLE'] = 'SOURCING_GUY_VALUE'
    pysource('./sourced_guy.sh')

setup_environment()
assert(os.environ['SOURCED_GUY_EXPORTED_VARIABLE'] != '')

# With this line, doing
# python3 sourcing_guy.py
# will make it look like you did
# source sourced_guy.sh
# os.execl('/bin/bash', '/bin/bash')
