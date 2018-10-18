import os
import time

def child():
    print('I am the child and have pid', os.getpid())
    os._exit(0)

def parent():
    while True:
        new_pid = os.fork()

        if new_pid == 0:
            child()
        else:
            print("I am the parent with pid: {}. I have a child with pid: {}".format(os.getpid(), new_pid))

        time.sleep(0.001)
        reply = input("Press q to quit or c for new fork")

        if reply != 'c':
            break;

parent()
