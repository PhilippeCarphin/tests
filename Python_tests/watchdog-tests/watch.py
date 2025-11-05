#!/usr/bin/env python3
import time
import threading
import subprocess
import watchdog.observers
import argparse
import signal
import sys

STOP_RUN_THREAD = threading.Event()
END_PROGRAM = threading.Event()

p = argparse.ArgumentParser()
p.add_argument("--shell", action='store_true')
p.add_argument("filespec")
p.add_argument("cmd", nargs='+')
args = p.parse_args()

class RunHandler:
    def __init__(self, observer):
        self.observer = observer
    def dispatch(self, event):
        print(event)
        self.observer.stop()

def wait_for_event(file):
    """ Spin until a filesystem event happens or asked to stop if a signal sets
    the END_PROGRAM flag """
    o = watchdog.observers.Observer()
    handler = RunHandler(observer=o)
    o.schedule(handler, file)
    o.start()
    while o.is_alive():
        if END_PROGRAM.is_set():
            o.stop()
            o.join()
            return False
        time.sleep(0.5)
    o.join()
    return True

def run(cmd):
    """ Run command and wait for either the command to finish or the thread
    is singalled via STOP_RUN_THREAD to terminate the command """
    full_cmd = ['bash', '-c', ' '.join(cmd)]
    p = subprocess.Popen(full_cmd)
    while not STOP_RUN_THREAD.is_set() and p.poll() is None:
        time.sleep(0.5)
    if p.poll() is None:
        print(f"... managed process still running: sending sigterm")
        p.terminate()
    p.wait()
    if p.returncode == -15:
        print("... process ended by TERM")
    elif p.returncode == 0:
        print("... process ended with SUCCESS")
    else:
        print(f"... process failed {p.returncode}")
    STOP_RUN_THREAD.clear()

def signal_end(*args):
    """ Singal handler for TERM and SIGINT.  sets both the END_PROGRAM and
    the STOP_RUN_THREAD flags and resumes execution.  The program will end
    naturally due to those flags shortly after """
    END_PROGRAM.set()
    STOP_RUN_THREAD.set()

signal.signal(signal.SIGINT, signal_end)
signal.signal(signal.SIGTERM, signal_end)

RUN_THREAD = None
while wait_for_event(args.filespec):
    print("File event observed")
    if RUN_THREAD and RUN_THREAD.is_alive():
        print(f"... terminating previous instance of {args.cmd}")
        STOP_RUN_THREAD.set()
        RUN_THREAD.join()
    print(f"... starting new instance of {args.cmd}")
    RUN_THREAD = threading.Thread(target=run, args=(args.cmd,))
    RUN_THREAD.start()

if RUN_THREAD and RUN_THREAD.is_alive():
    RUN_THREAD.join()
print("FINISHED")

