
import os
import sys
import subprocess



stdout = subprocess.check_output(['/bin/bash', '-c', 'source ./sourced_guy.sh >/dev/null 2>&1 ; env'])

new_env = {pair[0]: pair[1]
           for pair in [
               line.split('=') for line in stdout.decode('utf-8').split('\n')
           ] if len(pair) == 2
           }

import pprint

pprint.pprint(new_env)

os.environ.update(new_env)

os.execl('/bin/bash', '/bin/bash')
