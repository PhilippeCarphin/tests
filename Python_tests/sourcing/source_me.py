import os
""" THis test demonstrates that you can kind of use"""

os.environ['PYTHON_COLOR'] = 'red_no_green_no_blue'

os.execl('/bin/bash')
