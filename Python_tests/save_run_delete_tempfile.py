import tempfile
import time
import os
import subprocess


input_user_script = '''#!/bin/sh

echo allo
echo bonjour >&2
'''

tempfile_name = None

with tempfile.NamedTemporaryFile(dir=os.getcwd(), prefix='tempfile_ntf_', mode='w') as ntf:
    ntf.file.write(input_user_script)
    ntf.file.close()
    os.chmod(ntf.name, 0o755)
    tempfile_name = ntf.name
    subprocess.run(['bash', '-c', ntf.name])

if os.path.exists(tempfile_name):
    print("Tempfile still exists here")
else:
    print("Tempfile doesn't exist here")

ordenv_setup="""
export ORDENV_SITE_PROFILE=20190814
export ORDENV_COMM_PROFILE=eccc/20191002
export ORDENV_GROUP_PROFILE=eccc/cmc/1.8
. /fs/ssm/main/env/ordenv-boot-20200204.sh
"""

def create_temp_script(content, prefix='temp_script_', suffix='.sh' , mode=0o644):
    temp_script = tempfile.mkstemp(dir=TEMP_DIR, prefix=prefix)
    filename = temp_script[1]

    with open(filename, 'w') as f:
        f.write(content)

    os.chmod(filename, mode)

    return filename

def generate_wrapper_script():
    job_header = get_resources()
    wrapper_script = """#!/bin/bash
    {job_header}
    {files["user"]} >> {files["output"]} 2>&1
    echo $? > {files["status"]}
    """
    return create_temp_script(
            wrapper_script,
            prefix='wrapper_',
            mode=0o644
    )

def generate_user_script():
    input_user_script = '''
    set -e
    {sys.stdin.read()}
    '''
    return create_temp_script(
        input_user_script,
        prefix='user_script',
        suffix='.jgen',
        mode=0o755
    )

def generate_job_stopper_script():
    job_stopper_script=f"""
echo "JOBSTOPPER SCRIPT"
{ordenv_setup}
jobdel $1
"""
    return create_temp_script(
        job_stopper_script,
        prefix='jobstopper_script_',
        suffix='.sh',
        mode=0o755
    )

def generate_jobsub_script():
    jobsub_script=f"""#!/bin/bash
{ordenv_setup}
jobsub $1
"""
    return create_temp_script(
        jobsub_script,
        prefix='jobsub_script_',
        suffix='.sh',
        mode=0o755
    )








