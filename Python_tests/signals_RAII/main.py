import signal
import os
import tempfile
import atexit


# Remember name
tmpdir_path = None

class MediumStoppage(Exception):
    pass

class SuperDone(Exception):
    pass

def medium_stoppage(signum, stackframe):
    print(f'Handling signal {signal.Signals(signum).name}')
    raise MediumStoppage("DONESIES")

def super_done(signum, stackframe):
    print(f'SUPERDONE signal handler')
    raise SuperDone


def atexit_func():
    print("atexit_func() called")

def cleanup_func():
    print("Cleanup done through RAII, tmpdir will delete itself")

def loop():
    d = dict()
    print("Looping ...")
    while(True):
        pass

class MyTmpDir(tempfile.TemporaryDirectory):
    def __init__(self, *args, **kwargs):
        prefix = kwargs['prefix'] + 'deriv_'
        super().__init__(dir=kwargs['dir'], prefix=prefix)
    def __del__(self):
        print(f'Deleting {self.name}')

def main():
    global tmpdir_path
    print(f"PID = {os.getpid()}")
    if RAII:
        # mtd = MyTmpDir(dir=os.getcwd(), prefix='tmpdir_')
        tmpdir = tempfile.TemporaryDirectory(dir=os.getcwd(), prefix='tmpdir_')
        tmpdir_path = tmpdir.name
        tmpdir_extra_ref = tmpdir
        print(f'TemporaryDirectory object {tmpdir} created')
    else:
        tmpdir = tempfile.mkdtemp(dir=os.getcwd(), prefix='tmpdir_')
        tmpdir_path = tmpdir
        print(tmpdir)
    try:
        loop()
    except Donesies:
        pass
    finally:
        cleanup_func()

def set_signal_handlers():
    signal.signal(signal.SIGINT,  medium_stoppage)
    signal.signal(signal.SIGQUIT, medium_stoppage)
    signal.signal(signal.SIGTERM, super_done)


if __name__ == "__main__":

    RAII = True

    set_signal_handlers()
    atexit.register(atexit_func)

    try:

        #
        # Main function has an RAII class that manages a temporary directory
        # The goal of this is to show that after this function is finished,
        # then our temporary directory has disappeared.
        #
        main()
        print("BACK FROM MAIN()")

        #
        # Programmatically check for the existence of tmpdir
        # after main function.  This is a CPython property
        #
        if tmpdir_path:
            if os.path.exists(tmpdir_path):
                print(f'{tmpdir_path} still exists and was not cleaned up')
            else:
                print(f"'{tmpdir_path} doesn't exist")

        #
        # Wait for second SIGINT to check that exiting main has
        # really removed the tmpdir instead of the removal happening when we
        # exit the script itself.
        #
        try:
            while True:
                pass
        except MediumStoppage:
            pass
    except SuperDone:
        pass

