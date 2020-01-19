import os
import subprocess
import json

p = subprocess.run(['sh', '-c', 'export PHIL=VALUE_ALLO ; python3 -c "import os,json; print(json.dumps(dict(os.environ)))"'], stdout=subprocess.PIPE)
s = p.stdout.decode('utf-8')
d = json.loads(s)

print(f'os.environ contains variable PHIL: {"PHIL" in os.environ}')

print('updating with stdout of process')
os.environ.update(d)

print(f'os.environ contains variable PHIL: {"PHIL" in os.environ}')
