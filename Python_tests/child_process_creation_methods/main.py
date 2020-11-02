import multiprocessing
import subprocess
import os
import tempfile
import time
import signal
import psutil

glb_var = "INITIAL VALUE"

def main():
    fork_and_run()
    # multiproc_run()
    # popen_tail()

def popen_tail():
    p = subprocess.Popen(['tail', '-f', 'log.txt'])
    print(p)

def child(tmpdir):

    print(f'child sees glb_var = {glb_var}')

    print(f'My tmpdir is {tmpdir}')
    while True:
        try:
            time.sleep(6)
            print(f'Child : pid = {os.getpid()}')
        except KeyboardInterrupt:
            print("Child received KeyboardInterrupt")

def parent_wait(child_pid):
    print(f"Parent : PID : {os.getpid()}")
    sigint_caught = False
    def sigint_handler(signum, backtrace):
        nonlocal sigint_caught
        sigint_caught = True
    signal.signal(signal.SIGINT, sigint_handler)

    child = psutil.Process(child_pid)

    while True:
        time.sleep(2)
        if sigint_caught:
            sigint_caught = False
            print(child)
            answer = input("Continue y/n : ")
            if answer.upper() in ['N', 'NO']:
                child.terminate()
                break
        if child.status() == 'zombie':
            print(f'Detected that {child} is zombie')
            break

def multiproc_run():

    global glb_var
    glb_var = "MULTIPROC_RUN"
    tempdir = tempfile.TemporaryDirectory(dir=os.getcwd(), prefix='tempdir_')
    p = multiprocessing.Process(target=child, args=(tempdir.name,))
    p.start()
    parent_wait(p.pid)


def fork_and_run():

    global glb_var
    glb_var = "FORK AND RUN"

    tempdir = tempfile.TemporaryDirectory(dir=os.getcwd(), prefix='tempdir_')
    new_pid = os.fork()
    parent_pid = os.getpid()

    if new_pid == 0:
        pass
        with open('log.txt', 'a') as f:
            f.write(f'Child pid = {os.getpid()}')
        os.execlp('tail', '-f', 'log.txt')
        # child(tempdir)
    else:
        parent_wait(new_pid)

if __name__ == "__main__":
    main()
