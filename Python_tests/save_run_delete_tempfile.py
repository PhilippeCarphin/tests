import tempfile
import time
import os
import subprocess


input_user_script = '''#!/bin/sh

echo allo
echo bonjour >&2
'''

tempfile_name = None

with tempfile.NamedTemporaryFile(dir=os.getcwd(), prefix='tempfile_ntf_',
        mode='w') as ntf:
    ntf.file.write(input_user_script)
    ntf.file.close()
    os.chmod(ntf.name, 0o755)
    tempfile_name = ntf.name
    subprocess.run(['bash', '-c', ntf.name])

if os.path.exists(tempfile_name):
    print("Tempfile still exists here")
else:
    print("Tempfile doesn't exist here")




