import os

os.environ['PYTHON_SETUP_ENV_NEW_VAR'] = 'Python setup env new var'


os.execl('/bin/bash', '/bin/bash')
