import os
import subprocess
import time


#Kinda sourceing a script
def sourcing_demo():
    script = os.path.join(os.path.dirname(__file__), 'sourced_guy.sh')
    q = subprocess.Popen(['bash'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    with open(script, 'r') as s:
        script_text = s.read()

    q.stdin.write(script_text.encode('utf-8'))
    q.stdin.write(b'env\n')
    stdout = q.communicate()
    print(stdout)

def process_wrapper_demo():
    p = subprocess.Popen(['bash'], stdin=subprocess.PIPE)
    try:
        while True:
            host = os.uname().nodename
            user = os.environ['USER']
            cmd = input(f'{user}@{host} {os.getcwd()} $ ')
            p.stdin.write(cmd.encode('utf-8') + b'\n')
            p.stdin.flush()
            time.sleep(0.1)
    except EOFError:
        pass
    # If I wanted my script to have access to stdout
    # The sleep is like making sure that we empty stdout before printing the prompt because we don't read stdout
    # You need a separate thread that reads things and puts them in a queue
    # as in https://github.com/PhilippeCarphin/leela_interface/blob/master/src/pipelistener.py

sourcing_demo()
process_wrapper_demo()