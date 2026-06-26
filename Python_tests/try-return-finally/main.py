

def test():
    try:
        print("Try")
        return 8
    finally:
        print("Finally")

if __name__ == "__main__":
    result = test()
    print(f"Result is {result}")
