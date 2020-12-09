import signal
import time
import sys
import os
log_file = open('log.txt', 'w', buffering=1)

def handle_signal(signum, backtrace):

    signame = signal.Signals(signum).name
    log_file.write(f'Caught signal {signame}\n')
    sys.exit(signum)

signal.signal(signal.SIGHUP, handle_signal)
# signal.signal(signal.SIGTSTP, handle_signal)
# signal.signal(signal.SIGTERM, handle_signal)
# signal.signal(signal.SIGCHLD, handle_signal)


while True:
    log_file.write(f'PID = {os.getpid()} - \n')
    time.sleep(1)
    log_file.write(f'PID = {os.getpid()} \ \n')
    time.sleep(1)
    log_file.write(f'PID = {os.getpid()} |\n')
    time.sleep(1)
    log_file.write(f'PID = {os.getpid()} / \n')
    time.sleep(1)
    if sys.stdout.closed:
        log_file.write('stdout is closed, we are done\n')
        sys.exit()


