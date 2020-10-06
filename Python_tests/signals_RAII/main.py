import signal
import os
import tempfile
import atexit

class Donesies(Exception):
    pass

def donesies(signum, stackframe, string):
    print(f'string = {string}')
    print(f'signum = {signum}')
    print(stackframe)
    raise Donesies

def exit_func():
    print("Exit function registered with atexit.register()")

def cleanup_func():
    print("Cleanup done through RAII, tempdir will delete itself")

if __name__ == "__main__":
    tmpdir = tempfile.TemporaryDirectory(dir=os.getcwd(), prefix='tmpdir_')
    signal.signal(signal.SIGTERM, lambda n,s: donesies(n,s,"SIGTERM"))
    signal.signal(signal.SIGINT,  lambda n,s: donesies(n,s,"SIGINT"))
    signal.signal(signal.SIGQUIT, lambda n,s: donesies(n,s,"SIGQUIT"))
    atexit.register(lambda : print("piss bucket"))
    try:
        print("Try Block")
        d = dict()
        while(True):
            pass
    except Donesies as e:
        cleanup_func()
    # finally:
        # cleanup_func()
        # No finall
