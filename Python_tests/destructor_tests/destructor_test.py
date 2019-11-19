import os
class RAIIFileHandleWrapper:
    def __init__(self, filename, mode='r', name='default'):
        # Raises OSError if unsuccessfull
        print(f"    RAIIFileHandleWrapper('{name}') __init__")
        self.name = name
        self.file_object = open(filename, mode=mode)

    def __del__(self):
        print(f"    RAIIFileHandleWrapper('{self.name}') __del__")
        self.file_object.close()

def create_without_assigning():
    print("create_without_assigning() begin")
    RAIIFileHandleWrapper(os.path.expanduser('~/.bashrc'), name='created but not assigned')
    print("create_without_assigning() end")
def local_variable():
    print("local_variable() begin")
    v = RAIIFileHandleWrapper(os.path.expanduser('~/.bashrc'), name='local variable')
    print("local_variable() end")

def returned_variable():
    print("returned_variable() begin")
    v = RAIIFileHandleWrapper(os.path.expanduser('~/.bashrc'), name='returned variable')
    print("returned_variable() end")
    return v

def main():
    print("main() begin")
    print("------------- create_without_assigning() ------------------")
    create_without_assigning()
    print("------------- local_variable() ----------------------------")
    local_variable()
    print("------------- returned_variable() -------------------------")
    v = returned_variable()
    print("-----------------------------------------------------------")
    print("main() end")

if __name__ == "__main__":
    main()
    print("end of program")

