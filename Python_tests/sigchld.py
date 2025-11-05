import signal
import subprocess
import time

stop = False

def handle_sigchld(signum, stack):
    global stop
    print("Got sigchld")
    # stop = True

signal.signal(signal.SIGCHLD, handle_sigchld)


while not stop:
    p = subprocess.Popen('sleep 3', shell=True)
    time.sleep(1)

print(r)
