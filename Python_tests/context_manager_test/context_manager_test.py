from contextlib import contextmanager

class DemoError(BaseException):
    pass

@contextmanager
def SimpleContextManager(id):
    thing_I_keep = 2*id
    thing_I_give = 3*id
    print('    Beginning of SimpleContextManager, (Opening a file)')
    try:
        print('    Yeild from the function (like returning a file handle)')
        yield thing_I_give
    except DemoError as e:
        print(f"    DemoError caught in SimpleContextManager")
    finally:
        print(f'    finally block in SimpleContextManager, (Closing a file) thing_I_keep = {thing_I_keep}')


def test_simple_context_manager_catch():
    print("USING DemoError")
    with SimpleContextManager(21) as thing_I_got:
        print(f'    thing_I_got in test function : {thing_I_got}')
        print('    The context manager can catch exceptions thrown here')
        raise DemoError()
        print('    The exception still takes us out of the block')

def test_simple_context_manager_no_catch():
    print("USING ValueError")
    with SimpleContextManager(21) as thing_I_got:
        print(f'    thing_I_got in test function : {thing_I_got}')
        print('    The context manager can catch exceptions thrown here')
        raise ValueError("thing_I_got is not what I wanted")
        print('    The exception still takes us out of the block')

test_simple_context_manager_catch()
try:
    test_simple_context_manager_no_catch()
except ValueError as e:
    print("This time nobody caught the exception. BUT THE FILE ALWAYS GOT CLOSED")
