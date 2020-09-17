import os

class phil_open:
    def __init__(self, filename, mode):
        self.filename = filename
        self.mode = mode
        self.file_object = None

    def __enter__(self):
        print(f'Opening file {self.filename} in mode {self.mode}')
        self.file_object = open(self.filename, self.mode)
        return self.file_object

    def __exit__(self, *args):
        print(f'Closing file {self.filename}')
        self.file_object.close()


if __name__ == "__main__":
    filename = os.path.expanduser('~/.profile')
    with phil_open(filename, "r") as f:
        lines = f.read().splitlines()
        print('in the "with" block')
        raise ValueError('OOPSIE')
    print('after the "with" block')


