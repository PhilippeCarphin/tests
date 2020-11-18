import sys
import time

sigint_flag = False
def sigint_handler(signum, backtrace):
    global sigint_flag
    sigint_flag = True
signal.signal(signal.SIGINT, sigint_handler)


with open(sys.argv[1], 'r') as f:
    while True:
        time.sleep(1)
        read = f.read()
        if read:
            sys.stdout.write(read)
