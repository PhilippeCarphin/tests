import subprocess
import os

result = subprocess.run(['ls', '-l', os.environ['HOME']], stdout=subprocess.PIPE, text=True)
print(result.stdout)
try:
    result = subprocess.run(['ls', 'no-exists'], check=True, stderr=subprocess.PIPE, text=True)
except subprocess.CalledProcessError as e:
    print(f'stderr of process: {result.stderr}')
    print(f'{type(e)} thrown : {e}')
    print(f'Error was thrown when process failed because of "check" argument')

cmd = ['ls', '-l', os.environ['HOME']]

result = subprocess.run(cmd, capture_output=True, text=True)

result = subprocess.run(cmd, stdout=subprocess.PIPE, stderr=subprocess.STDOUT, text=True)
combined_output = result.stdout

