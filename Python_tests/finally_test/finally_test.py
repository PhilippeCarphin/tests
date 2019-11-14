def finally_no_except(x):
    try:
        print("Trying")
        raise Exception("Something went wrong")
        print("never run")
    finally:
        print("Finally")


finally_no_except(1)
