from module_with_main import *

def compute_val():
    l = [0,1,2,3,4,5]
    s = 0
    for n in range(10):
        v = useful_function(l[(7 * i + 6) % len(l)])
        s += v
    return s

def main():
    val = compute_val()
    print(f"val={val}")

if __name__ == '__main__':
    main()
