import subprocess
import os

# Again, I'm going to be using 'ls' as the external command.
# use os.listdir(path) if you want get the contents of a directory.

result_object = subprocess.run(['ls', '-l', os.environ['HOME']], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
print(f'result_object.returncode={result_object.returncode}')
# stdout and stderr will be of type bytes, so we
# have to change them to strings:
stderr = result_object.stderr.decode('utf-8')
print(f'stderr={stderr}')
stdout = result_object.stdout.decode('utf-8')
print(f'stdout={stdout}')

result_object = subprocess.run(['ls', '-l', '/no-exists'], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
print(f'result_object.returncode={result_object.returncode}')
# stdout and stderr will be of type bytes, so we
# have to change them to strings:
stderr = result_object.stderr.decode('utf-8')
print(f'stderr={stderr}')

# Have you ever done something like
# 1: grep 'string' file > /dev/null
# 2: if ! [ $? = 0 ] ; then
# 3:      echo "file doesn't contain 'string'""
# 4: fi
# but then you put another command between lines 1 and 2
# so you have to save $? in a variable status (status=$?)
# but you only do that after getting caught by the error

# Can also output to files...
with open('./ls-output.txt', 'w+') as f:
    subprocess.run(['ls', '-l', os.environ['HOME']], stdout=f)

# But for me, it is more common to do this:
result_object = subprocess.run(['ls', '-l', os.environ['HOME']], stdout=subprocess.PIPE, stderr=subprocess.PIPE)
if result_object.returncode == 0:
    stdout = result_object.stdout.decode('utf-8')
    def process(input):
        return input
    stuff_to_write = process(stdout)
    with open('./ls-output_2.txt', 'w+') as f:
        f.write(stuff_to_write)
else:
    print('Something went wrong with the command')

input('Press any key to end program and cleanup files')
os.remove('ls-output.txt')
os.remove('ls-output_2.txt')