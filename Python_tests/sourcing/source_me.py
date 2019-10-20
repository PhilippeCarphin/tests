import os
import subprocess
""" THis test demonstrates that you can kind of use"""

os.environ['PYTHON_COLOR'] = 'red_no_green_no_blue'

# os.execl('/bin/bash', '')

subprocess.call(([
    '/bin/bash', '-c', 'source bash_script.sh ; env > environment.config'
]))

# Construct environment

## Start with a dict = current environment

## Change dict with various commands

# Exec bash with constructed environment
