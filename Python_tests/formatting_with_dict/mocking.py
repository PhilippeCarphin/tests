import subprocess

def mock_shell_command(cmd, desired_stdout):
    print(f'RUNNING COMMAND : {cmd}')
    r = subprocess.run(['true'])
    if isinstance(desired_stdout, bytes):
        r.stdout = desired_stdout
    else:
        r.stdout = bytes(desired_stdout, 'utf-8')
    return r

