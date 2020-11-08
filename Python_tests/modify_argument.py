
def modify_var(arg):
    arg = "MODIFIED ARG"

def modify_list(l):
    l.append('ADDED ELEMENT')

def do_partial_work(l):
    # Leaves our object in an invalid state
    l.append('THE NEXT ELEMENT IS HELLO')
    raise Exception("Cannot complete work")
    l.append('HELLO')

def do_all_or_no_work(l):
    result = list(l)
    result.append('THE NEXT ELEMENT IS HELLO')
    raise Exception("Cannot complete work")
    result.append('HELLO')
    return result

def raise_exception(arg):
    if arg % 2 == 0:
        raise Exception("Even numbers are bad")

    return arg**3

def main():
    # You cannot change what object main_var points to.
    # They are like C pointers and you can't pass &main_var
    # so that a function could change what main_var points to.
    main_var = "Initial main var value"
    modify_var(main_var)
    print(main_var)

    # We can modify the object itself.  main_var points to a
    # list, we can modify this list in a function
    main_var = ['elem 0', 'elem 1']
    modify_list(main_var)
    print(main_var)

    # No rollback to modifications in case of exceptions. Here
    # the list pointed to by main_var may get screwed up by
    # the function.  We cant ensure that main_var points to
    # a valid object.
    try:
        do_partial_work(main_var)
    except:
        pass
    finally:
        # Where is "The next element"
        print(f"Exception: main_var = {main_var}")

    # But assignment doesn't happen if the right hand side
    # raises an exception.  We can ensure that a points to
    # a valid object.  This is a copy and swap.  The function
    # returns a modified copy and we update the pointer true_list
    # to point to the modified copy only if everything went well
    true_list = ['This list contains no lies']
    try:
        true_list = do_all_or_no_work(true_list)
    except:
        pass
    finally:
        # If we modify by returning a new instance (not
        # necessarily always possible), then we can be
        # sure that a points to a valid object since if
        # the function raises an exception, the assignment
        # doesn't happen.
        print(f'true_list = {true_list}')

if __name__ == "__main__":
    main()
