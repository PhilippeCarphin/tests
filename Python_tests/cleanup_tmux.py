import os
import stat
import sys
import time

def normal_files(d):
    for root, dirs, files in os.walk(d):
        yield from (os.path.join(root, f) for f in files)

def public_sockets(d):
    for f in normal_files(d):
        if is_public_socket(f):
            yield f

def is_public_socket(f):
    try:
        st = os.stat(f)
        if stat.S_IMODE(st.st_mode) == 0o777:
            if stat.S_ISSOCK(st.st_mode):
                return True
    except FileNotFoundError:
        pass
    except PermissionError:
        pass


def check_dir(d):
    for f in public_sockets(d):
        print(f'We got one: {f}\a')
        # return True
    return False


sys.exit(check_dir(sys.argv[1]))

while True:
    print('checking ...')
    check_dir(sys.argv[1])
    print('sleeping ...')
    time.sleep(5)

