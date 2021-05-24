import signal
import time
import sys
import os
# Try to have a particular action happen when
# the program gets hung up on (receives SIGHUP)
# or the program sees that its parent process
# has died.

# Fish seems to always send SIGHUP when you exit
# from the shell and there are jobs running
# Bash however does not, I can't remember if I
# ever got Bash to do it.

# tail -f log.txt to see output of running this.

# I ended up adding a loop that polls os.getppid()
# and returns if we get 1.  That's the last thing
# I tried and it worked the best.

# So you can't rely on receiving SIGHUP to know
# if your parent process has disappeared.

# Reasearch suggested that I try checking for stdout
# being closed.  This didn't seem to work though I
# didn not try very hard to find out why.
log_file = open('log.txt', 'a', buffering=1)

def handle_signal(signum, backtrace):
    signame = signal.Signals(signum).name
    log_file.write(f'Caught signal {signame}\n')
    sys.exit(signum)

signal.signal(signal.SIGHUP, handle_signal)
# signal.signal(signal.SIGTSTP, handle_signal)
# signal.signal(signal.SIGTERM, handle_signal)
# signal.signal(signal.SIGCHLD, handle_signal)

pid = os.getpid()
while True:
    log_file.write(f'PID = {pid} - \n')
    time.sleep(1)
    log_file.write(f'PID = {pid} \ \n')
    time.sleep(1)
    log_file.write(f'PID = {pid} |\n')
    time.sleep(1)
    log_file.write(f'PID = {pid} / \n')
    time.sleep(1)
    # if sys.stdout.closed:
    #     log_file.write('stdout is closed, we are done\n')
    #     sys.exit()

    ppid = os.getppid()
    log_file.write(f'Parent PID IS {ppid} (type:{type(ppid)}) \n')
    if ppid == 1:
        log_file.write('My parent process is gone, exiting \n')
        sys.exit()


