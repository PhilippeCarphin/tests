
import subprocess
import time

p = subprocess.Popen(['bash'], stdin=subprocess.PIPE)

p.stdin.write('echo "ALLO"'.encode('utf-8'))

time.sleep(1)
# m = bytes([0, 1,2,3,4,5,6,7,8,9,10])
m = '\n'.encode('utf-8')

p.stdin.write(m)


p.stdin.flush()
time.sleep(0.1)

# TODO Use this for sourcing

script = './sourced_guy.sh'

q = subprocess.Popen(['bash'], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
with open(script, 'r') as s:
    script_text = s.read()

q.stdin.write(script_text.encode('utf-8'))
q.stdin.write(b'env\n')
stdout = q.communicate()
print(stdout)

while True:
    cmd = input("Please enter command")
    p.stdin.write(cmd.encode('utf-8') + m)
    p.stdin.flush()
    time.sleep(1)