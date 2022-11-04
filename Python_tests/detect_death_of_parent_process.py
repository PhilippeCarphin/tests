import signal
import time
import sys
import os

def handle_signal(signum, backtrace):

    signame = signal.Signals(signum).name
    log_file.write(f'Caught signal {signame}\n')
    sys.exit(signum)

with open('log.txt', 'w', buffering=1) as log_file:


    signal.signal(signal.SIGHUP, handle_signal)
    # signal.signal(signal.SIGTSTP, handle_signal)
    # signal.signal(signal.SIGTERM, handle_signal)
    # signal.signal(signal.SIGCHLD, handle_signal)

    log_file.write(f'Parent PID = {os.getppid()}\n')

    while True:
        log_file.write(f'PID = {os.getpid()} - \r')
        time.sleep(1)
        log_file.write(f'PID = {os.getpid()} \ \r')
        time.sleep(1)
        log_file.write(f'PID = {os.getpid()} | \r')
        time.sleep(1)
        log_file.write(f'PID = {os.getpid()} / \r')
        time.sleep(1)
        if sys.stdout.closed:
            log_file.write('\nstdout is closed, we are done\n')
            sys.exit()


