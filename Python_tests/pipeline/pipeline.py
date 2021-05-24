import time

duration = 1.0

def first(a):
    b = 2 * a
    time.sleep(duration)
    return b

def second(b):
    c = 3 * b
    time.sleep(duration)
    return c

def third(c):
    d = 4 * c
    time.sleep(duration)
    return d

def pipeline(number):
    b = first(number)
    c = second(b)
    d = third(c)

    return d

def main():
    for i in range(10):
        out = pipeline(i)
        print(out)

main()


