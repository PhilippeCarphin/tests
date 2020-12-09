import subprocess
import json
import os

script = r'''
ssh localhost \
        "python3 -c \
'
import os
import json
print(json.dumps(dict(os.environ)))
'"
# Important in case there are traps that print to stdout
exec 1>&2
'''

result = subprocess.run(script, shell=True, universal_newlines=True,
        stdout=subprocess.PIPE)

base_env = json.loads(result.stdout)
del base_env['_']
import pprint
pprint.pprint(base_env)

