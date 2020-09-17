import os
import subprocess
print(f'Initial os.getcwd() : {os.getcwd()}') 
print(f'Initial os.environ["PWD"]: {os.environ["PWD"]}') 
print("==== os.chdir('/home/phc001/workspace/spooki') ======")
os.chdir('/home/phc001/workspace/spooki') 
print(f'Final os.getcwd() : {os.getcwd()}') 
print(f'Final os.environ["PWD"]: {os.environ["PWD"]}') 
result = subprocess.run(['pwd'], stdout=subprocess.PIPE)
print(f'Result of running "pwd" as a subprocess: {result.stdout.decode("utf-8").strip()}')
result = subprocess.run(['printenv', 'PWD'], stdout=subprocess.PIPE)
print(f'Result of runing "printenv PWD" as a subprocess : {result.stdout.decode("utf-8").strip()}')
print(f'Result of running os.system(echo $PWD) : ...')
os.system('echo $PWD')
print(f'Result of running os.system(printenv PWD) : ...')
os.system('printenv PWD')

quit()

def get_number_of_lines(file):
    try:
        with open(file) as f:
            return f.read().count('\n')
    except UnicodeDecodeError:
        with open(file, encoding='iso8859-1') as f:
            return f.read().count('\n')


def count_lines(directory):
    lines = 0
    for f in os.listdir(directory):
        file = os.path.join(directory, f)
        # print(file)
        if os.path.isfile(file):
            lines += get_number_of_lines(file)

    return lines


def count_lines_other(directory):
    lines = 0
    os.chdir(directory)
    for f in os.listdir():
        # print(f)
        if os.path.isfile(f):
            lines += get_number_of_lines(f)

    return lines

print(count_lines('/home/phc001/workspace/spooki/plugins'))
print(count_lines_other('/home/phc001/workspace/spooki/plugins'))
